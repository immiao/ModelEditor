#pragma once
#include <QtWidgets/QMainWindow>
#include "MEProjCodeWidget.h"

class MEProjLineNumberArea : public QWidget
{
public:
	MEProjLineNumberArea(MEProjCodeWidget *pEditor);
	~MEProjLineNumberArea(void);
	QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
	void paintEvent(QPaintEvent *pQEvent) Q_DECL_OVERRIDE;

private:
	MEProjCodeWidget *m_pCodeEditor;
};

