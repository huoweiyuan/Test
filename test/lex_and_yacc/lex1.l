/* lex 简单入门 1*/
/*
  flex lex1.l
  flex -i lex1.l 匹配模式不区分大小写
  gcc lex.yy.c -o lex -ll
*/
%{
#include <stdio.h>
%}

%%
stop printf("Stop command received\n");
start printf("Start command received\n");
%%
