#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);
    rserver.setPort(ui->sbPort->value());
    makeClientsModel();
    makeUiBehavior();
}

View::~View()
{
    delete ui;
}

#include <clientsmodel.h>
void View::makeClientsModel()
{
    ClientsModel* clientsModel = rserver.makeListModel(ui->clientsList);
    connect(
        ui->pbDisconnectOne,
        &QPushButton::clicked,
        [this, clientsModel](){clientsModel->removeOne(ui->clientsList->currentIndex());}
    );
    ui->clientsList->setModel(clientsModel);
}

void View::makeUiBehavior()
{
    rserver.connect(
        ui->pbStartServer,
        SIGNAL(clicked()),
        SLOT(start())
    );
    rserver.connect(
        ui->pbCloseServer,
        SIGNAL(clicked()),
        SLOT(stop())
    );
    connect(
        ui->sbPort,
        static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [this](int value){ rserver.setPort(value); }
    );
    rserver.connect(
        ui->pbDisconnectAll,
        SIGNAL(clicked()),
        SLOT(disconnectAll())
    );
    connect(
        ui->leMsg,
        &QLineEdit::returnPressed,
        [this](){
            rserver.sayAll(tr("<Server> ") + ui->leMsg->text());
            ui->leMsg->clear();
        }
    );
}

