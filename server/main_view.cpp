#include "main_view.h"

MainView::MainView()
    : QMainWindow{}
    , work{new boost::asio::io_service::work{io_service}}
    , io_service_runner{[this]{ io_service.run(); }}
    , server{io_service, 3001}
{
    ui.setupUi(this);
}

MainView::~MainView()
{
    work.reset();
    io_service_runner.join();
}
