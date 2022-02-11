/* lex 简单入门 1*/

%{
#include <stdio.h>
int yywrap()
{
  return 1;
}
%}

%%
stop printf("Stop command received\n");
start printf("Start command received\n");
%%

main()
{
  yylex();
}
