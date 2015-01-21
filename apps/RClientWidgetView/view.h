#ifndef VIEW_H
#define VIEW_H

#include <QDialog>
#include <rclient.h>

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
    void makeConnections();
    Ui::View *ui;
    RClient rclient;
};

#endif // VIEW_H
