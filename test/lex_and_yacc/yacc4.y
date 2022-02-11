%{
#include <stdio.h>
#include <string.h>

int yywrap()
{
  return 1;
}

void yyerror(const char *s)
{
  printf("[error] %s\n", s);
}

int main()
{
  yyparse();
  return 0;
}
%}

%token NUMBER TOKHEAT STATE TOKTARGET TOKTEMPERATURE

%%
commands:
| commands command
;

command:
heat_switch | target_set
;

heat_switch:
TOKHEAT STATE
{
  printf("\tHeat turned on or off\n");
};

target_set:
TOKTARGET TOKTEMPERATURE NUMBER
{
  printf("\tTemperature set\n");
};
