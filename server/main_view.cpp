#include "main_view.h"

MainView::MainView()
    : QMainWindow{ nullptr }
{
    _ui.setupUi(this);

    connect(_ui.startServerButton, &QPushButton::clicked, this, &MainView::startServer);
    connect(_ui.stopServerButton, &QPushButton::clicked, this, &MainView::stopServer);
}

void MainView::startServer()
{

}

void MainView::stopServer()
{

}
