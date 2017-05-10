#include "SHighlighter.h"

SHighlighter::SHighlighter(QTextDocument *parent): QSyntaxHighlighter(parent)
{


    keywordFormats["operator"].setForeground(QBrush(QColor(234,42,228)));
    keywordFormats["operator"].setFontItalic(true);

    keywordFormats["operation"].setForeground(QBrush(QColor(234,42,228)));

    keywordFormats["keyword"].setForeground(QBrush(QColor(234,42,228)));
    //keywordFormats["keyword"].setFontWeight(QFont::Bold);

    keywordFormats["types"].setForeground(QBrush(QColor(95,165,255)));
    //keywordFormats["types"].setFontWeight(QFont::Bold);

    keywordFormats["singleLineComment"].setForeground(Qt::gray);
    keywordFormats["multiLineComment"].setForeground(Qt::gray);

    keywordFormats["numbers"].setForeground(QBrush(QColor(150,66,255)));
    keywordFormats["quotation"].setForeground(QBrush(QColor(255,134,11)));

    keywordFormats["function"].setFontWeight(QFont::Bold);


    QStringList keywordPatterns;
    keywordPatterns << "\\bclass\\b" << "\\bunion\\b" <<  "\\bstruct\\b" << "\\benum\\b"
                    << "\\bif\\b" << "\\belse\\b" << "\\bifno\\b" << "\\bifunk\\b"
                    << "\\bfor\\b" << "\\bwhile\\b" << "\\bdo\\b" << "\\bifunk\\b"
                    << "\\bbreak\\b" << "\\bcontinue\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\btypedef\\b" << "\\blabel\\b" << "\\busing\\b"
                    <<  "\\bconst\\b"  << "\\breturn\\b";

    QStringList typesPatterns;
    typesPatterns << "\\bnum\\b" << "\\bchar\\b" << "\\bbool\\b" << "\\bvoid\\b"
                  <<"\\bstr\\b" << "\\buni\\b" << "\\bbyte\\b" << "\\bbit\\b";


    HighlightingRule rule;

    highlightingRules.append( HighlightingRule( keywordFormats["operator"], QRegExp("\\x0028") ) ); // (
    highlightingRules.append( HighlightingRule( keywordFormats["operator"], QRegExp("\\x0029") ) ); // (
    highlightingRules.append( HighlightingRule( keywordFormats["operator"], QRegExp("\\x007B") ) ); // {
    highlightingRules.append( HighlightingRule( keywordFormats["operator"], QRegExp("\\x007D") ) ); // }
    highlightingRules.append( HighlightingRule( keywordFormats["operator"], QRegExp("\\x005B") ) ); // [
    highlightingRules.append( HighlightingRule( keywordFormats["operator"], QRegExp("\\x005D") ) ); // ]

    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x003B") ) ); // ;

    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x002B+\\x002B+") ) ); // ++
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x002D+\\x002D") ) ); // --
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x002B") ) ); // +
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x002D") ) ); // -
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x002A") ) ); // *
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x002F") ) ); // /

    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x005C") ) ); // \\
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x0025") ) ); // %
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x005E") ) ); // ^
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x003C+\\x003D") ) ); // <=
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x003E+\\x003D") ) ); // =>
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x0021+\\x003D") ) ); // !=
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x003D+\\x003D") ) ); // ==
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x003E") ) ); // >
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x003C") ) ); // <
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x0021") ) ); // !
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x003D") ) ); // =
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x003F") ) ); // ?
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x003A") ) ); // :
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x0026+\\x0026") ) ); // &&
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x007C+\\x007C") ) ); // ||
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x007E") ) ); // ~
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x0026") ) ); // &
    highlightingRules.append( HighlightingRule( keywordFormats["operation"], QRegExp("\\x007C") ) ); // |

    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormats["keyword"];
        highlightingRules.append(rule);
    }

    foreach (const QString &pattern, typesPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormats["types"];
        highlightingRules.append(rule);
    }

    foreach (const QString &pattern, typesPatterns)
    {
        rule.pattern = QRegExp("\\b"+pattern+"+\\x005B+[amt]+\\x005D");
        rule.format = keywordFormats["types"];
        highlightingRules.append(rule);
    }

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bclass+\\s+[A-Za-z0-9_]{1,40}\\s");
    rule.format = classFormat;
    highlightingRules.append(rule);

    rule.pattern = QRegExp("[\\^#]+include\\s");
    rule.format = keywordFormats["keyword"];
    highlightingRules.append(rule);

//    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = keywordFormats["function"];
//    highlightingRules.append(rule);

    rule.pattern = QRegExp("\\b[0-9]+\\b");
    rule.format = keywordFormats["numbers"];
    highlightingRules.append(rule);

    rule.pattern = QRegExp("//[^\n]*");
    rule.format = keywordFormats["singleLineComment"];
    highlightingRules.append(rule);

    rule.pattern = QRegExp("\"[^\"]*\"");
    rule.format = keywordFormats["quotation"];
    highlightingRules.append(rule);


//    rule.pattern = QRegExp("\"[^\"]*");
//    rule.format = keywordFormats["quotation"];
//    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void SHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);

            if(rule.pattern == QRegExp("\\bclass+\\s+[A-Za-z0-9_]{1,40}\\s"))
            {
                QString new_type = "\\b";
                int start = text.lastIndexOf( QRegExp("\\bclass+\\s"), index );
                for(int i = start+6; i < length-start-1; i++)
                {
                    new_type += text.at(i);
                }
                new_type += "\\b";

                //qDebug() << new_type;

                HighlightingRule new_rule;
                new_rule.pattern = QRegExp(new_type);
                new_rule.format = keywordFormats["types"];
                highlightingRules.append(new_rule);

                new_rule.pattern = QRegExp("\\b"+new_type+"+\\x005B+[amt]+\\x005D");
                new_rule.format = keywordFormats["types"];
                highlightingRules.append(new_rule);
            }
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0)
    {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else
        {
            commentLength = endIndex - startIndex
                    + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, keywordFormats["multiLineComment"] );
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}

