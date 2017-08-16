#ifndef SHIGHLIGHTER_H
#define SHIGHLIGHTER_H

#include <QDebug>
#include <QSyntaxHighlighter>
#include <QFile>

class SHighlighter : public QSyntaxHighlighter
 {
     Q_OBJECT

 public:
     SHighlighter(QTextDocument *parent = 0);
     void updateHighlightRules(const QString &highlight_page);

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
#endif // SHIGHLIGHTER_H
