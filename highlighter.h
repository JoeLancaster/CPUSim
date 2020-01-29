#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QString>
#include <QRegExp>
#include <QTextCharFormat>
#include <QSyntaxHighlighter>
#include <QVector>

class highlighter : public QSyntaxHighlighter{

        Q_OBJECT

    public:
        highlighter(QTextDocument * parent = 0);
    protected:
        void highlightBlock(const QString &text);
    private:
        struct highlight_rule{
            QRegExp pattern;
            QTextCharFormat format;
        };
        QVector<highlight_rule> rules;
        QTextCharFormat commentFormat, opcodeFormat, operandFormat, colonFormat;

};

#endif
