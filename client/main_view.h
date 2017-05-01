#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "client.h"
#include "ui_main_view.h"


class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView();
    ~MainView();

private:
    void connect_to_server();
    void disconnect_from_server();
    void show_info(const QString& msg);
    void show_error(const QString& msg);
    void write_msg();

private:
    Ui::MainView ui;
    boost::asio::io_service io_service;
    std::unique_ptr<boost::asio::io_service::work> work;
    std::thread io_service_runner;
    Client client;
    QStateMachine machine;
    QState connectedState;
    QState disconnectedState;
};

#endif // MAIN_VIEW_H
