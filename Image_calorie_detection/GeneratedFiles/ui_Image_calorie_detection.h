/********************************************************************************
** Form generated from reading UI file 'Image_calorie_detection.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGE_CALORIE_DETECTION_H
#define UI_IMAGE_CALORIE_DETECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Image_calorie_detectionClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Image_calorie_detectionClass)
    {
        if (Image_calorie_detectionClass->objectName().isEmpty())
            Image_calorie_detectionClass->setObjectName(QStringLiteral("Image_calorie_detectionClass"));
        Image_calorie_detectionClass->resize(622, 481);
        centralWidget = new QWidget(Image_calorie_detectionClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(250, 240, 131, 71));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 340, 54, 12));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 340, 331, 71));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(210, 41, 361, 181));
        Image_calorie_detectionClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Image_calorie_detectionClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 622, 23));
        Image_calorie_detectionClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Image_calorie_detectionClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Image_calorie_detectionClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Image_calorie_detectionClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Image_calorie_detectionClass->setStatusBar(statusBar);

        retranslateUi(Image_calorie_detectionClass);
        QObject::connect(pushButton, SIGNAL(clicked()), Image_calorie_detectionClass, SLOT(toGetCalorie()));

        QMetaObject::connectSlotsByName(Image_calorie_detectionClass);
    } // setupUi

    void retranslateUi(QMainWindow *Image_calorie_detectionClass)
    {
        Image_calorie_detectionClass->setWindowTitle(QApplication::translate("Image_calorie_detectionClass", "Image_calorie_detection", 0));
        pushButton->setText(QApplication::translate("Image_calorie_detectionClass", "\350\257\267\351\200\211\346\213\251\345\233\276\347\211\207\350\257\206\345\210\253", 0));
        label->setText(QApplication::translate("Image_calorie_detectionClass", "\347\273\223\346\236\234\357\274\232", 0));
        label_2->setText(QString());
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Image_calorie_detectionClass: public Ui_Image_calorie_detectionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGE_CALORIE_DETECTION_H
