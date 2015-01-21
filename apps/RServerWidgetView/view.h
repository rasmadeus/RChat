#ifndef VIEW_H
#define VIEW_H

class QAbstractListModel;
#include <rserver.h>
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
    void makeClientsModel();
    void makeUiBehavior();
    Ui::View *ui;
    RServer rserver;

};

#endif // VIEW_H
