#include "main_view.h"


MainView::MainView()
    : QMainWindow{}
    , work{new boost::asio::io_service::work{io_service}}
    , io_service_runner{[this]{ io_service.run(); }}
    , client{io_service}
{
    ui.setupUi(this);

    connect(&client, &Client::info, this, &MainView::show_info);
    connect(&client, &Client::error, this, &MainView::show_error);
    connect(ui.connectButton, &QPushButton::clicked, this, &MainView::connect_to_server);
    connect(ui.disconnectButton, &QPushButton::clicked, this, &MainView::disconnect_from_server);

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
    client.connect(ui.serverLineEdit->text().toStdString(), std::to_string(ui.portSpinBox->value()));
}

void MainView::disconnect_from_server()
{
    client.disconnect();
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
