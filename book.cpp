#include "book.h"

Book::Book()
{

}
Book::Book(QString title, QString description, int tag1Id, int tag2Id, int tag3Id)
{
    this->Title = title;
    this->Description = description;
    this->Tag1Id = tag1Id;
    this->Tag2Id = tag2Id;
    this->Tag3Id = tag3Id;
}

void Book::setTitle(QString title)
{
    this->Title = title;
}

void Book::setDescription(QString description)
{
    this->Description = description;
}

void Book::setTag1Id(int tag1Id)
{
    this->Tag1Id = tag1Id;
}

void Book::setTag2Id(int tag2Id)
{
    this->Tag2Id = tag2Id;
}

void Book::setTag3Id(int tag3Id)
{
    this->Tag3Id = tag3Id;
}

void Book::setTag1Name(QString name1)
{
    this->Tag1Name = name1;
}

void Book::setTag2Name(QString name2)
{
    this->Tag2Name = name2;
}

void Book::setTag3Name(QString name3)
{
    this->Tag3Name = name3;
}

QString Book::getTitle()
{
    return this->Title;
}

QString Book::getDescription()
{
    return this->Description;
}

int Book::getTag1Id()
{
    return this->Tag1Id;
}

int Book::getTag2Id()
{
    return this->Tag2Id;
}

int Book::getTag3Id()
{
    return this->Tag3Id;
}

QString Book::getTag1Name()
{
    return this->Tag1Name;
}

QString Book::getTag2Name()
{
    return this->Tag2Name;
}

QString Book::getTag3Name()
{
    return this->Tag3Name;
}
