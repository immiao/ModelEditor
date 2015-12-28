///////////////////////////////////////////////////////////////
// Copyright(c) Kingsoft
// 
// FileName : modeleditor.cpp
// Creator  : Miao Kaixiang
// Date     : 2015-7-30 15:00:00
// Comment  : Entrance
//
///////////////////////////////////////////////////////////////

#include "modeleditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ModelEditor w;
	w.Init();
	w.show();
	
	int nResult = a.exec();
	w.UnInit();

	return nResult;
}
