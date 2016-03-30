#ifndef ACP_H
#define ACP_H

#include <QVector>
#include <QString>
#include <QRegExp>

#include <QDebug>

class ParseRule
{
public:
    ParseRule()
    {

    }

    ParseRule( QString name, QRegExp rule )
    {
        this->name = name;
        this->rule = rule;
    }

    ParseRule( QString name, QString rule )
    {
        this->name = name;
        this->rule = QRegExp(rule);
    }

public:
    QString name;
    QRegExp rule;
};

class ACP
{
public:
    ACP();
    QVector<QString> parse( const QString& text );

private:
    QVector<ParseRule> rules;
};

#endif // ACP_H
