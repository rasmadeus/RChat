#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "ui_main_view.h"

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView();

private:
    Ui::MainView ui;
};

#endif // MAIN_VIEW_H
