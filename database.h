#ifndef DATABASE_H
#define DATABASE_H

#include <QList>
#include <QString>
#include <QVariantMap>

bool connectToDatabase();

QList<QVariantMap> getCountryData();
QList<QVariantMap> getOperatorData();



#endif // DATABASE_H
