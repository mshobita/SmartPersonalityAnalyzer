#include "tag.h"

Tag::Tag()
{

}

Tag::Tag(QString name, QString trait ,bool correlation)
{
    this->Name = name;
    this->Trait = trait;
    this->Correlation = correlation;
}

void Tag::setName(QString name)
{
    this->Name = name;
}

void Tag::setTrait(QString trait)
{
    this->Trait = trait;
}

void Tag::setCorrelation(bool correlation)
{
    this->Correlation = correlation;
}

QString Tag::getName()
{
    return this->Name;
}
QString Tag::getTrait()
{
    return this->Trait;
}
bool Tag::getCorrelation()
{
    return this->Correlation;
}
