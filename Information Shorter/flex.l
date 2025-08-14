%{
#include "bison.tab.h"
#include <string.h>
#include <stdlib.h>

#define YY_NO_UNPUT
%}

%option caseless

%%
[ \t\r\n]+                     ; // Ignore whitespace

my[ \t]+name[ \t]+is            return NAME_KW;
i[ \t]+am                       return AGE_KW;
my[ \t]+address[ \t]+is         return ADDRESS_KW;
my[ \t]+educational[ \t]+background[ \t]+is[:] return EDUCATION_KW;
my[ \t]+technical[ \t]+skills[ \t]+are[:]      return TECH_SKILLS_KW;
my[ \t]+soft[ \t]+skills[ \t]+are[:]           return SOFT_SKILLS_KW;
my[ \t]+projects[ \t]+are[:]                   return PROJECTS_KW;
my[ \t]+achievements[ \t]+are[:]               return ACHIEVEMENTS_KW;
my[ \t]+hobbies[ \t]+are[:]                    return HOBBIES_KW;

[0-9]+                          { yylval.str = strdup(yytext); return NUMBER; }
[A-Za-z0-9.,]+                  { yylval.str = strdup(yytext); return TEXT; }

.                               ; // Ignore unknown chars
%%

int yywrap() { return 1; }
