#ifndef PLATFORMCLIENT_H
#define PLATFORMCLIENT_H

#include <QObject>
#include "book.h"
#include "movie.h"
#include "quote.h"

class PlatformClient
{

private:
    int Id;
    QString Name;
    int Age;
    QString Gender;
    int OpennessScore;
    int ConscientiousnessScore;
    int ExtraversionScore;
    int AgreeablenessScore;
    int NeuroticismScore;
    Book BookRecommendation;
    Movie MovieRecommendation;
    Quote QuoteRecommendation;
    int Feedback;

public:
    PlatformClient();
    PlatformClient(QString name, int age, QString gender, int oScore, int cScore, int eScore, int aScore, int nScore);
    void setId(int id);
    void setName(QString name);
    void setAge(int age);
    void setGender(QString gender);
    void setOpennessScore(int oScore);
    void setConscientiousnessSScore(int cScore);
    void setExtraversionScore(int eScore);
    void setAgreeablenessScore(int aScore);
    void setNeuroticismScore(int nScore);
    void setBookRecommendation(Book book);
    void setMovieRecommendation(Movie movie);
    void setQuoteRecommendation(Quote quote);
    void setFeedback(int feedback);

    int getId();
    QString getName();
    int getAge();
    QString getGender();
    int getOpennessScore();
    int getConscientiousnessSScore();
    int getExtraversionScore();
    int getAgreeablenessScore();
    int getNeuroticismScore();
    Book getBookRecommendation();
    Movie getMovieRecommendation();
    Quote getQuoteRecommendation();
    int getFeedback();
};

#endif // PLATFORMCLIENT_H
