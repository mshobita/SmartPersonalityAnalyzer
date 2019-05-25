#ifndef TAG_H
#define TAG_H

#include <QObject>

class Tag
{

private:
    QString Name;
    QString Trait;
    bool Correlation;
public:
    Tag();
    Tag(QString name, QString trait ,bool Correlation);
    void setName(QString name);
    void setTrait(QString trait);
    void setCorrelation(bool correlation);
    QString getName();
    QString getTrait();
    bool getCorrelation();
};

#endif // TAG_H
