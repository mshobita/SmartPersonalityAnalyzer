/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtNetwork>
#include <QApplication>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTextEdit>

#include "platformclientgui.h"

PlatformClientGUI::PlatformClientGUI(QWidget *parent) :
    QMainWindow(parent)
    , hostCombo(new QComboBox)
    , portLineEdit(new QLineEdit)
    , nameLineEdit(new QLineEdit)
    , ageLineEdit(new QLineEdit)
    , genderCombo(new QComboBox)
    , connectButton(new QPushButton("Connect",this))
    , submitButton(new QPushButton("Submit",this))
    , tcpSocket(new QTcpSocket(this))
{

    page1Widget = new QWidget(this);
    page2Widget = new QWidget(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    hostCombo->setEditable(true);
    // find out name of this machine
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        hostCombo->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            hostCombo->addItem(name + QChar('.') + domain);
    }
    if (name != QLatin1String("localhost"))
        hostCombo->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }

    portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    auto hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(hostCombo);
    auto portLabel = new QLabel(tr("S&erver port:"));
    portLabel->setBuddy(portLineEdit);

    auto serverGroupBox = new QGroupBox(tr("Server Info"));
    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(hostLabel);
    horizontalLayout->addWidget(hostCombo);
    horizontalLayout->addWidget(portLabel);
    horizontalLayout->addWidget(portLineEdit);
    horizontalLayout->addWidget(connectButton);
    horizontalLayout->addStretch(1);
    serverGroupBox->setLayout(horizontalLayout);


    statusLabel = new QLabel(tr("Please Enter Server Name and Port Number and connect to Server!"));

    createPersonalInfoBox();
    createPersonalityAnalysisBox();

    connectButton->setDefault(true);
    connectButton->setEnabled(false);

    submitButton->setDefault(true);
    submitButton->setEnabled(true);

    auto quitButton = new QPushButton(tr("Quit"));

    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);


    sendFbButton = new QPushButton(tr("Send Feedback"));
    sendFbButton->setDefault(true);
    sendFbButton->setEnabled(true);

    auto quit2Button = new QPushButton(tr("Quit"));

    auto page2buttonBox = new QDialogButtonBox;
    page2buttonBox->addButton(sendFbButton, QDialogButtonBox::ActionRole);
    page2buttonBox->addButton(quit2Button, QDialogButtonBox::RejectRole);

    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);


    connect(hostCombo, &QComboBox::editTextChanged,
            this, &PlatformClientGUI::enableConnectButton);
    connect(portLineEdit, &QLineEdit::textChanged,
            this, &PlatformClientGUI::enableConnectButton);
    connect(connectButton, SIGNAL(clicked()),
            this, SLOT(serverConnect()));
    connect(submitButton, SIGNAL(clicked()),
            this, SLOT(sendInfo()));
    connect(sendFbButton, SIGNAL(clicked()),
            this, SLOT(sendFeedback()));
    connect(quitButton, &QAbstractButton::clicked,
            this, &QWidget::close);
    connect(quit2Button, &QAbstractButton::clicked,
            this, &QWidget::close);
    connect(this, &PlatformClientGUI::FeedbackSentSignal ,
            this, &QWidget::close);
    connect(tcpSocket, &QIODevice::readyRead,
            this, &PlatformClientGUI::readRecommendation);

    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &PlatformClientGUI::displayError);

    QGridLayout *mainLayout = nullptr;

    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        auto outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        auto outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QGridLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QGridLayout;
    }

    mainLayout->addWidget(serverGroupBox, 0,0,1,4);
    mainLayout->addWidget(statusLabel, 1, 0, 1, 2);
    mainLayout->addWidget(pinfoBox, 2, 0, 1, 4);
    mainLayout->addWidget(panalysisBox, 3, 0, 1, 4);
    mainLayout->addWidget(buttonBox, 4, 0, 1, 4);



    setWindowTitle(QGuiApplication::applicationDisplayName());
    portLineEdit->setFocus();

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    page1Widget->setLayout(mainLayout);

    /*          Page 2                                                                        */
    QVBoxLayout *page2Layout = new QVBoxLayout;
    bookLabel = new QLabel(tr("Book Recommendation: "));
    movieLabel = new QLabel(tr("Movie Recommendation: "));
    quoteLabel = new QLabel(tr("Quote Recommendation: "));
    feedbackLabel = new QLabel(tr("Give us your feedback (score from 1 to 5)."));
    feedbackLabel->setAlignment(Qt::AlignRight);
    feedbackLineEdit = new QLineEdit;
    feedbackLineEdit->setValidator(new QIntValidator(1, 5));
    feedbackLineEdit->setAlignment(Qt::AlignLeft);
    auto recommendationBox = new QGroupBox(tr("Suggested Recommendations"));
    auto vLayout = new QVBoxLayout;
    vLayout->addWidget(bookLabel);
    vLayout->addWidget(movieLabel);
    vLayout->addWidget(quoteLabel);
    vLayout->addStretch(1);
    recommendationBox->setLayout(vLayout);


    auto feedbackBox = new QGroupBox(tr("Feedback!"));
    auto hLayout = new QHBoxLayout;
    hLayout->addWidget(feedbackLabel);
    hLayout->addWidget(feedbackLineEdit);
    hLayout->addStretch(1);
    feedbackBox->setLayout(hLayout);

    page2Layout->addWidget(recommendationBox);
    page2Layout->addWidget(feedbackBox);
    page2Layout->addWidget(page2buttonBox);
    page2Layout->addStretch(1);
    page2Widget->setLayout(page2Layout);

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(page1Widget);
    stackedWidget->addWidget(page2Widget);
    setCentralWidget(stackedWidget);


    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened, this, &PlatformClientGUI::sessionOpened);

        connectButton->setEnabled(false);
        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }
}

void PlatformClientGUI::serverConnect()
{
    connectButton->setEnabled(false);
    tcpSocket->abort();
    tcpSocket->connectToHost(hostCombo->currentText(),
                             portLineEdit->text().toInt());
    if(tcpSocket->isOpen())
    statusLabel->setText("Connected to Server. Please fill your Personal Information and check all statements that apply to you!");
}

QVector<int> PlatformClientGUI::getAnalysisResults()
{
    QVector<int>    analysisResults(5, 0);
    int k = 0;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(checkBoxes[k]->isChecked())
                analysisResults[i]++;
            k++;
        }
    }
    return analysisResults;
}

void PlatformClientGUI::sendInfo()
{
    submitButton->setEnabled(false);

    if(!tcpSocket->isOpen())
    {
        QMessageBox::information(this, tr("Platform Client"),
                                 tr("Socket not opened. Please Connect"));
        submitButton->setEnabled(true);
        return;
    }

    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
    {
        tcpSocket->connectToHost(hostCombo->currentText(),
                                 portLineEdit->text().toInt());
    }

    if(nameLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("Platform Client"),
                                 tr("Please Insert a Name"));
        submitButton->setEnabled(true);
        return;
    }
    if(ageLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("Platform Client"),
                                 tr("Please Insert an Age"));
        submitButton->setEnabled(true);
        return;
    }

    QVector<int> results(5);
    results = getAnalysisResults();

    Client.setName(nameLineEdit->text());
    Client.setAge(ageLineEdit->text().toInt());
    Client.setGender(genderCombo->currentText());
    Client.setOpennessScore(results[0]);
    Client.setConscientiousnessSScore(results[1]);
    Client.setExtraversionScore(results[2]);
    Client.setAgreeablenessScore(results[3]);
    Client.setNeuroticismScore(results[4]);

    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setDevice(tcpSocket);
    out.setVersion(QDataStream::Qt_4_0);
    out<<Client.getName()
       <<QString::number(Client.getAge())
       <<Client.getGender()
       <<QString::number(Client.getOpennessScore())
       <<QString::number(Client.getConscientiousnessSScore())
       <<QString::number(Client.getExtraversionScore())
       <<QString::number(Client.getAgreeablenessScore())
       <<QString::number(Client.getNeuroticismScore());

    tcpSocket->write(block);
    tcpSocket->waitForBytesWritten(10000);

    submitButton->setEnabled(true);

    stackedWidget->setCurrentIndex(1);
    //stackedWidget->currentWidget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //stackedWidget->currentWidget()->adjustSize();
    //stackedWidget->adjustSize();
    //adjustSize();
}

void PlatformClientGUI::sendFeedback()
{
    sendFbButton->setEnabled(false);

    if(!tcpSocket->isOpen())
    {
        QMessageBox::information(this, tr("Platform Client"),
                                 tr("Socket not opened. Please Connect"));
        return;
    }

    if(tcpSocket->state() != QAbstractSocket::ConnectedState)
    {
        tcpSocket->connectToHost(hostCombo->currentText(),
                                 portLineEdit->text().toInt());
    }

    if(feedbackLineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("Platform Client"),
                                 tr("Please add your feedback!"));
        sendFbButton->setEnabled(true);
        return;
    }

    Client.setFeedback(feedbackLineEdit->text().toInt());

    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setDevice(tcpSocket);
    out.setVersion(QDataStream::Qt_4_0);

    out<<QString::number(Client.getFeedback());
    tcpSocket->write(block);
    tcpSocket->waitForBytesWritten(1000);

    sendFbButton->setEnabled(true);

    QMessageBox::information(this, tr("Platform Client"),
                             tr("Feedback Sent successfully! Thank You for your contribution!"));
    emit FeedbackSentSignal();
}

void PlatformClientGUI::readRecommendation()
{
    in.startTransaction();            

    Book RecommendedBook;
    Movie RecommendedMovie;
    Quote RecommendedQuote;
    QString bookTitle, bookDescription, bookTag1Name, bookTag2Name, bookTag3Name,
            movieTitle, movieDescription, movieTag1Name, movieTag2Name, movieTag3Name,
            quoteContent, quoteTag1Name, quoteTag2Name, quoteTag3Name;

    in >> bookTitle >> bookDescription >> bookTag1Name >> bookTag2Name >> bookTag3Name
       >> movieTitle >> movieDescription >> movieTag1Name >> movieTag2Name >> movieTag3Name
       >>quoteContent >> quoteTag1Name >> quoteTag2Name >> quoteTag3Name;

    if (!in.commitTransaction())
        return;

    RecommendedBook.setTitle(bookTitle);
    RecommendedBook.setDescription(bookDescription);
    RecommendedBook.setTag1Name(bookTag1Name);
    RecommendedBook.setTag2Name(bookTag2Name);
    RecommendedBook.setTag3Name(bookTag3Name);

    RecommendedMovie.setTitle(movieTitle);
    RecommendedMovie.setDescription(movieDescription);
    RecommendedMovie.setTag1Name(movieTag1Name);
    RecommendedMovie.setTag2Name(movieTag2Name);
    RecommendedMovie.setTag3Name(movieTag3Name);

    RecommendedQuote.setContent(quoteContent);
    RecommendedQuote.setTag1Name(quoteTag1Name);
    RecommendedQuote.setTag2Name(quoteTag2Name);
    RecommendedQuote.setTag3Name(quoteTag3Name);

    Client.setBookRecommendation(RecommendedBook);
    Client.setMovieRecommendation(RecommendedMovie);
    Client.setQuoteRecommendation(RecommendedQuote);

    movieLabel->setText("\nMovie Recommendation: " + Client.getMovieRecommendation().getTitle()
                        + "\n\n" + Client.getMovieRecommendation().getDescription()
                        + "\n\nTags: " + Client.getMovieRecommendation().getTag1Name()
                        + ", " + Client.getMovieRecommendation().getTag2Name()
                        + ", " + Client.getMovieRecommendation().getTag3Name());

    movieLabel->setWordWrap(true);

    bookLabel->setText("\nBook Recommendation: " + Client.getBookRecommendation().getTitle()
                       + "\n\n" + Client.getBookRecommendation().getDescription()
                       + "\n\nTags: " + Client.getBookRecommendation().getTag1Name()
                       + ", " + Client.getBookRecommendation().getTag2Name()
                       + ", " + Client.getBookRecommendation().getTag3Name());

    bookLabel->setWordWrap(true);

    quoteLabel->setText("\nQuote Recommendation: \n\n" + Client.getQuoteRecommendation().getContent()
                        + "\n\nTags: " + Client.getBookRecommendation().getTag1Name()
                        + ", " + Client.getBookRecommendation().getTag2Name()
                        + ", " + Client.getBookRecommendation().getTag3Name());

    quoteLabel->setWordWrap(true);

}

void PlatformClientGUI::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Platform Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Platform Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Platform Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
        statusLabel->setText("Connection Error. Please try to connect again!");
    }

    connectButton->setEnabled(true);
}

void PlatformClientGUI::enableConnectButton()
{
    connectButton->setEnabled((!networkSession || networkSession->isOpen()) &&
                                 !hostCombo->currentText().isEmpty() &&
                                 !portLineEdit->text().isEmpty());

}

void PlatformClientGUI::sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();

    statusLabel->setText(tr("This examples requires that you run the "
                            "Fortune Server example as well."));

    enableConnectButton();
}

void PlatformClientGUI::createPersonalInfoBox()
{
    pinfoBox = new QGroupBox(tr("Personal Info"));

    QGridLayout *layout = new QGridLayout;

    auto nameLabel = new QLabel(tr("Name:"));
    nameLabel->setAlignment(Qt::AlignRight);
    layout->addWidget(nameLabel,0, 0);
    layout->addWidget(nameLineEdit, 0, 1);

    auto ageLabel = new QLabel(tr("Age:"));
    ageLabel->setAlignment(Qt::AlignRight);
    layout->addWidget(ageLabel,0, 2);
    ageLineEdit->setValidator(new QIntValidator(1, 200, this));
    ageLineEdit->setAlignment(Qt::AlignLeft);
    layout->addWidget(ageLineEdit, 0, 3);

    auto genderLabel = new QLabel(tr("Gender:"));
    genderLabel->setAlignment(Qt::AlignRight);
    layout->addWidget(genderLabel, 0, 4);
    genderCombo->addItem("male");
    genderCombo->addItem("female");
    layout->addWidget(genderCombo, 0, 5);
    for(int i=0;i<6;i++)    layout->setColumnStretch(i,1);
    pinfoBox->setLayout(layout);
}

void PlatformClientGUI::createPersonalityAnalysisBox()
{
    panalysisBox = new QGroupBox(tr("Personality Analysis"));
    QGridLayout *grid = new QGridLayout;

    QGroupBox *Openness = new QGroupBox;
    QVBoxLayout *vbox1 = new QVBoxLayout;

    ocheckBox1 = new QCheckBox(tr("I have excellent ideas."));
    ocheckBox2 = new QCheckBox(tr("I am quick to understand things."));
    ocheckBox3 = new QCheckBox(tr("I use difficult words."));
    ocheckBox4 = new QCheckBox(tr("I am full of ideas."));
    ocheckBox5 = new QCheckBox(tr("I am interested in abstractions."));

    ocheckBox1->setChecked(false);
    ocheckBox2->setChecked(false);
    ocheckBox3->setChecked(false);
    ocheckBox4->setChecked(false);
    ocheckBox5->setChecked(false);

    checkBoxes.push_back(ocheckBox1);
    checkBoxes.push_back(ocheckBox2);
    checkBoxes.push_back(ocheckBox3);
    checkBoxes.push_back(ocheckBox4);
    checkBoxes.push_back(ocheckBox5);

    vbox1->addWidget(ocheckBox1);
    vbox1->addWidget(ocheckBox2);
    vbox1->addWidget(ocheckBox3);
    vbox1->addWidget(ocheckBox4);
    vbox1->addWidget(ocheckBox5);

    Openness->setLayout(vbox1);

    QGroupBox *Conscientiousness = new QGroupBox;
    QVBoxLayout *vbox2 = new QVBoxLayout;

    ccheckBox1 = new QCheckBox(tr("I like order."));
    ccheckBox2 = new QCheckBox(tr("I follow a schedule."));
    ccheckBox3 = new QCheckBox(tr("I am exacting in my work."));
    ccheckBox4 = new QCheckBox(tr("I always am prepared."));
    ccheckBox5 = new QCheckBox(tr("I pay attention to details."));

    ccheckBox1->setChecked(false);
    ccheckBox2->setChecked(false);
    ccheckBox3->setChecked(false);
    ccheckBox4->setChecked(false);
    ccheckBox5->setChecked(false);

    checkBoxes.push_back(ccheckBox1);
    checkBoxes.push_back(ccheckBox2);
    checkBoxes.push_back(ccheckBox3);
    checkBoxes.push_back(ccheckBox4);
    checkBoxes.push_back(ccheckBox5);

    vbox2->addWidget(ccheckBox1);
    vbox2->addWidget(ccheckBox2);
    vbox2->addWidget(ccheckBox3);
    vbox2->addWidget(ccheckBox4);
    vbox2->addWidget(ccheckBox5);

    Conscientiousness->setLayout(vbox2);

    QGroupBox *Extraversion = new QGroupBox;
    QVBoxLayout *vbox3 = new QVBoxLayout;

    echeckBox1 = new QCheckBox(tr("I am the life of the party."));
    echeckBox2 = new QCheckBox(tr("I don't mind being the center of attention."));
    echeckBox3 = new QCheckBox(tr("I feel comfortable around people."));
    echeckBox4 = new QCheckBox(tr("I start conversations."));
    echeckBox5 = new QCheckBox(tr("I talk to a lot of different people at parties."));

    echeckBox1->setChecked(false);
    echeckBox2->setChecked(false);
    echeckBox3->setChecked(false);
    echeckBox4->setChecked(false);
    echeckBox5->setChecked(false);

    checkBoxes.push_back(echeckBox1);
    checkBoxes.push_back(echeckBox2);
    checkBoxes.push_back(echeckBox3);
    checkBoxes.push_back(echeckBox4);
    checkBoxes.push_back(echeckBox5);

    vbox3->addWidget(echeckBox1);
    vbox3->addWidget(echeckBox2);
    vbox3->addWidget(echeckBox3);
    vbox3->addWidget(echeckBox4);
    vbox3->addWidget(echeckBox5);

    Extraversion->setLayout(vbox3);

    QGroupBox *Agreeableness = new QGroupBox;
    QVBoxLayout *vbox4 = new QVBoxLayout;

    acheckBox1 = new QCheckBox(tr("I make people feel at ease."));
    acheckBox2 = new QCheckBox(tr("I feel others' emotions."));
    acheckBox3 = new QCheckBox(tr("I take time out for others."));
    acheckBox4 = new QCheckBox(tr("I have a soft heart."));
    acheckBox5 = new QCheckBox(tr("I am interested in people."));

    acheckBox1->setChecked(false);
    acheckBox2->setChecked(false);
    acheckBox3->setChecked(false);
    acheckBox4->setChecked(false);
    acheckBox5->setChecked(false);

    checkBoxes.push_back(acheckBox1);
    checkBoxes.push_back(acheckBox2);
    checkBoxes.push_back(acheckBox3);
    checkBoxes.push_back(acheckBox4);
    checkBoxes.push_back(acheckBox5);

    vbox4->addWidget(acheckBox1);
    vbox4->addWidget(acheckBox2);
    vbox4->addWidget(acheckBox3);
    vbox4->addWidget(acheckBox4);
    vbox4->addWidget(acheckBox5);

    Agreeableness->setLayout(vbox4);

    QGroupBox *Neuroticism = new QGroupBox;
    QVBoxLayout *vbox5 = new QVBoxLayout;

    ncheckBox1 = new QCheckBox(tr("I get irritated easily."));
    ncheckBox2 = new QCheckBox(tr("I get stressed out easily."));
    ncheckBox3 = new QCheckBox(tr("I get upset easily."));
    ncheckBox4 = new QCheckBox(tr("I have frequent mood swings."));
    ncheckBox5 = new QCheckBox(tr("I worry about things."));

    ncheckBox1->setChecked(false);
    ncheckBox2->setChecked(false);
    ncheckBox3->setChecked(false);
    ncheckBox4->setChecked(false);
    ncheckBox5->setChecked(false);

    checkBoxes.push_back(ncheckBox1);
    checkBoxes.push_back(ncheckBox2);
    checkBoxes.push_back(ncheckBox3);
    checkBoxes.push_back(ncheckBox4);
    checkBoxes.push_back(ncheckBox5);

    vbox5->addWidget(ncheckBox1);
    vbox5->addWidget(ncheckBox2);
    vbox5->addWidget(ncheckBox3);
    vbox5->addWidget(ncheckBox4);
    vbox5->addWidget(ncheckBox5);

    Neuroticism->setLayout(vbox5);

    grid->addWidget(new QLabel(tr("check all boxes that apply to you")),0, 0);
    grid->addWidget(Openness,1,0);
    grid->addWidget(Conscientiousness, 1, 1);
    grid->addWidget(Extraversion,1,2);
    grid->addWidget(Agreeableness, 2,0);
    grid->addWidget(Neuroticism, 2,1);
    panalysisBox->setLayout(grid);
}
