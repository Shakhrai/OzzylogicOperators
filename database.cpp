#include "database.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QCoreApplication>

bool connectToDatabase()
{
    QString dbPath = QCoreApplication::applicationDirPath() + "/system.db";
    QSqlDatabase db = QSqlDatabase ::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if(!db.open())
    {
        qDebug()<<"Database connection failed"<<db.lastError().text();
        return false;
    }




    qDebug() << "Using database path:" << dbPath;

    return true;
}
QList<QVariantMap> countryOperatorData()
{
    QList<QVariantMap> data;
    QSqlQuery query;

    if(!query.exec(
                "SELECT countries.name AS country_name, "
                "       countries.code AS country_code, "
                "       countries.mcc AS countries_mcc, "
                "       operators.name AS operator_name, "
                "       operators.mcc AS operator_mcc, "
                "       operators.mnc AS operator_mnc "
                "FROM countries "
                "LEFT JOIN operators ON countries.code = operators.mcc"
            ))
    {
        qDebug()<<"Select query error"<<query.lastError().text();
    }
    while(query.next())
    {
        QVariantMap row;
        row["country_name"]     =   query.value("country_name").toString();
        row["country_code"]     =   query.value("country_code").toString();
        row["countries_mcc"]     =   query.value("countries_mcc").toString();
        row["operator_name"]     =   query.value("operator_name").toString();
        row["operator_mcc"]     =   query.value("operator_mcc").toString();
        row["operator_mnc"]     =   query.value("operator_mnc").toString();

        data.append(row);
    }

    return data;
}
QList<QVariantMap> getCountryData()
{
    QList<QVariantMap> data;
    QSqlQuery query;

    if(!query.exec(
            "SELECT name AS country_name, code AS country_code, mcc AS country_mcc FROM countries"
            ))
    {
        qDebug()<<"Select country query error"<<query.lastError().text();
    }

    while (query.next()) {
        QVariantMap row;
        row["country_name"] = query.value("country_name").toString();
        row["country_code"] = query.value("country_code").toString();
        row["country_mcc"] = query.value("country_mcc").toString();
        data.append(row);
    }
    return data;

}

QList<QVariantMap> getOperatorData()
{
    QList<QVariantMap> data;
    QSqlQuery query;

    if(!query.exec(
           "SELECT name AS operator_name, mcc AS operator_mcc, mnc AS operator_mnc FROM operators"
            ))
    {
        qDebug()<<"Select country query error"<<query.lastError().text();
    }

    while (query.next()) {
        QVariantMap row;
        row["operator_name"] = query.value("operator_name").toString();
        row["operator_mcc"] = query.value("operator_mcc").toString();
        row["operator_mnc"] = query.value("operator_mnc").toString();
        data.append(row);
    }
    return data;

}
