#include "MEProjHighlighter.h"


MEProjHighlighter::MEProjHighlighter(QTextDocument *pqParent) : QSyntaxHighlighter(pqParent)
{
	HighlightingRule hRule;

	// Append command rules
	m_CommandFormat.setForeground(Qt::darkRed);
	m_CommandFormat.setFontWeight(QFont::Bold);
	QStringList qCommandPatterns;
	qCommandPatterns << "\\bforward\\b" << "\\bback\\b" << "\\bright\\b"
		<< "\\bleft\\b";
	foreach (const QString &qStrPattern, qCommandPatterns) {
		hRule.qPattern = QRegExp(qStrPattern);
		hRule.qFormat = m_CommandFormat;
		m_qvHighlightingRules.append(hRule);
	}

	// Append number rules
	m_NumberFormat.setForeground(Qt::blue);
	hRule.qPattern = QRegExp("\\b[0-9]+\\b");
	hRule.qFormat = m_NumberFormat;
	m_qvHighlightingRules.append(hRule);

	// Append keyword rules
	m_KeywordFormat.setForeground(Qt::magenta);
	hRule.qPattern = QRegExp("\\bend\\b");
	hRule.qFormat = m_KeywordFormat;
	m_qvHighlightingRules.append(hRule);

	// Append comment name rules
	m_SingleLineCommentFormat.setForeground(Qt::darkGreen);
	hRule.qPattern = QRegExp("//[^\n]*");
	hRule.qFormat = m_SingleLineCommentFormat;
	m_qvHighlightingRules.append(hRule);

	m_MultiLineCommentFormat.setForeground(Qt::darkGreen);

	m_CommentStartExpression = QRegExp("/\\*");
	m_CommentEndExpression = QRegExp("\\*/");
}

void MEProjHighlighter::highlightBlock(const QString &qStrText)
{
	foreach (const HighlightingRule &hRule, m_qvHighlightingRules) {
		QRegExp expression(hRule.qPattern);
		int index = expression.indexIn(qStrText);
		while (index >= 0) {
			int length = expression.matchedLength();
			setFormat(index, length, hRule.qFormat);
			index = expression.indexIn(qStrText, index + length);
		}
	}
	setCurrentBlockState(0);

	int nStartIndex = 0;
	if (previousBlockState() != 1)
		nStartIndex = m_CommentStartExpression.indexIn(qStrText);
	while (nStartIndex >= 0) {
		int nEndIndex = m_CommentEndExpression.indexIn(qStrText, nStartIndex);
		int nCommentLength;
		if (nEndIndex == -1) {
			setCurrentBlockState(1);
			nCommentLength = qStrText.length() - nStartIndex;
		} else {
			nCommentLength = nEndIndex - nStartIndex
				+ m_CommentEndExpression.matchedLength();
		}
		setFormat(nStartIndex, nCommentLength, m_MultiLineCommentFormat);
		nStartIndex = m_CommentStartExpression.indexIn(qStrText, nStartIndex + nCommentLength);
	}
}