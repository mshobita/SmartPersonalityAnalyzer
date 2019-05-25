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

#ifndef CLIENT_H
#define CLIENT_H

#include <QDataStream>
#include <QTcpSocket>
#include <QMainWindow>
#include <QStackedWidget>

#include "platformclient.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QCheckBox;
class QGroupBox;
class QComboBox;
class QGridLayout;
class QTcpSocket;
class QNetworkSession;
template <class T> class QVector;

class QTextEdit;
QT_END_NAMESPACE

class PlatformClientGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlatformClientGUI(QWidget *parent = nullptr);

private slots:
    void readRecommendation();
    void sendInfo();
    void sendFeedback();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableConnectButton();
    void sessionOpened();
    void serverConnect();

signals:
     void FeedbackSentSignal();

private:
    PlatformClient Client;
    QComboBox *hostCombo = nullptr;
    QLineEdit *portLineEdit = nullptr;
    QLabel *statusLabel = nullptr;
    QPushButton *connectButton = nullptr;
    QPushButton *submitButton = nullptr;
    QLineEdit *nameLineEdit;
    QComboBox *genderCombo = nullptr;
    QLineEdit *ageLineEdit= nullptr;
    QGroupBox *pinfoBox= nullptr;
    QGroupBox *panalysisBox= nullptr;
    QLabel *bookLabel = nullptr;
    QLabel *movieLabel = nullptr;
    QLabel *quoteLabel = nullptr;
    QLabel *feedbackLabel = nullptr;
    QLineEdit *feedbackLineEdit = nullptr;
    QPushButton *sendFbButton = nullptr;
    QWidget *page1Widget = nullptr;
    QWidget *page2Widget = nullptr;
    QStackedWidget *stackedWidget;

    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString currentFortune;

    QNetworkSession *networkSession = nullptr;


    QTextEdit *debugEdit;

    void createServerBox();
    void createPersonalInfoBox();
    void createPersonalityAnalysisBox();

    QVector<int> getAnalysisResults();

    QVector< QCheckBox* > checkBoxes;

    QCheckBox *ocheckBox1 = nullptr;
    QCheckBox *ocheckBox2 = nullptr;
    QCheckBox *ocheckBox3 = nullptr;
    QCheckBox *ocheckBox4 = nullptr;
    QCheckBox *ocheckBox5 = nullptr;

    QCheckBox *ccheckBox1 = nullptr;
    QCheckBox *ccheckBox2 = nullptr;
    QCheckBox *ccheckBox3 = nullptr;
    QCheckBox *ccheckBox4 = nullptr;
    QCheckBox *ccheckBox5 = nullptr;

    QCheckBox *echeckBox1 = nullptr;
    QCheckBox *echeckBox2 = nullptr;
    QCheckBox *echeckBox3 = nullptr;
    QCheckBox *echeckBox4 = nullptr;
    QCheckBox *echeckBox5 = nullptr;

    QCheckBox *acheckBox1 = nullptr;
    QCheckBox *acheckBox2 = nullptr;
    QCheckBox *acheckBox3 = nullptr;
    QCheckBox *acheckBox4 = nullptr;
    QCheckBox *acheckBox5 = nullptr;

    QCheckBox *ncheckBox1 = nullptr;
    QCheckBox *ncheckBox2 = nullptr;
    QCheckBox *ncheckBox3 = nullptr;
    QCheckBox *ncheckBox4 = nullptr;
    QCheckBox *ncheckBox5 = nullptr;
};

#endif
