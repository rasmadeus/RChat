#include "main_view.h"


MainView::MainView()
    : QMainWindow{}
    , work{new boost::asio::io_service::work{io_service}}
    , io_service_runner{[this]{ io_service.run(); }}
    , client{io_service}
{
    ui.setupUi(this);

    connect(ui.connectButton, &QPushButton::clicked, this, &MainView::connect_to_server);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &MainView::disconnect_from_server);
    connect(ui.msg, &QLineEdit::returnPressed, this, &MainView::write_msg);
    connect(&client, &Client::info, this, &MainView::show_info);

    connectedState.assignProperty(ui.connectButton, "visible", "false");
    connectedState.assignProperty(ui.disconnectButton, "visible", "true");
    connectedState.addTransition(ui.disconnectButton, &QPushButton::clicked, &disconnectedState);

    disconnectedState.assignProperty(ui.connectButton, "visible", "true");
    disconnectedState.assignProperty(ui.disconnectButton, "visible", "false");
    disconnectedState.addTransition(ui.connectButton, &QPushButton::clicked, &connectedState);

    machine.addState(&connectedState);
    machine.addState(&disconnectedState);
    machine.setInitialState(&disconnectedState);
    machine.start();
}

MainView::~MainView()
{
    disconnect_from_server();
    work.reset();
    io_service_runner.join();
}

void MainView::connect_to_server()
{
    client.open(ui.serverLineEdit->text().toStdString(), std::to_string(ui.portSpinBox->value()));
}

void MainView::disconnect_from_server()
{
    client.close();
}

void MainView::show_info(const QString& msg)
{
    static const QString html{"<font color=\"green\">%1</font>"};
    ui.log->append(html.arg(msg));
}

void MainView::show_error(const QString& msg)
{
    static const QString html{"<font color=\"red\">%1</font>"};
    ui.log->append(html.arg(msg));
}

void MainView::write_msg()
{
    chat_message chat_msg;
    chat_msg.body_length(ui.msg->text().length());
    std::memcpy(chat_msg.body(), ui.msg->text().toStdString().c_str(), chat_msg.body_length());
    chat_msg.encode_header();
    client.write(chat_msg);
    ui.msg->clear();
}
