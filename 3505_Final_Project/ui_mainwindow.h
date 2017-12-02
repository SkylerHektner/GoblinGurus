/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *MapLabel;
    QLabel *PlayerLabel;
    QLabel *GoblinLabel1;
    QLabel *GoblinLabel2;
    QLabel *GoblinLabel3;
    QLabel *GoblinLabel4;
    QLabel *GoblinLabel5;
    QLabel *ParchmentLabel;
    QLabel *ParchmentTextLabel;
    QLineEdit *AnswerLineEdit;
    QPushButton *SubmitAnswerButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MapLabel = new QLabel(centralWidget);
        MapLabel->setObjectName(QStringLiteral("MapLabel"));
        MapLabel->setGeometry(QRect(20, 20, 351, 201));
        PlayerLabel = new QLabel(centralWidget);
        PlayerLabel->setObjectName(QStringLiteral("PlayerLabel"));
        PlayerLabel->setGeometry(QRect(160, 70, 55, 16));
        GoblinLabel1 = new QLabel(centralWidget);
        GoblinLabel1->setObjectName(QStringLiteral("GoblinLabel1"));
        GoblinLabel1->setGeometry(QRect(10, 230, 55, 16));
        GoblinLabel2 = new QLabel(centralWidget);
        GoblinLabel2->setObjectName(QStringLiteral("GoblinLabel2"));
        GoblinLabel2->setGeometry(QRect(70, 230, 55, 16));
        GoblinLabel3 = new QLabel(centralWidget);
        GoblinLabel3->setObjectName(QStringLiteral("GoblinLabel3"));
        GoblinLabel3->setGeometry(QRect(130, 230, 55, 16));
        GoblinLabel4 = new QLabel(centralWidget);
        GoblinLabel4->setObjectName(QStringLiteral("GoblinLabel4"));
        GoblinLabel4->setGeometry(QRect(190, 230, 55, 16));
        GoblinLabel5 = new QLabel(centralWidget);
        GoblinLabel5->setObjectName(QStringLiteral("GoblinLabel5"));
        GoblinLabel5->setGeometry(QRect(250, 230, 55, 16));
        ParchmentLabel = new QLabel(centralWidget);
        ParchmentLabel->setObjectName(QStringLiteral("ParchmentLabel"));
        ParchmentLabel->setGeometry(QRect(330, 10, 55, 16));
        ParchmentTextLabel = new QLabel(centralWidget);
        ParchmentTextLabel->setObjectName(QStringLiteral("ParchmentTextLabel"));
        ParchmentTextLabel->setGeometry(QRect(330, 40, 55, 16));
        ParchmentTextLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        ParchmentTextLabel->setWordWrap(true);
        AnswerLineEdit = new QLineEdit(centralWidget);
        AnswerLineEdit->setObjectName(QStringLiteral("AnswerLineEdit"));
        AnswerLineEdit->setGeometry(QRect(280, 70, 113, 22));
        SubmitAnswerButton = new QPushButton(centralWidget);
        SubmitAnswerButton->setObjectName(QStringLiteral("SubmitAnswerButton"));
        SubmitAnswerButton->setGeometry(QRect(272, 100, 121, 28));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 26));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        MapLabel->setText(QString());
        PlayerLabel->setText(QString());
        GoblinLabel1->setText(QString());
        GoblinLabel2->setText(QString());
        GoblinLabel3->setText(QString());
        GoblinLabel4->setText(QString());
        GoblinLabel5->setText(QString());
        ParchmentLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        ParchmentTextLabel->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        AnswerLineEdit->setPlaceholderText(QApplication::translate("MainWindow", "Answer...", Q_NULLPTR));
        SubmitAnswerButton->setText(QApplication::translate("MainWindow", "Submit Answer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
