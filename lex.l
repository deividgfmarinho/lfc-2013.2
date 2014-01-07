%{ 
/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 01
*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
/* contador para controlar o total de aberturas e fechamentos de delimitadores de comentários de C++ */ 
int cont = 0;
/* cadeia de caracteres que armazena o valor do comentário de C++ */
char* comentario;
/* armazena o tamanho da cadeia de caracteres acima */
int tamComentario = 0;
%}
%x STRING
%x COMENTARIO
%% 



["]	       { BEGIN STRING; }	

<STRING>([^"\\\n]|\\[nt"])*["] { 
		   BEGIN INITIAL;
	      	   printf("STRING: \"%s \n", yytext);
                }
				
<STRING>([^"\\\n]|\\[nt"])*[\n] { 
		   BEGIN INITIAL;
	      	   printf("ERRO LÉXICO. ERA ESPERADO O FECHAMENTO DAS ASPAS DUPLAS EM: \"%s \n", yytext);
                }


"/*" 	{ 
	  if(cont == 0){
	    BEGIN COMENTARIO;
	    tamComentario = 0;
	    comentario = (char*) malloc(1 * sizeof(char));
	  }				 
	  cont++;
	  tamComentario += 2; 
	  comentario = (char*) realloc(comentario, tamComentario * sizeof(char));
	  strcat(comentario, "/*");
	}
	
<COMENTARIO>"/*" { cont++;
	  	   tamComentario += 2; 
	  	   comentario = (char*) realloc(comentario, tamComentario * sizeof(char));
	  	   strcat(comentario, "/*");
		 }
		 
<COMENTARIO>"*/" { tamComentario += 2; 
	           comentario = (char*) realloc(comentario, tamComentario * sizeof(char));
	  	   strcat(comentario, "*/");
		   if(cont > 0){
	    	     cont--;
	    	     if(cont == 0 ) {
	      	       BEGIN INITIAL;
	      	       printf("COMENTÁRIO: %s \n", comentario);
		       memset(comentario, 0, tamComentario);
		       tamComentario = 0;
	    	     }
	  	   }
		 }
		 
<COMENTARIO>.|\n|\r { tamComentario += strlen(yytext); 
	              comentario = (char*) realloc(comentario, tamComentario * sizeof(char));
		      strcat(comentario, yytext);
		    }






[/][/].* {printf("COMENTÁRIO: %s \n",yytext );}

[+-]?"0x"([0-9]|[a-f]|[A-F])+ {printf("NÚMERO HEXADECIMAL: %s \n",yytext );}

[+-]?"0"([0-7])+ {printf("NÚMERO OCTAL: %s \n",yytext );}

[+-]?[0-9]+ {printf("NÚMERO INTEIRO DECIMAL: %s \n",yytext );}

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
"NULL"			{ printf("VALOR NULO : %s \n",yytext ); }
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
";"			{ printf("DELIMITADOR DE COMANDOS: %s \n",yytext ); }
"{"			{ printf("ABERTURA DE UM BLOCO: %s \n",yytext ); }
"}"			{ printf("FECHAMENTO DE UM BLOCO: %s \n",yytext ); }
","			{ printf("SEPARADOR: %s \n",yytext ); }
":"			{ printf("OPERADOR: %s \n",yytext ); }
"="			{ printf("OPERADOR: %s \n",yytext ); }
"("			{ printf("ABERTURA DE PARÊNTESIS: %s \n",yytext ); }
")"			{ printf("FECHAMENTO DE PARÊNTESIS: %s \n",yytext ); }
"["			{ printf("ABERTURA DE COLCHETES: %s \n",yytext ); }
"]"			{ printf("FECHAMENTO DE COLCHETES: %s \n",yytext ); }
"."			{ printf("OPERADOR: %s \n",yytext ); }
"&"			{ printf("OPERADOR: %s \n",yytext ); }
"!"			{ printf("OPERADOR: %s \n",yytext ); }
"~"			{ printf("OPERADOR: %s \n",yytext ); }
"-"			{ printf("OPERADOR: %s \n",yytext ); }
"+"			{ printf("OPERADOR: %s \n",yytext ); }
"*"			{ printf("OPERADOR: %s \n",yytext ); }
"/"			{ printf("OPERADOR: %s \n",yytext ); }
"%"			{ printf("OPERADOR: %s \n",yytext ); }
"<"			{ printf("OPERADOR: %s \n",yytext ); }
">"			{ printf("OPERADOR: %s \n",yytext ); }
"^"			{ printf("OPERADOR: %s \n",yytext ); }
"|"			{ printf("OPERADOR: %s \n",yytext ); }
"?"			{ printf("OPERADOR: %s \n",yytext ); }




([a-z]|[A-Z]){1,32}	{ printf("IDENTIFICADOR: %s \n",yytext ); }





[0-9]+([^0123456789.,;\n\]\)]+|[.,][0-9]*[^0123456789;\n\]\)]+)	{ printf("ERRO LÉXICO. VALOR NÃO RECONHECIDO:  %s \n",yytext ); }

["]([^"\\\n]|\\[^nt"])*\\[^nt"]([^"\\\n]|\\.)*["] {printf("ERRO LÉXICO. ESCAPE NÃO RECONHECIDO NA STRING: %s \n",yytext );}

\'\\([^\\\'"?abfnrtvx01234567]+|[0-7]+[^01234567]|x([^0123456789abcdefABCDEF]|([0-9]|[a-f]|[A-F])+[^0123456789abcdefABCDEF])?)\' {printf("ERRO LÉXICO. ESCAPE INVÁLIDO NO CARACTERE: %s \n",yytext );}

\'(([^\\\'\n]|\\(\\|[']|["]|[?]|0|[a]|[b]|[f]|[n]|[r]|[t]|[v]|[0-7]{1,3}|x(([0-9]|[a-f]|[A-F]){1,2})))[^\'\n]+\') {printf("ERRO LÉXICO. CARACTERE INVÁLIDO: %s \n",yytext );}

\'([^\']?|([^\\\'\n]|\\(\\|[']|["]|[?]|0|[a]|[b]|[f]|[n]|[r]|[t]|[v]|[0-7]{1,3}|x(([0-9]|[a-f]|[A-F]){1,2})))[^\']?) {printf("ERRO LÉXICO. ERA ESPERADO O FECHAMENTO DA ASPA SIMPLES EM %s \n",yytext );}

([a-z]|[A-Z]){33,}[^\n[:space:];,\+\-*><!\?&/%.\]\[\)\({}~:\"\']*	{ printf("ERRO LÉXICO. IDENTIFICADOR NÃO PODE CONTER MAIS DE 32 CARACTERES!: %s \n",yytext ); }

(([a-z]|[A-Z])+("_"|[0-9])+|("_"|[0-9])+([a-z]|[A-Z])+)[^\n[:space:];,\+\-*><!\?&/%.\]\[\)\({}~:\"\']*	{ printf("ERRO LÉXICO. IDENTIFICADOR INVÁLIDO!: %s \n",yytext ); }


<<EOF>>		  { if(tamComentario > 0){
		      if(cont == 1)
			printf("ERRO LÉXICO. ERA ESPERADO O \"*/\" AO FINAL DE : %s \n", comentario);
		      else
			printf("ERRO LÉXICO. ERAM ESPERADOS %d \"*/\" AO FINAL DE : %s \n", cont, comentario);
		    }
		    yyterminate();
		  }



.|\n|\r



