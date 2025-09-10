/********************************************************************************
** Form generated from reading UI file 'satellitepositionview.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SATELLITEPOSITIONVIEW_H
#define UI_SATELLITEPOSITIONVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_satellitepositionview
{
public:

    void setupUi(QWidget *satellitepositionview)
    {
        if (satellitepositionview->objectName().isEmpty())
            satellitepositionview->setObjectName("satellitepositionview");
        satellitepositionview->resize(800, 600);

        retranslateUi(satellitepositionview);

        QMetaObject::connectSlotsByName(satellitepositionview);
    } // setupUi

    void retranslateUi(QWidget *satellitepositionview)
    {
        satellitepositionview->setWindowTitle(QCoreApplication::translate("satellitepositionview", "satellitepositionview", nullptr));
    } // retranslateUi

};

namespace Ui {
    class satellitepositionview: public Ui_satellitepositionview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SATELLITEPOSITIONVIEW_H
