#ifndef VIEW_H
#define VIEW_H

#include "host.h"
#include <QDialog>

namespace Ui {
class View;
}

class View : public QDialog
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    ~View();
private:
    Ui::View* ui;
    Host host;
};

#endif // VIEW_H
