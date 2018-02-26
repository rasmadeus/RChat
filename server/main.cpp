#include "main_view.h"
#include "server.h"


int main(int argc, char* argv[])
{
    QApplication::setDesktopSettingsAware(false);
    QApplication app{ argc, argv };
    MainView mainView;
    mainView.show();

    boost::asio::io_context ioContext;
    Server server{ ioContext, 1111 };
    std::thread thread{[&ioContext]{ ioContext.run(); }};
    thread.join();

    return app.exec();
}
