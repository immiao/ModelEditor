#pragma once
#include <QtWidgets/QMainWindow>
#include <QSyntaxHighlighter>

class MEProjHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	MEProjHighlighter(QTextDocument *pqParent);
	
protected:
	void highlightBlock(const QString &qStrText) Q_DECL_OVERRIDE;

private:
	struct HighlightingRule
	{
		QRegExp qPattern;
		QTextCharFormat qFormat;
	};
	QVector<HighlightingRule> m_qvHighlightingRules;

	QRegExp m_CommentStartExpression;
	QRegExp m_CommentEndExpression;

	QTextCharFormat m_CommandFormat;
	QTextCharFormat m_NumberFormat;
	QTextCharFormat m_SingleLineCommentFormat;
	QTextCharFormat m_MultiLineCommentFormat;
	QTextCharFormat m_KeywordFormat;
};

