//============================================================================
// Project     : YE.A.S.T (YEt Another Small Timetracker)
// Author      : lisr-pcx (github.com/lisr-pcx)
// File        : highlight.h
// Description : Manage syntax highlighting
//
// This software come with absolutely no warranty. This is free software and
// you are welcome to use it, and redistribute. See license file for details.
//============================================================================

#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QRegularExpression>
#include <QTextCharFormat>

class Highlight : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlight(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightRule> highlighting_rules;
};

#endif // HIGHLIGHT_H
