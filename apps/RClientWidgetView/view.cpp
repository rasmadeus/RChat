#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);
    ui->leSay->installEventFilter(this);
    makeConnections();
}

View::~View()
{
    delete ui;
}

void View::makeConnections()
{
    rclient.connect(
        ui->pbConnect,
        &QPushButton::clicked,
        [this] () {
            const QString address = ui->leAddress->text();
            const quint16 port = ui->sbPort->value();
            rclient.connectToHost(address, port);
        }
    );
    rclient.connect(
       ui->pbDisconnect,
       SIGNAL(clicked()),
       SLOT(disconnectFromHost())
    );
    ui->teConversation->connect(
       &rclient,
       &RClient::msgCame,
       [this](const QString& msg){ui->teConversation->append(msg);}
    );
    rclient.connect(
        ui->leSay,
        &QLineEdit::returnPressed,
        [this](){rclient.sayToHost(ui->leSay->text());}
    );
}

