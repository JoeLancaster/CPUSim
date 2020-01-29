#include "highlighter.h"

highlighter::highlighter(QTextDocument * parent) : QSyntaxHighlighter(parent) {

    static highlight_rule temp_rule;

    /*
     * add rules to the 'rules' vector
     * where a rule consists of a regular expression and some formatting
     * they specify when a piece of text should be highlighted and how
     */
    opcodeFormat.setForeground(Qt::darkBlue);
    opcodeFormat.setFontWeight(QFont::Bold);
    temp_rule.format = opcodeFormat;
    temp_rule.pattern = QRegExp("[A-Z]+\\s*:");
    rules.append(temp_rule);


    operandFormat.setForeground(Qt::magenta);
    temp_rule.format = operandFormat;
    temp_rule.pattern = QRegExp(":\\s*[A-Z0-9]+");
    rules.append(temp_rule);


    colonFormat.setForeground(Qt::black);
    temp_rule.format = colonFormat;
    temp_rule.pattern = QRegExp(":");
    rules.append(temp_rule);

    commentFormat.setForeground(Qt::gray);
    temp_rule.format = commentFormat;
    temp_rule.pattern = QRegExp(";[^\n]*");
    rules.append(temp_rule);
}

void highlighter::highlightBlock(const QString &text){
    /*
     * sequentially applies all of the rules to a line of text
     */
    foreach(const highlight_rule &rule, rules){
        QRegExp exp(rule.pattern);
        int index = exp.indexIn(text);
        while(index >= 0){
            int length = exp.matchedLength();
            setFormat(index, length, rule.format);
            index = exp.indexIn(text, index + length);
        }
    }
}
