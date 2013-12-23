%{ 
/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 01
*/
#include <stdio.h> 
%} 

%% 





[/][/].* {printf("COMENTÁRIO: %s \n",yytext );}

[/][*]([^*]|[*]+[^*/])*[*]+[/] {printf("COMENTÁRIO: %s \n",yytext );}

["]([^"\\\n]|\\.)*["] {printf("STRING: %s \n",yytext );}

[+-]?[0-9]+ {printf("NÚMERO INTEIRO: %s \n",yytext );}

\'(\'|([^\\\'\n]|\\(\\|[']|["]|[?]|0|[a]|[b]|[f]|[n]|[r]|[t]|[v]|[0-7]{1,3}|x(([0-9]|[a-f]|[A-F]){1,2})))\') {printf("CARACTERE: %s \n",yytext );}

[+-]?([0-9]+([.,][0-9]*)?|[.,][0-9]+)([Ee][+-]?[0-9]+)? {printf("NÚMERO FRACIONÁRIO: %s \n",yytext );}




"auto"			{ printf("ESPECIFICADOR: %s \n",yytext ); }
"bool"			{ printf("ESPECIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"break"			{ printf("COMANDO DE SALTO: %s \n",yytext ); }
"case"			{ printf("COMANDO DE DECISÃO: %s \n",yytext ); }
"char"			{ printf("ESPECIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"const"			{ printf("QUALIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"continue"		{ printf("COMANDO DE SALTO: %s \n",yytext ); }
"default"		{ printf("PALAVRA RESERVADA: %s \n",yytext ); }
"do"			{ printf("COMANDO DE REPETIÇÃO: %s \n",yytext ); }
"double"		{ printf("TIPO DE DADO: %s \n",yytext ); }
"else"			{ printf("PALAVRA RESERVADA: %s \n",yytext ); }
"enum"			{ printf("PALAVRA RESERVADA: %s \n",yytext ); }
"extern"		{ printf("ESPECIFICADOR: %s \n",yytext ); }
"false"			{ printf("VALOR BOOLEANO: %s \n",yytext ); }
"float"			{ printf("ESPECIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"for"			{ printf("COMANDO DE REPETIÇÃO: %s \n",yytext ); }
"goto"			{ printf("COMANDO DE SALTO: %s \n",yytext ); }
"if"			{ printf("COMANDO DE DECISÃO: %s \n",yytext ); }
"int"			{ printf("ESPECIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"long"			{ printf("ESPECIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"NULL"			{ printf("Valor nulo : %s \n",yytext ); }
"register"		{ printf("ESPECIFICADOR: %s \n",yytext ); }
"return"		{ printf("COMANDO DE SALTO: %s \n",yytext ); }
"short"			{ printf("ESPECIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"signed"		{ printf("ESPECIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"sizeof"		{ printf("PALAVRA RESERVADA: %s \n",yytext ); }
"static"		{ printf("ESPECIFICADOR: %s \n",yytext ); }
"string"		{ printf("ESPECIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"struct"		{ printf("PALAVRA RESERVADA: %s \n",yytext ); }
"switch"		{ printf("PALAVRA RESERVADA: %s \n",yytext ); }
"true"			{ printf("VALOR BOOLEANO: %s \n",yytext ); }
"typedef"		{ printf("ESPECIFICADOR: %s \n",yytext ); }
"union"			{ printf("PALAVRA RESERVADA: %s \n",yytext ); }
"unsigned"		{ printf("PALAVRA RESERVADA: %s \n",yytext ); }
"void"			{ printf("ESPECIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"volatile"		{ printf("QUALIFICADOR DE TIPO DE DADO: %s \n",yytext ); }
"while"			{ printf("PALAVRA RESERVADA: %s \n",yytext ); }



"..."			{ printf("OPERADOR: %s \n",yytext ); }
">>="			{ printf("OPERADOR: %s \n",yytext ); }
"<<="			{ printf("OPERADOR: %s \n",yytext ); }
"+="			{ printf("OPERADOR: %s \n",yytext ); }
"-="			{ printf("OPERADOR: %s \n",yytext ); }
"*="			{ printf("OPERADOR: %s \n",yytext ); }
"/="			{ printf("OPERADOR: %s \n",yytext ); }
"%="			{ printf("OPERADOR: %s \n",yytext ); }
"&="			{ printf("OPERADOR: %s \n",yytext ); }
"^="			{ printf("OPERADOR: %s \n",yytext ); }
"|="			{ printf("OPERADOR: %s \n",yytext ); }
">>"			{ printf("OPERADOR: %s \n",yytext ); }
"<<"			{ printf("OPERADOR: %s \n",yytext ); }
"++"			{ printf("OPERADOR: %s \n",yytext ); }
"--"			{ printf("OPERADOR: %s \n",yytext ); }
"->"			{ printf("OPERADOR: %s \n",yytext ); }
"&&"			{ printf("OPERADOR: %s \n",yytext ); }
"||"			{ printf("OPERADOR: %s \n",yytext ); }
"<="			{ printf("OPERADOR: %s \n",yytext ); }
">="			{ printf("OPERADOR: %s \n",yytext ); }
"=="			{ printf("OPERADOR: %s \n",yytext ); }
"!="			{ printf("OPERADOR: %s \n",yytext ); }
";"				{ printf("DELIMITADOR DE COMANDOS: %s \n",yytext ); }
"{"				{ printf("ABERTURA DE UM BLOCO: %s \n",yytext ); }
"}"				{ printf("FECHAMENTO DE UM BLOCO: %s \n",yytext ); }
","				{ printf("SEPARADOR: %s \n",yytext ); }
":"				{ printf("OPERADOR: %s \n",yytext ); }
"="				{ printf("OPERADOR: %s \n",yytext ); }
"("				{ printf("ABERTURA DE PARÊNTESIS: %s \n",yytext ); }
")"				{ printf("FECHAMENTO DE PARÊNTESIS: %s \n",yytext ); }
"["				{ printf("ABERTURA DE COLCHETES: %s \n",yytext ); }
"]"				{ printf("FECHAMENTO DE COLCHETES: %s \n",yytext ); }
"."				{ printf("OPERADOR: %s \n",yytext ); }
"&"				{ printf("OPERADOR: %s \n",yytext ); }
"!"				{ printf("OPERADOR: %s \n",yytext ); }
"~"				{ printf("OPERADOR: %s \n",yytext ); }
"-"				{ printf("OPERADOR: %s \n",yytext ); }
"+"				{ printf("OPERADOR: %s \n",yytext ); }
"*"				{ printf("OPERADOR: %s \n",yytext ); }
"/"				{ printf("OPERADOR: %s \n",yytext ); }
"%"				{ printf("OPERADOR: %s \n",yytext ); }
"<"				{ printf("OPERADOR: %s \n",yytext ); }
">"				{ printf("OPERADOR: %s \n",yytext ); }
"^"				{ printf("OPERADOR: %s \n",yytext ); }
"|"				{ printf("OPERADOR: %s \n",yytext ); }
"?"				{ printf("OPERADOR: %s \n",yytext ); }




("_"|[a-z]|[A-Z])("_"|[0-9]|[a-z]|[A-Z]){0,31}	{ printf("IDENTIFICADOR: %s \n",yytext ); }




[0-9]+([^0123456789.,;\n\]\)]+|[.,][0-9]*[^0123456789;\n\]\)]+)	{ printf("ERRO LÉXICO. VALOR NAO RECONHECIDO:  %s \n",yytext ); }
[^"]([^"\\\n]|\\.)*["][,\);&|+:\?\]\=]	{ printf("ERRO LÉXICO. ERA ESPERADO A ABERTURA DAS ASPAS DUPLAS em  %s \n",yytext ); }
["]([^"\\\n]|\\.)*[^"]?			{ printf("ERRO LÉXICO. ERA ESPERADO O FECHAMENTO DAS ASPAS DUPLAS em  %s \n",yytext ); }
[^"_"[a-z][A-Z][0-9]]+.*		{ printf("ERRO LÉXICO. EXPRESSAO OU IDENTIFICADOR INVALIDO:  %s \n",yytext ); }

.|\n|\r



