%{
#include <stdio.h>
#include "yacc4.tab.h"
%}

%%
[0-9]+ {yylval = atoi(yytext); return NUMBER;}
heat return TOKHEAT;
on|off {yylval = !strcasecmp(yytext, "on");return STATE;}
target return TOKTARGET;
temperature return TOKTEMPERATURE;
\n ;
[ \t]+ ;
%%
