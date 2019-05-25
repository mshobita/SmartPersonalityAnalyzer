#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include "tag.h"
class Book
{

private:
    QString Title;
    QString Description;
    int Tag1Id;
    int Tag2Id;
    int Tag3Id;
    QString Tag1Name;
    QString Tag2Name;
    QString Tag3Name;

public:
    Book();
    Book(QString title, QString description, int tag1Id, int tag2Id, int tag3Id);
    void setTitle(QString title);
    void setDescription(QString description);
    void setTag1Id(int tag1Id);
    void setTag2Id(int tag2Id);
    void setTag3Id(int tag3Id);
    void setTag1Name(QString name1);
    void setTag2Name(QString name2);
    void setTag3Name(QString name3);
    QString getTitle();
    QString getDescription();
    int getTag1Id();
    int getTag2Id();
    int getTag3Id();
    QString getTag1Name();
    QString getTag2Name();
    QString getTag3Name();
};

#endif // BOOK_H
