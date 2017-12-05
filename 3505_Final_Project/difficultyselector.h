#ifndef DIFFICULTYSELECTOR_H
#define DIFFICULTYSELECTOR_H

#include <QDialog>

namespace Ui {
class difficultyselector;
}

class difficultyselector : public QDialog
{
    Q_OBJECT

signals:
    playGame(int diff);

public:
    explicit difficultyselector(QWidget *parent = 0);
    ~difficultyselector();

private slots:
    void on_PlayButton_clicked();

private:
    Ui::difficultyselector *ui;
};

#endif // DIFFICULTYSELECTOR_H
