/********************************************************************************
** Form generated from reading UI file 'modeleditor.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELEDITOR_H
#define UI_MODELEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelEditorClass
{
public:
    QAction *openObjFile;
    QAction *saveFile;
    QAction *openM3dFile;
    QAction *openMEProjFile;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ModelEditorClass)
    {
        if (ModelEditorClass->objectName().isEmpty())
            ModelEditorClass->setObjectName(QStringLiteral("ModelEditorClass"));
        ModelEditorClass->resize(1024, 768);
        openObjFile = new QAction(ModelEditorClass);
        openObjFile->setObjectName(QStringLiteral("openObjFile"));
        saveFile = new QAction(ModelEditorClass);
        saveFile->setObjectName(QStringLiteral("saveFile"));
        openM3dFile = new QAction(ModelEditorClass);
        openM3dFile->setObjectName(QStringLiteral("openM3dFile"));
        openMEProjFile = new QAction(ModelEditorClass);
        openMEProjFile->setObjectName(QStringLiteral("openMEProjFile"));
        centralWidget = new QWidget(ModelEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ModelEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ModelEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 23));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        ModelEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ModelEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ModelEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ModelEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ModelEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menu_F->addAction(openObjFile);
        menu_F->addAction(openM3dFile);
        menu_F->addAction(openMEProjFile);
        menu_F->addAction(saveFile);

        retranslateUi(ModelEditorClass);

        QMetaObject::connectSlotsByName(ModelEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ModelEditorClass)
    {
        ModelEditorClass->setWindowTitle(QApplication::translate("ModelEditorClass", "ModelEditor", 0));
        openObjFile->setText(QApplication::translate("ModelEditorClass", "\346\211\223\345\274\200.obj\346\226\207\344\273\266", 0));
        saveFile->setText(QApplication::translate("ModelEditorClass", "\344\277\235\345\255\230\346\226\207\344\273\266", 0));
        openM3dFile->setText(QApplication::translate("ModelEditorClass", "\346\211\223\345\274\200.m3d\346\226\207\344\273\266", 0));
        openMEProjFile->setText(QApplication::translate("ModelEditorClass", "\346\211\223\345\274\200.meproj\346\226\207\344\273\266", 0));
        menu_F->setTitle(QApplication::translate("ModelEditorClass", "\346\226\207\344\273\266(&F)", 0));
    } // retranslateUi

};

namespace Ui {
    class ModelEditorClass: public Ui_ModelEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELEDITOR_H
