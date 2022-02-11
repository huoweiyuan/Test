/* lex 简单入门 1*/

%{
#include <stdio.h>
%}

%%
stop printf("Stop command received\n");
start printf("Start command received\n");
%%
