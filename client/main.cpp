#include "main_view.h"


int main(int argc, char* argv[])
{
    QApplication client_app{argc, argv};
    MainView mainView;
    mainView.show();
    return client_app.exec();
}
