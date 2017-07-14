/********************************************************************************
** Form generated from reading UI file 'cdrawframe.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDRAWFRAME_H
#define UI_CDRAWFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CDRawFrame
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *StartButton;
    QPushButton *StopButton;
    QPushButton *CloseButton;

    void setupUi(QFrame *CDRawFrame)
    {
        if (CDRawFrame->objectName().isEmpty())
            CDRawFrame->setObjectName(QString::fromUtf8("CDRawFrame"));
        CDRawFrame->resize(400, 300);
        CDRawFrame->setFrameShape(QFrame::StyledPanel);
        CDRawFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(CDRawFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        StartButton = new QPushButton(CDRawFrame);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));

        horizontalLayout->addWidget(StartButton);

        StopButton = new QPushButton(CDRawFrame);
        StopButton->setObjectName(QString::fromUtf8("StopButton"));

        horizontalLayout->addWidget(StopButton);

        CloseButton = new QPushButton(CDRawFrame);
        CloseButton->setObjectName(QString::fromUtf8("CloseButton"));

        horizontalLayout->addWidget(CloseButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CDRawFrame);

        QMetaObject::connectSlotsByName(CDRawFrame);
    } // setupUi

    void retranslateUi(QFrame *CDRawFrame)
    {
        CDRawFrame->setWindowTitle(QApplication::translate("CDRawFrame", "Frame", 0, QApplication::UnicodeUTF8));
        StartButton->setText(QApplication::translate("CDRawFrame", "Start", 0, QApplication::UnicodeUTF8));
        StopButton->setText(QApplication::translate("CDRawFrame", "Stop", 0, QApplication::UnicodeUTF8));
        CloseButton->setText(QApplication::translate("CDRawFrame", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CDRawFrame: public Ui_CDRawFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDRAWFRAME_H
