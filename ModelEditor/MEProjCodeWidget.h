#ifndef MEPROJCODEWIDGET_H
#define MEPROJCODEWIDGET_H

#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QMainWindow>
#include "KEPublic2.h"

class MEProjCodeWidget : public QPlainTextEdit
{
	Q_OBJECT
public:
	MEProjCodeWidget(QWidget *pQParent = 0);
	~MEProjCodeWidget(void);
	void LineNumberAreaPaintEvent(QPaintEvent *pQEvent);
	int  LineNumberAreaWidth();

protected:
	void resizeEvent(QResizeEvent *pQEvent) Q_DECL_OVERRIDE;

	private slots:
		void UpdateLineNumberAreaWidth(int nNewBlockCount);
		void HighlightCurrentLine();
		void UpdateLineNumberArea(const QRect &qRect, int nDeltaY);

private:
	QWidget *m_pQLineNumberArea;
};

#endif