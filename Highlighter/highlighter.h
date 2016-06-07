#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QDebug>
#include <QSyntaxHighlighter>

class Highlighter : public QSyntaxHighlighter
 {
     Q_OBJECT

 public:
     Highlighter(QTextDocument *parent = 0);

 protected:
     void highlightBlock(const QString &text);
     void addHighlighterRule();

 private:
     struct HighlightingRule
     {
         QRegExp pattern;
         QTextCharFormat format;

         HighlightingRule()
         {
             this->format = QTextCharFormat();
             this->pattern = QRegExp();
         }

         HighlightingRule(const QTextCharFormat& format, const QRegExp& pattern)
         {
             this->format = format;
             this->pattern = pattern;
         }
     };
     QVector<HighlightingRule> highlightingRules;

     QRegExp commentStartExpression;
     QRegExp commentEndExpression;

     QMap<QString, QTextCharFormat> keywordFormats;
     QTextCharFormat classFormat;
     QTextCharFormat singleLineCommentFormat;
     QTextCharFormat multiLineCommentFormat;
     QTextCharFormat quotationFormat;
     QTextCharFormat functionFormat;
 };
#endif // HIGHLIGHTER_H
