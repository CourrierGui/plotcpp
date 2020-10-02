/********************************************************************************
** Form generated from reading UI file 'figure.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIGURE_H
#define UI_FIGURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <plotcpp/plotwidget.hpp>

#include <memory>

QT_BEGIN_NAMESPACE

class Ui_Figure
{
public:
    QVBoxLayout *verticalLayout;
		pcpp::PlotWidget* _plot;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *_save;

    void setupUi(
			std::size_t rows, std::size_t cols,
			QWidget *Figure)
    {
        if (Figure->objectName().isEmpty())
            Figure->setObjectName(QString::fromUtf8("Figure"));
        Figure->resize(400, 300);
        verticalLayout = new QVBoxLayout(Figure);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        _plot = new pcpp::PlotWidget{rows, cols, Figure};
        _plot->setObjectName(QString::fromUtf8("_plot"));

        verticalLayout->addWidget(&*_plot);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        _save = new QPushButton(Figure);
        _save->setObjectName(QString::fromUtf8("_save"));

        horizontalLayout_2->addWidget(_save);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Figure);

        QMetaObject::connectSlotsByName(Figure);
    } // setupUi

    void retranslateUi(QWidget *Figure)
    {
        Figure->setWindowTitle(QCoreApplication::translate("Figure", "Form", nullptr));
        _save->setText(QCoreApplication::translate("Figure", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Figure: public Ui_Figure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGURE_H
