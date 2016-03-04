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
    QAction *action_save;
    QAction *action_play;
    QAction *action_stop;
    QAction *action_grid;
    QAction *action_saveAll;
    QAction *actionRay_Tracing;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_Demo;
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
        action_save = new QAction(ModelEditorClass);
        action_save->setObjectName(QStringLiteral("action_save"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/ModelEditor/Resources/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_save->setIcon(icon);
        action_play = new QAction(ModelEditorClass);
        action_play->setObjectName(QStringLiteral("action_play"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ModelEditor/Resources/Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_play->setIcon(icon1);
        action_stop = new QAction(ModelEditorClass);
        action_stop->setObjectName(QStringLiteral("action_stop"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ModelEditor/Resources/Stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_stop->setIcon(icon2);
        action_grid = new QAction(ModelEditorClass);
        action_grid->setObjectName(QStringLiteral("action_grid"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/ModelEditor/Resources/Grid.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_grid->setIcon(icon3);
        action_saveAll = new QAction(ModelEditorClass);
        action_saveAll->setObjectName(QStringLiteral("action_saveAll"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/ModelEditor/Resources/Save All.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_saveAll->setIcon(icon4);
        actionRay_Tracing = new QAction(ModelEditorClass);
        actionRay_Tracing->setObjectName(QStringLiteral("actionRay_Tracing"));
        centralWidget = new QWidget(ModelEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ModelEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ModelEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 23));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_Demo = new QMenu(menu_F);
        menu_Demo->setObjectName(QStringLiteral("menu_Demo"));
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
        menu_F->addAction(menu_Demo->menuAction());
        menu_F->addAction(saveFile);
        menu_Demo->addAction(actionRay_Tracing);
        mainToolBar->addAction(action_save);
        mainToolBar->addAction(action_saveAll);
        mainToolBar->addAction(action_grid);
        mainToolBar->addAction(action_play);
        mainToolBar->addAction(action_stop);

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
        action_save->setText(QApplication::translate("ModelEditorClass", "\344\277\235\345\255\230xml\346\226\207\344\273\266", 0));
#ifndef QT_NO_TOOLTIP
        action_save->setToolTip(QApplication::translate("ModelEditorClass", "\344\277\235\345\255\230\346\226\207\344\273\266", 0));
#endif // QT_NO_TOOLTIP
        action_play->setText(QApplication::translate("ModelEditorClass", "\346\222\255\346\224\276", 0));
        action_stop->setText(QApplication::translate("ModelEditorClass", "\345\201\234\346\255\242", 0));
#ifndef QT_NO_TOOLTIP
        action_stop->setToolTip(QApplication::translate("ModelEditorClass", "\345\201\234\346\255\242", 0));
#endif // QT_NO_TOOLTIP
        action_grid->setText(QApplication::translate("ModelEditorClass", "\347\275\221\346\240\274", 0));
        action_saveAll->setText(QApplication::translate("ModelEditorClass", "\344\277\235\345\255\230\346\211\200\346\234\211\346\226\207\344\273\266", 0));
        actionRay_Tracing->setText(QApplication::translate("ModelEditorClass", "Ray Tracing", 0));
        menu_F->setTitle(QApplication::translate("ModelEditorClass", "\346\226\207\344\273\266(&F)", 0));
        menu_Demo->setTitle(QApplication::translate("ModelEditorClass", "\350\277\220\350\241\214Demo", 0));
    } // retranslateUi

};

namespace Ui {
    class ModelEditorClass: public Ui_ModelEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELEDITOR_H
