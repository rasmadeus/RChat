#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "ui_main_view.h"
#include "server.h"


class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView();
    ~MainView();

private:
    Ui::MainView ui;
    boost::asio::io_service io_service;
    std::unique_ptr<boost::asio::io_service::work> work;
    std::thread io_service_runner;
    Server server;
};

#endif // MAIN_VIEW_H
