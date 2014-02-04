/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 02
*/



/* a opção abaixo é para impedir que o analisador léxico
   chama a função yywrap quando chegar no final do arquivo.
   Sem esta opção, o analisador léxico não gera conflito
   com o analisador sintático. */
%option noyywrap

%{ 

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "sintatico.h"


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
			
			/* está retornando sem a aspa dupla no início! */
			return STRSTR;
                }
				
<STRING>([^"\\\n]|\\.)*[\n] { 
		   	BEGIN INITIAL;
			/* "remove" o \n do final */
			yytext[strlen(yytext) - 2] = '\0';
			printf("ERRO LÉXICO. ERA ESPERADO O FECHAMENTO DAS ASPAS DUPLAS EM:   \"%s \n", yytext);
			
			//return error;
                }

<STRING>([^"\\\n]|\\[nt"])*\\[^nt"]([^"\n])*["] {
			BEGIN INITIAL;
			
			printf("ALERTA: STRING (POSSUI ESCAPE(S) NÃO RECONHECIDO(S)):   \"%s \n",yytext);


			/* está retornando sem a aspa dupla no início! */
			return STRSTR;
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
	      	       
			/*printf("COMENTÁRIO: %s \n", comentario);*/		       

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
				
		      //return error;       

		    }

		    yyterminate();
		  }




"else"		{ return ELSE;   }
"if"		{ return IF;     }
"int"		{ return INT;    }
"return"	{ return RETURN; }
"string"	{ return STR;    }
"void"		{ return VOID;   }
"while"		{ return WHILE;  }


{NUM} 		{ return NUM;    }

"+"		{ return MAIS;   }
"-"		{ return MENOS;  }
"*"		{ return ASTERISCO; }
"/"		{ return BARRA;  }
"<"		{ return MENOR;  }
"<="		{ return MENORIGUAL; }
">"		{ return MAIOR;  }
">="		{ return MAIORIGUAL; }
"=="		{ return IGUAL;  }
"!="		{ return DIFERENTE;  }
"="		{ return ATRIBUICAO;  }
";"		{ return PONTOEVIRGULA;  }
","		{ return VIRGULA;  }
"("		{ return ABREPARENTESIS;  }
")"		{ return FECHAPARENTESIS; }
"["		{ return ABRECOLCHETE;  }
"]"		{ return FECHACOLCHETE; }
"{"		{ return ABRECHAVES;  }
"}"		{ return FECHACHAVES; } 


{ID}		{ return ID;  }






{ID}{NUM}({ID}|{NUM})*	{ printf("ERRO LÉXICO. IDENTIFICADOR   %s   É INVÁLIDO! \n",yytext); 
		  	  //return error;
			}

{NUM}{ID}({ID}|{NUM})*	{ printf("ERRO LÉXICO. VALOR NÃO RECONHECIDO:   %s \n",yytext); 
			  //return error;
			}

[^{NUM}{ID}{SIMBOL}[:space:]\n\r]	{ printf("ERRO LÉXICO. SÍMBOLO   %s   NÃO É RECONHECIDO! \n",yytext); 
				  //return error;
				}



.|\n|\r

%%

/* 
   não pode exibir a main aqui se
   não vai dar conflito com a main
   criada pelo analisador sintático! 
*/



