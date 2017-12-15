#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>

namespace Ui {
class startmenu;
}

class startmenu : public QWidget
{
    Q_OBJECT

public:
    explicit startmenu(QWidget *parent = 0);
    ~startmenu();

private:
    Ui::startmenu *ui;
};

#endif // STARTMENU_H
