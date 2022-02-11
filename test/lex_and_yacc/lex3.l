%{
#include <stdio.h>
%}

%%
[a-z][a-z0-9]* printf("WORD ");
[a-z0-9\/.-]+ printf("FILENAME ");
\" printf("QUOTE ");
\{ printf("OBRACE ");
\} printf("EBRACE ");
; printf("SEMICOLON ");
\n printf("\n");
[ \t]+ /*ignore whitespace*/;
%%
