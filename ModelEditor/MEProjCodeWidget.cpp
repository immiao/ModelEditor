#include "MEProjCodeWidget.h"
#include "MEProjLineNumberArea.h"
#include <QPainter>
#include <QTextBlock>
#include <QDebug>

MEProjCodeWidget::MEProjCodeWidget(QWidget *pqParent) : QPlainTextEdit(pqParent)
{
	m_pQLineNumberArea = new MEProjLineNumberArea(this);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(UpdateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(UpdateLineNumberArea(QRect,int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(HighlightCurrentLine()));

	UpdateLineNumberAreaWidth(0);
	HighlightCurrentLine();
}

// Calculates the width of the LineNumberArea widget
int MEProjCodeWidget::LineNumberAreaWidth()
{
	int nDigits = 1;
	int nMax = qMax(1, blockCount());
	while (nMax >= 10) {
		nMax /= 10;
		++nDigits;
	}

	int nSpace = 3 + fontMetrics().width(QLatin1Char('9')) * nDigits;

	return nSpace;
}

void MEProjCodeWidget::UpdateLineNumberAreaWidth(int nNewBlockCount)
{
	setViewportMargins(LineNumberAreaWidth(), 0, 0, 0);
}

// Invoked when viewport has been scrolled
void MEProjCodeWidget::UpdateLineNumberArea(const QRect &qRect, int nDeltaY)
{
	if (nDeltaY)
		m_pQLineNumberArea->scroll(0,nDeltaY);
	else
		m_pQLineNumberArea->update(0, qRect.y(), m_pQLineNumberArea->width(), qRect.height());

	if (qRect.contains(viewport()->rect()))
		UpdateLineNumberAreaWidth(0);
}

// Resize the line number area when the size of the editor changes
void MEProjCodeWidget::resizeEvent(QResizeEvent *pqEvent)
{
	QPlainTextEdit::resizeEvent(pqEvent);

	QRect qCR = contentsRect();
	m_pQLineNumberArea->setGeometry(QRect(qCR.left(), qCR.top(), LineNumberAreaWidth(), qCR.height()));
}

void MEProjCodeWidget::HighlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> qlExtraSelections;

	if (!isReadOnly()) {
		QTextEdit::ExtraSelection qtSelection;

		QColor lineColor = QColor(Qt::yellow).lighter(160);

		qtSelection.format.setBackground(lineColor);
		qtSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
		qtSelection.cursor = textCursor();
		qtSelection.cursor.clearSelection();
		qlExtraSelections.append(qtSelection);
	}

	setExtraSelections(qlExtraSelections);
}

// Called by LineNumberArea to paint editor
void MEProjCodeWidget::LineNumberAreaPaintEvent(QPaintEvent *pqEvent)
{
	QPainter qPainter(m_pQLineNumberArea);
	qPainter.fillRect(pqEvent->rect(), Qt::lightGray);

	QTextBlock qBlock = firstVisibleBlock();
	int nBlockNumber = qBlock.blockNumber();
	int nTop = (int) blockBoundingGeometry(qBlock).translated(contentOffset()).top();
	int nBottom = nTop + (int) blockBoundingRect(qBlock).height();

	while (qBlock.isValid() && nTop <= pqEvent->rect().bottom()) {
		if (qBlock.isVisible() && nBottom >= pqEvent->rect().top()) {
			QString qStrNumber = QString::number(nBlockNumber + 1);
			qPainter.setPen(Qt::black);
			qPainter.drawText(0, nTop, m_pQLineNumberArea->width(), fontMetrics().height(),
				Qt::AlignRight, qStrNumber);
		}

		qBlock = qBlock.next();
		nTop = nBottom;
		nBottom = nTop + (int) blockBoundingRect(qBlock).height();
		++nBlockNumber;
	}
}

MEProjCodeWidget::~MEProjCodeWidget(void)
{
	SAFE_DELETE(m_pQLineNumberArea);
	qDebug() << "Code Widget Delete";
}
