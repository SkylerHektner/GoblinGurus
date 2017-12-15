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
    void playGame(int diff);

public:
    explicit difficultyselector(QWidget *parent = 0);
    ~difficultyselector();

private slots:
    void on_PlayButton_clicked();

    void on_difficultyselector_finished(int result);

private:
    Ui::difficultyselector *ui;
};

#endif // DIFFICULTYSELECTOR_H
