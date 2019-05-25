#include "movie.h"

Movie::Movie()
{

}
Movie::Movie(QString title, QString description, int tag1Id, int tag2Id, int tag3Id)
{
    this->Title = title;
    this->Description = description;
    this->Tag1Id = tag1Id;
    this->Tag2Id = tag2Id;
    this->Tag3Id = tag3Id;
}

void Movie::setTitle(QString title)
{
    this->Title = title;
}

void Movie::setDescription(QString description)
{
    this->Description = description;
}

void Movie::setTag1Id(int tag1Id)
{
    this->Tag1Id = tag1Id;
}

void Movie::setTag2Id(int tag2Id)
{
    this->Tag2Id = tag2Id;
}

void Movie::setTag3Id(int tag3Id)
{
    this->Tag3Id = tag3Id;
}

void Movie::setTag1Name(QString name1)
{
    this->Tag1Name = name1;
}

void Movie::setTag2Name(QString name2)
{
    this->Tag2Name = name2;
}

void Movie::setTag3Name(QString name3)
{
    this->Tag3Name = name3;
}

QString Movie::getTitle()
{
    return this->Title;
}

QString Movie::getDescription()
{
    return this->Description;
}


int Movie::getTag1Id()
{
    return this->Tag1Id;
}

int Movie::getTag2Id()
{
    return this->Tag2Id;
}

int Movie::getTag3Id()
{
    return this->Tag3Id;
}


QString Movie::getTag1Name()
{
    return this->Tag1Name;
}

QString Movie::getTag2Name()
{
    return this->Tag2Name;
}

QString Movie::getTag3Name()
{
    return this->Tag3Name;
}
