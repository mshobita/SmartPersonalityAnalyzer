#include "platformclient.h"

PlatformClient::PlatformClient()
{

}

PlatformClient::PlatformClient(QString name, int age, QString gender, int oScore, int cScore, int eScore, int aScore, int nScore)
{
    this->Name = name;
    this->Age = age;
    this->Gender = gender;
    this->OpennessScore = oScore;
    this->ConscientiousnessScore = cScore;
    this->ExtraversionScore = eScore;
    this->AgreeablenessScore = aScore;
    this->NeuroticismScore = nScore;
}

void PlatformClient::setId(int id)
{
    this->Id = id;
}

void PlatformClient::setName(QString name)
{
    this->Name = name;
}

void PlatformClient::setAge(int age)
{
    this->Age = age;
}

void PlatformClient::setGender(QString gender)
{
    this->Gender = gender;
}

void PlatformClient::setOpennessScore(int oScore)
{
    this->OpennessScore = oScore;
}

void PlatformClient::setConscientiousnessSScore(int cScore)
{
    this->ConscientiousnessScore = cScore;
}

void PlatformClient::setExtraversionScore(int eScore)
{
    this->ExtraversionScore = eScore;
}

void PlatformClient::setAgreeablenessScore(int aScore)
{
    this->AgreeablenessScore = aScore;
}

void PlatformClient::setNeuroticismScore(int nScore)
{
    this->NeuroticismScore = nScore;
}

void PlatformClient::setBookRecommendation(Book book)
{
    this->BookRecommendation = book;
}

void PlatformClient::setMovieRecommendation(Movie movie)
{
    this->MovieRecommendation = movie;
}

void PlatformClient::setQuoteRecommendation(Quote quote)
{
    this->QuoteRecommendation = quote;
}
void PlatformClient::setFeedback(int feedback)
{
    this->Feedback = feedback;
}

int PlatformClient::getId()
{
    return this->Id;
}

QString PlatformClient::getName()
{
    return this->Name;
}

int PlatformClient::getAge()
{
    return this->Age;
}

QString PlatformClient::getGender()
{
    return this->Gender;
}

int PlatformClient::getOpennessScore()
{
    return this->OpennessScore;
}

int PlatformClient::getConscientiousnessSScore()
{
    return this->ConscientiousnessScore;
}

int PlatformClient::getExtraversionScore()
{
    return this->ExtraversionScore;
}

int PlatformClient::getAgreeablenessScore()
{
    return this->AgreeablenessScore;
}

int PlatformClient::getNeuroticismScore()
{
    return this->NeuroticismScore;
}

Book PlatformClient::getBookRecommendation()
{
    return this->BookRecommendation;
}

Movie PlatformClient::getMovieRecommendation()
{
    return this->MovieRecommendation;
}
Quote PlatformClient::getQuoteRecommendation()
{
    return this->QuoteRecommendation;
}
int PlatformClient::getFeedback()
{
    return this->Feedback;
}
