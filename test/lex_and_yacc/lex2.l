%{
#include <stdio.h>
%}

%%

[0-9]+ printf("NUMBER\n");
[a-z][a-z0-9]* printf("WORD\n");
