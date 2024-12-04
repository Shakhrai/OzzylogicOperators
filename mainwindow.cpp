#include "database.h"
#include "tree_model.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "icon_item_delegate.h"

#include <QTreeView>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , treeView(new QTreeView(this))
    {
        ui->setupUi(this);

        if (!connectToDatabase()) {
            qDebug() << "Database connection failed.";
            return;
        }

        QWidget* centralWidget = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(centralWidget);


        QStandardItemModel* model = createTreeModel();
        if (model) {
            treeView->setModel(model);
            treeView->setTextElideMode(Qt::ElideNone);

            treeView->setItemDelegate(new IconItemDelegate(treeView));



        } else {
            qDebug() << "Failed to create tree model.";
        }

        layout->addWidget(treeView);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }
