#include "MEProjLineNumberArea.h"


MEProjLineNumberArea::MEProjLineNumberArea(MEProjCodeWidget *pEditor) : QWidget(pEditor) 
{
	m_pCodeEditor = pEditor;
}

QSize MEProjLineNumberArea::sizeHint() const
{
	return QSize(m_pCodeEditor->LineNumberAreaWidth(), 0);
}

void MEProjLineNumberArea::paintEvent(QPaintEvent *pQEvent)
{
	m_pCodeEditor->LineNumberAreaPaintEvent(pQEvent);
}

MEProjLineNumberArea::~MEProjLineNumberArea(void)
{
}
