#include "tree_model.h"
#include "database.h"

#include <QIcon>
#include <QFile>
#include <QStandardItem>
#include <QStandardItemModel>


QStandardItemModel* createTreeModel() {
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels({""});

    QList<QVariantMap> countryData = getCountryData();
    QList<QVariantMap> operatorData = getOperatorData();

    QMap<QString, QStandardItem*> countryItems;


    QString iconPath = ":/icons/icons/";


    for (const QVariantMap& country : countryData) {
        QString countryName = country["country_name"].toString();
        QString countryCode = country["country_code"].toString();
        QString countryMcc = country["country_mcc"].toString();


        QString flagPath = iconPath + countryCode + ".png";
        QIcon flagIcon;
        if (QFile::exists(flagPath)) {
            flagIcon = QIcon(flagPath);
        }


        if (!countryItems.contains(countryName)) {
            QStandardItem* countryItem = new QStandardItem(countryName + " (" + countryCode + ")");
            if (!flagIcon.isNull()) {
                countryItem->setData(flagIcon, Qt::DecorationRole);
            }
            countryItems[countryName] = countryItem;
            model->appendRow(countryItem);
        }
    }


    for (const QVariantMap& operatorRow : operatorData) {
        QString operatorName = operatorRow["operator_name"].toString();
        QString mcc = operatorRow["operator_mcc"].toString();
        QString mnc = operatorRow["operator_mnc"].toString();
        QString mccMnc = mcc + " - " + mnc;


        QString operatorIconPath = iconPath + mcc + "_" + mnc + ".png";
        QIcon operatorIcon;
        if (QFile::exists(operatorIconPath)) {
            operatorIcon = QIcon(operatorIconPath);
        }


        for (const QVariantMap& country : countryData) {
            QString countryMcc = country["country_mcc"].toString();
            QString countryName = country["country_name"].toString();


            if (mcc == countryMcc) {
                QStandardItem* operatorItem = new QStandardItem(operatorName + " (" + mccMnc + ")");
                if (!operatorIcon.isNull()) {
                    operatorItem->setData(operatorIcon, Qt::DecorationRole);
                }
                countryItems[countryName]->appendRow(operatorItem);
            }
        }
    }

    return model;
}
