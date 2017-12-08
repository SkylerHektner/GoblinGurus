/********************************************************************************
** Form generated from reading UI file 'difficultyselector.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIFFICULTYSELECTOR_H
#define UI_DIFFICULTYSELECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_difficultyselector
{
public:
    QLabel *label;
    QSpinBox *difficultyBox;
    QPushButton *PlayButton;

    void setupUi(QDialog *difficultyselector)
    {
        if (difficultyselector->objectName().isEmpty())
            difficultyselector->setObjectName(QStringLiteral("difficultyselector"));
        difficultyselector->resize(400, 300);
        label = new QLabel(difficultyselector);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 120, 101, 20));
        difficultyBox = new QSpinBox(difficultyselector);
        difficultyBox->setObjectName(QStringLiteral("difficultyBox"));
        difficultyBox->setGeometry(QRect(180, 150, 43, 22));
        difficultyBox->setMinimum(1);
        difficultyBox->setMaximum(3);
        PlayButton = new QPushButton(difficultyselector);
        PlayButton->setObjectName(QStringLiteral("PlayButton"));
        PlayButton->setGeometry(QRect(160, 210, 80, 21));

        retranslateUi(difficultyselector);

        QMetaObject::connectSlotsByName(difficultyselector);
    } // setupUi

    void retranslateUi(QDialog *difficultyselector)
    {
        difficultyselector->setWindowTitle(QApplication::translate("difficultyselector", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("difficultyselector", "Select Your Difficulty", Q_NULLPTR));
        PlayButton->setText(QApplication::translate("difficultyselector", "Play", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class difficultyselector: public Ui_difficultyselector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIFFICULTYSELECTOR_H
