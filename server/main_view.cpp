#include "main_view.h"

MainView::MainView()
    : QMainWindow{}
    , work{new boost::asio::io_service::work{io_service}}
    , io_service_runner{[this]{ io_service.run(); }}
    , server{io_service, 3001}
{
    ui.setupUi(this);
    connect(&server, &Server::error, this, &MainView::show_error);
    connect(&server, &Server::info, this, &MainView::show_info);
}

MainView::~MainView()
{
    work.reset();
    io_service_runner.join();
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
