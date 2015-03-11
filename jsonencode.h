#ifndef JSONENCODE_H
#define JSONENCODE_H

#include <QJsonObject>
#include <QJsonArray>
#include <QString>

class JsonEncode
{
public:
    JsonEncode();
    ~JsonEncode();

    bool parser(QString const& arg);
    QString toJsonString();
    void fromArg(QString const& arg);

private:
    //QJsonObject object_;
    QJsonArray array_;
};

#endif // JSONENCODE_H
