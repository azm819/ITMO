%{
#include <string>
#include "../expression.h"
#include "expression.tab.h"
%}

%option outfile="lex.c" header-file="lex.h"


white [ \t]+
digit [0-9]
lett [A-Z]
letter [a-z]

symbol {lett}({lett}|{digit}|{letter})*


%%
{symbol} {
    yylval.name=new std::string(yytext);
    return NAME;
}
"&" return AND;
"|" return OR;
"->" return IMP;
"!" return NEG;
"(" return LEFT;
")" return RIGHT;
"\n" return END;
%%