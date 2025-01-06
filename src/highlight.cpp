//============================================================================
// Project     : YE.A.S.T
// Please refer to header file
//============================================================================
#include "highlight.h"

Highlight::Highlight(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightRule rule;
    QTextCharFormat keyword_format;

    keyword_format.setForeground(Qt::magenta);
    keyword_format.setBackground(Qt::transparent);
    keyword_format.setFontWeight(QFont::Bold);
    const QString keyword_patterns[] = {
        QStringLiteral("\\bFIR\\b"),
        QStringLiteral("\\bCRL\\b"),
        QStringLiteral("\\bBGL\\b"),
        QStringLiteral("\\bVBN\\b"),
        QStringLiteral("\\bDESG_[0-9_]+\\b"),
        QStringLiteral("\\bGATC_CRL_MEMO_[0-9_\\-]+\\b"),

    };
    for (const QString &pattern : keyword_patterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keyword_format;
        highlighting_rules.append(rule);
    }

    QTextCharFormat keyword_task;
    keyword_task.setForeground(Qt::blue);
    keyword_task.setBackground(Qt::transparent);
    keyword_task.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("^(\\<.*\\>)"));
    rule.format = keyword_task;
    highlighting_rules.append(rule);

    QTextCharFormat keyword_status_todo;
    keyword_status_todo.setForeground(Qt::blue);
    keyword_status_todo.setBackground(Qt::cyan);
    keyword_status_todo.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("(\\[TODO\\])"));
    rule.format = keyword_status_todo;
    highlighting_rules.append(rule);

    QTextCharFormat keyword_status_inprogress;
    keyword_status_inprogress.setForeground(Qt::black);
    keyword_status_inprogress.setBackground(Qt::green);
    keyword_status_inprogress.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("(\\[\\b(PROGRESS|INPROGRESS|IN PROGRESS)\\b\\])"));
    rule.format = keyword_status_inprogress;
    highlighting_rules.append(rule);

    QTextCharFormat keyword_status_wait;
    keyword_status_wait.setForeground(Qt::black);
    keyword_status_wait.setBackground(Qt::yellow);
    keyword_status_wait.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("(\\[WAIT\\])"));
    rule.format = keyword_status_wait;
    highlighting_rules.append(rule);

    QTextCharFormat keyword_status_done;
    keyword_status_done.setForeground(Qt::black);
    keyword_status_done.setBackground(Qt::transparent);
    keyword_status_done.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("(\\[DONE\\])"));
    rule.format = keyword_status_done;
    highlighting_rules.append(rule);

    QTextCharFormat keyword_status_invalid;
    keyword_status_invalid.setForeground(Qt::black);
    keyword_status_invalid.setBackground(Qt::red);
    keyword_status_invalid.setFontWeight(QFont::Normal);
    rule.pattern = QRegularExpression(QStringLiteral("^.*(\\[[ \t]*\\]).*$"));
    rule.format = keyword_status_invalid;
    highlighting_rules.append(rule);

    QTextCharFormat keyword_status_note;
    keyword_status_invalid.setForeground(Qt::red);
    keyword_status_invalid.setBackground(Qt::transparent);
    keyword_status_invalid.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("(\\(\\!\\).*)$"));
    rule.format = keyword_status_invalid;
    highlighting_rules.append(rule);

    QTextCharFormat keyword_pic;
    keyword_pic.setFontItalic(true);
    keyword_pic.setForeground(Qt::darkGreen);
    keyword_pic.setBackground(Qt::transparent);
    keyword_pic.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("(@[a-zA-Z]+)"));
    rule.format = keyword_pic;
    highlighting_rules.append(rule);

    // Add here other rules ...
}

void Highlight::highlightBlock(const QString &text)
{
    for (const HighlightRule &rule : qAsConst(highlighting_rules)) {
        QRegularExpressionMatchIterator re_match_iterator = rule.pattern.globalMatch(text);
        while (re_match_iterator.hasNext()) {
            QRegularExpressionMatch match = re_match_iterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
