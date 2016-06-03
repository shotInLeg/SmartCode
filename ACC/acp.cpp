#include "acp.h"

ACP::ACP()
{
    QStringList typesPatterns;
    typesPatterns << "\\bnum\\b" << "\\bchar\\b" << "\\bbool\\b" << "\\bvoid\\b"
                  <<"\\bstr\\b";

    QStringList keywordPatterns;
    keywordPatterns << "\\bclass\\b" << "\\bstruct\\b" << "\\benum\\b"
                    << "\\bif\\b" << "\\belse\\b" << "\\bifno\\b" << "\\bifunk\\b"
                    << "\\bfor\\b" << "\\bwhile\\b" << "\\bdo\\b" << "\\bifunk\\b"
                    << "\\bbreak\\b" << "\\bcontinue\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\btypedef\\b" << "\\blabel\\b" << "\\busing\\b"
                    <<  "\\bconst\\b"  << "\\breturn\\b";


    rules.push_back(ParseRule("type", "\\bnum\\b"));
    rules.push_back(ParseRule("type", "num\\s"));
    rules.push_back(ParseRule("type", "\\bchar\\b"));
    rules.push_back(ParseRule("type", "char\\s"));
    rules.push_back(ParseRule("type", "\\bbool\\b"));
    rules.push_back(ParseRule("type", "bool\\s"));
    rules.push_back(ParseRule("type", "\\bstr\\b"));
    rules.push_back(ParseRule("type", "str\\s"));

    rules.push_back(ParseRule("operator", "\\bif\\b")); //если да
    rules.push_back(ParseRule("operator", "\\belse\\b")); // иначе
    rules.push_back(ParseRule("operator", "\\bifno\\b")); // если нет
    rules.push_back(ParseRule("operator", "\\bifunk\\b")); // если незвестно

    rules.push_back(ParseRule("operator", "\\bfor\\b"));
    rules.push_back(ParseRule("operator", "\\bwhile\\b"));
    rules.push_back(ParseRule("operator", "\\bdo\\b"));
    rules.push_back(ParseRule("operator", "\\bbreak\\b"));
    rules.push_back(ParseRule("operator", "\\bcontinue\\b"));


    rules.push_back(ParseRule("value", "\"[^\"]*\""));

    foreach (const QString &pattern, typesPatterns)
    {
        rules.push_back(ParseRule("value", "\\b"+pattern+"+\\x005B+[amt]+\\x005D"));
    }
    foreach (const QString &pattern, typesPatterns)
    {
        rules.push_back(ParseRule("value", pattern));
    }
    foreach (const QString &pattern, keywordPatterns)
    {
        rules.push_back(ParseRule("value", pattern));
    }

    rules.push_back(ParseRule("operator", "\\x0028")); // (
    rules.push_back(ParseRule("operator", "\\x0029")); // )
    rules.push_back(ParseRule("operator", "\\x007B")); // {
    rules.push_back(ParseRule("operator", "\\x007D")); // }

    rules.push_back(ParseRule("operation", "\\x005B")); // [
    rules.push_back(ParseRule("operation", "\\x005D")); // ]

    rules.push_back(ParseRule("operation", "\\x002B+\\x002B+")); // ++
    rules.push_back(ParseRule("operation", "\\x002D+\\x002D")); // --

    rules.push_back(ParseRule("operation", "\\x002B")); // +
    rules.push_back(ParseRule("operation", "\\x002D")); // -
    rules.push_back(ParseRule("operation", "\\x002A")); // *
    rules.push_back(ParseRule("operation", "\\x002F")); // /
    rules.push_back(ParseRule("operation", "\\x005C")); // \\
    rules.push_back(ParseRule("operation", "\\x0025")); // %
    rules.push_back(ParseRule("operation", "\\x005E")); // ^

    rules.push_back(ParseRule("operator", "\\x002C")); // ,
    rules.push_back(ParseRule("operation", "\\x002E")); // .
    rules.push_back(ParseRule("operator", "\\x003B")); // ;

    rules.push_back(ParseRule("operation", "\\x003C+\\x003D")); // <=
    rules.push_back(ParseRule("operation", "\\x003E+\\x003D")); // >=
    rules.push_back(ParseRule("operation", "\\x0021+\\x003D")); // !=
    rules.push_back(ParseRule("operation", "\\x003D+\\x003D")); // ==
    rules.push_back(ParseRule("operation", "\\x0021")); // !
    rules.push_back(ParseRule("operation", "\\x003C")); // <
    rules.push_back(ParseRule("operation", "\\x003D")); // =
    rules.push_back(ParseRule("operation", "\\x003E")); // >

    rules.push_back(ParseRule("operator", "\\x003F")); // ?
    rules.push_back(ParseRule("operator", "\\x003A")); // :

    rules.push_back(ParseRule("operation", "\\x0026+\\x0026")); // &&
    rules.push_back(ParseRule("operation", "\\x007C+\\x007C")); // ||

    rules.push_back(ParseRule("operation", "\\x007E")); // ~
    rules.push_back(ParseRule("operation", "\\x0026")); // &
    rules.push_back(ParseRule("operation", "\\x007C")); // |

    rules.push_back(ParseRule("variables", "\\b[\\^A-Za-z_]+\\b"));

    rules.push_back(ParseRule("values", "\\b[0-9]+\\b"));


}

QVector<QPair<QString,QString> > ACP::parse(const QString &text)
{
    QVector<QPair<QString,QString> >  tokens;

    QString currentText = text;
    currentText = currentText.replace("\\x0009", "    ");

    while(currentText.size() > 0)
    {

        int minPos = currentText.size()+1;
        QRegExp curRegExp = rules.at(0).rule;
        int indexRule = 0;
        for(int numRule = 0; numRule < rules.size(); numRule++)
        {
            int index = rules.at(numRule).rule.indexIn(currentText);

            if( index < minPos && index >= 0 )
            {
                minPos = index;
                curRegExp = rules.at(numRule).rule;
                indexRule = numRule;
            }
        }

        if(minPos == currentText.size()+1)
        {
            break;
        }

        int length = curRegExp.matchedLength();
        if( length > 0 )
        {

            QString token = "";
            for(int i = minPos; i < minPos + length; i++)
            {
                token += currentText.at(i);
            }

            tokens.push_back( {rules.at(indexRule).name, token} );

            qDebug() << token << curRegExp.pattern();

            QString new_currentText = "";
            for( int i = minPos+length; i < currentText.size(); i++ )
            {
                new_currentText += currentText.at(i);
            }

            currentText = new_currentText;
        }
    }

    return tokens;
}

QString ACP::parseString(const QString &text)
{
    QVector<QPair<QString,QString> >  tokens = parse(text);

    for(int i = 0; i < tokens.size(); i++)
    {
        if( tokens.at(i).first == "type" )
            if( tokens.at(i).second == "num"  )
                tokens[i] = {"type", "ANum32"};
            if( tokens.at(i).second == "num16"  )
                tokens[i] = {"type", "ANum16"};
            else if( tokens.at(i).second == "num32" )
                tokens[i] = {"type", "ANum32"};
            else if( tokens.at(i).second == "num64" )
                tokens[i] = {"type", "ANum64"};
            else if( tokens.at(i).second == "num128" )
                tokens[i] = {"type", "ANum128"};
            else if( tokens.at(i).second == "charA" )
                tokens[i] = {"type", "ACharASCII"};
            else if( tokens.at(i).second == "byte" )
                tokens[i] = {"type", "AByte"};
            else if( tokens.at(i).second == "bit" )
                tokens[i] = {"type", "ABit"};

            else if( tokens.at(i).second == "str" )
                tokens[i] = {"type", "AArray<ACharASCII, Array>"};
            else if( tokens.at(i).second == "num[a]" )
                tokens[i] = {"type", "AArray<ANum32, Array>"};
            else if( tokens.at(i).second == "num16[a]" )
                tokens[i] = {"type", "AArray<ANum16, Array>"};
            else if( tokens.at(i).second == "num32[a]" )
                tokens[i] = {"type", "AArray<ANum32, Array>"};
            else if( tokens.at(i).second == "num64[a]" )
                tokens[i] = {"type", "AArray<ANum64, Array>"};
            else if( tokens.at(i).second == "num128[a]" )
                tokens[i] = {"type", "AArray<ANum128, Array>"};
            else if( tokens.at(i).second == "charA[a]" )
                tokens[i] = {"type", "AArray<ACharASCII, Array>"};
            else if( tokens.at(i).second == "byte[a]" )
                tokens[i] = {"type", "AArray<AByte, Array>"};
            else if( tokens.at(i).second == "bit[a]" )
                tokens[i] = {"type", "AArray<ABit, Array>"};

            else if( tokens.at(i).second == "num[m]" )
                tokens[i] = {"type", "AArray<ANum32, Matrix>"};
            else if( tokens.at(i).second == "num16[m]" )
                tokens[i] = {"type", "AArray<ANum16, Matrix>"};
            else if( tokens.at(i).second == "num32[m]" )
                tokens[i] = {"type", "AArray<ANum32, Matrix>"};
            else if( tokens.at(i).second == "num64[m]" )
                tokens[i] = {"type", "AArray<ANum64, Matrix>"};
            else if( tokens.at(i).second == "num128[m]" )
                tokens[i] = {"type", "AArray<ANum128, Matrix>"};
            else if( tokens.at(i).second == "charA[m]" )
                tokens[i] = {"type", "AArray<ACharASCII, Matrix>"};
            else if( tokens.at(i).second == "byte[m]" )
                tokens[i] = {"type", "AArray<AByte, Matrix>"};
            else if( tokens.at(i).second == "bit[m]" )
                tokens[i] = {"type", "AArray<ABit, Matrix>"};
    }

    QString cpp_text = "";
    cpp_text += "#include <Archi/ATL/ATL.h>\n";
    cpp_text += "#include <Archi/ACL/ACL.h>\n\n";
    for(int i = 0; i < tokens.size(); i++)
    {
        if( tokens.at(i).second == "{" || tokens.at(i).second == "}" || tokens.at(i).second == ";" )
            cpp_text += tokens.at(i).second + "\n";
        else
            cpp_text += tokens.at(i).second + " ";
    }

    return cpp_text;
}

