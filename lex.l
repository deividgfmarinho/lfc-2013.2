%{ 
/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 01
*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
/* contador para controlar o total de aberturas e fechamentos de delimitadores de comentários de C- */ 
int cont = 0;
/* cadeia de caracteres que armazena o valor do comentário de C- */
char* comentario;
/* armazena o tamanho da cadeia de caracteres acima */
int tamComentario = 0;
%}
NUM [0-9]+
ID ([a-z]|[A-Z])+
SIMBOL "+"|"-"|"*"|"/"|"<"|"<="|">"|">="|"=="|"!="|"="|";"|","|"("|")"|"["|"]"|"{"|"}"
%x STRING
%x COMENTARIO
%% 



["]		{ BEGIN STRING; }	

<STRING>([^"\\\n]|\\[nt"])*["] { 
		   	BEGIN INITIAL;
	      	   	printf("STRING: \"%s \n", yytext);
                }
				
<STRING>([^"\\\n]|\\.)*[\n] { 
		   	BEGIN INITIAL;
			/* "remove" o \n do final */
			yytext[strlen(yytext) - 2] = '\0';
			printf("ERRO LÉXICO. ERA ESPERADO O FECHAMENTO DAS ASPAS DUPLAS EM:   \"%s \n", yytext);
                }

<STRING>([^"\\\n]|\\[nt"])*\\[^nt"]([^"\n])*["] {
			BEGIN INITIAL;
			printf("STRING (POSSUI ESCAPE(S) NÃO RECONHECIDO(S)):   \"%s \n",yytext );
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


<<EOF>>		  { if(tamComentario > 0){
		      if(cont == 1)
			printf("ERRO LÉXICO. ERA ESPERADO O \"*/\" AO FINAL DE:   %s \n", comentario);
		      else
			printf("ERRO LÉXICO. ERAM ESPERADOS %d \"*/\" AO FINAL DE:   %s \n", cont, comentario);
		    }
		    yyterminate();
		  }




"else"		{ printf("PALAVRA-CHAVE: %s \n",yytext ); }
"if"		{ printf("PALAVRA-CHAVE: %s \n",yytext ); }
"int"		{ printf("PALAVRA-CHAVE: %s \n",yytext ); }
"return"	{ printf("PALAVRA-CHAVE: %s \n",yytext ); }
"string"	{ printf("PALAVRA-CHAVE: %s \n",yytext ); }
"void"		{ printf("PALAVRA-CHAVE: %s \n",yytext ); }
"while"		{ printf("PALAVRA-CHAVE: %s \n",yytext ); }


{NUM} 		{ printf("NÚMERO INTEIRO: %s \n",yytext );}

{SIMBOL}	{ printf("SÍMBOLO ESPECIAL: %s \n",yytext ); }

{ID}		{ printf("IDENTIFICADOR: %s \n",yytext ); }






{ID}[^\+\-\*/<=>!;,\(\)\[\]\{\}\"[:space:]\n]+	{ printf("ERRO LÉXICO. IDENTIFICADOR   %s   É INVÁLIDO! \n",yytext ); }

{NUM}{ID}({ID}|{NUM})*				{ printf("ERRO LÉXICO. VALOR NÃO RECONHECIDO:   %s \n",yytext ); }

[^{NUM}{ID}{SIMBOL}[:space:]\n]			{ printf("SÍMBOLO   %s   NÃO É RECONHECIDO! \n",yytext ); }



.|\n|\r

%%
main(){
  yylex();
  return 0;
}



