/********************************************************************************
** Form generated from reading UI file 'startmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENU_H
#define UI_STARTMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_startmenu
{
public:
    QLabel *label;
    QSlider *difficultySlider;
    QLabel *difficultyLabel;
    QPushButton *play;

    void setupUi(QWidget *startmenu)
    {
        if (startmenu->objectName().isEmpty())
            startmenu->setObjectName(QStringLiteral("startmenu"));
        startmenu->resize(400, 300);
        label = new QLabel(startmenu);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 130, 47, 13));
        difficultySlider = new QSlider(startmenu);
        difficultySlider->setObjectName(QStringLiteral("difficultySlider"));
        difficultySlider->setGeometry(QRect(140, 90, 101, 31));
        difficultySlider->setMinimum(1);
        difficultySlider->setOrientation(Qt::Horizontal);
        difficultyLabel = new QLabel(startmenu);
        difficultyLabel->setObjectName(QStringLiteral("difficultyLabel"));
        difficultyLabel->setGeometry(QRect(190, 150, 31, 20));
        play = new QPushButton(startmenu);
        play->setObjectName(QStringLiteral("play"));
        play->setGeometry(QRect(150, 190, 80, 21));

        retranslateUi(startmenu);

        QMetaObject::connectSlotsByName(startmenu);
    } // setupUi

    void retranslateUi(QWidget *startmenu)
    {
        startmenu->setWindowTitle(QApplication::translate("startmenu", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("startmenu", "Difficulty:", Q_NULLPTR));
        difficultyLabel->setText(QApplication::translate("startmenu", "1", Q_NULLPTR));
        play->setText(QApplication::translate("startmenu", "Play", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class startmenu: public Ui_startmenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENU_H
