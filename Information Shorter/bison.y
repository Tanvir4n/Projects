%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

char *name=NULL, *age=NULL, *address=NULL, *education=NULL;
char *tech_skills=NULL, *soft_skills=NULL, *projects=NULL;
char *achievements=NULL, *hobbies=NULL;

char* concat(char *a, char *b) {
    char *res = malloc(strlen(a) + strlen(b) + 2);
    sprintf(res, "%s %s", a, b);
    free(a);
    free(b);
    return res;
}

// Trim everything after first dot
char* trim_at_dot(char *s) {
    char *dot = strchr(s, '.');
    if (dot) *dot = '\0';
    return s;
}
%}

%union {
    char *str;
}

%token NAME_KW AGE_KW ADDRESS_KW EDUCATION_KW TECH_SKILLS_KW SOFT_SKILLS_KW
%token PROJECTS_KW ACHIEVEMENTS_KW HOBBIES_KW
%token <str> TEXT
%token <str> NUMBER

%type <str> text_list

%%
cv:
    sections
    {
        printf("\n---- Extracted CV Information ----\n");
        if(name) printf("Name: %s\n", name);
        if(age) printf("Age: %s\n", age);
        if(address) printf("Address: %s\n", address);
        if(education) printf("Education: %s\n", education);
        if(tech_skills) printf("Technical Skills: %s\n", tech_skills);
        if(soft_skills) printf("Soft Skills: %s\n", soft_skills);
        if(projects) printf("Projects: %s\n", projects);
        if(achievements) printf("Achievements: %s\n", achievements);
        if(hobbies) printf("Hobbies: %s\n", hobbies);
    }
    ;

sections:
    | sections section
    ;

section:
      NAME_KW text_list           { name         = trim_at_dot($2); }
    | AGE_KW NUMBER text_list     { age          = trim_at_dot(concat($2, $3)); }
    | ADDRESS_KW text_list        { address      = trim_at_dot($2); }
    | EDUCATION_KW text_list      { education    = trim_at_dot($2); }
    | TECH_SKILLS_KW text_list    { tech_skills  = trim_at_dot($2); }
    | SOFT_SKILLS_KW text_list    { soft_skills  = trim_at_dot($2); }
    | PROJECTS_KW text_list       { projects     = trim_at_dot($2); }
    | ACHIEVEMENTS_KW text_list   { achievements = trim_at_dot($2); }
    | HOBBIES_KW text_list        { hobbies      = trim_at_dot($2); }
    ;

text_list:
      TEXT                        { $$ = $1; }
    | text_list TEXT              { $$ = concat($1, $2); }
    ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

int main() {
    printf("Reading CV and extracting information...\n");
    yyparse();
    return 0;
}
