#include "view.h"
#include "ui_view.h"


#include <QHostAddress>
View::View(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::View),
    host(this)
{
    ui->setupUi(this);
    connect(
        ui->actionGenerate,
        &QPushButton::clicked,
        [this](){host.generateClients(ui->clientsCount->value());}
    );
    ui->serverAnswer->connect(
        &host,
        SIGNAL(newDataCame(QString)),
        SLOT(appendPlainText(QString))
    );
    host.connect(
        ui->actionKill,
        SIGNAL(clicked()),
        SLOT(killAllClients())
    );
    host.connect(
        ui->address,
        SIGNAL(textChanged(QString)),
        SLOT(setAddress(QString))
    );
    host.connect(
        ui->port,
        SIGNAL(valueChanged(int)),
        SLOT(setPort(int))
    );

}

View::~View()
{
    delete ui;
}

