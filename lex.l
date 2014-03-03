/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 03

						ANALISADOR LÉXICO PARA A LINGUAGEM C-
	 (baseado no livro de Kenneth C. Louden, só que aceita strings e comentários aninhados)


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
#include "arvoreabstrata.h"
#include "util.h"
#include "sintatico.h"



/* contador para controlar o total de aberturas e fechamentos de delimitadores de comentários de C- */ 
int cont = 0;
/* cadeia de caracteres que armazena o valor do comentário de C- */
string comentario;
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
			
			/* adiciona a aspa dupla no início! 
			memmove(yytext + 1, yytext, strlen(yytext) + 1);
			yytext[0] = '\"';  
			yytext[strlen(yytext)] = '\0'; */
			
			/* remove a aspa dupla do final,
			   deixando a string sem aspas */
			yytext[strlen(yytext) - 1] = '\0';
			
			
			/* ASSOCIA O VALOR A SER RETORNADO AO TIPO
			   DEFINIDO NO sintatico.y.
			   O método strdup faz uma cópia de um string */
			yylval.cstring = strdup(yytext);
			return STRSTR;
                }
				
<STRING>([^"\\\n]|\\.)*[\n] { 
		   	BEGIN INITIAL;
			/* "remove" o \n do final */
			yytext[strlen(yytext) - 2] = '\0';

			fprintf(stderr,"Erro lexico. Era esperado o fechamento das aspas duplas em:   \"%s \n", yytext);
			exit(1);
                }

<STRING>([^"\\\n]|\\[nt"])*\\[^nt"]([^"\n])*["] {
			BEGIN INITIAL;
			
			printf("Alerta: String possui escape(s) nao reconhecido(s):   \"%s \n",yytext);


			/* adiciona a aspa dupla no início! 
			memmove(yytext + 1, yytext, strlen(yytext) + 1);
			yytext[0] = '\"'; 
			yytext[strlen(yytext)] = '\0'; */
			
			/* remove a aspa dupla do final,
			   deixando a string sem aspas */
			yytext[strlen(yytext) - 1] = '\0';
			
			
			yylval.cstring = strdup(yytext);
			return STRSTR;
		}



"/*" 	{ 
	  if(cont == 0){
	    BEGIN COMENTARIO;
	    tamComentario = 0;
	    comentario = (string) malloc(1 * sizeof(char));
	  }				 
	  cont++;
	  tamComentario += 2; 
	  comentario = (string) realloc(comentario, tamComentario * sizeof(char));
	  strcat(comentario, "/*");
	}
	
<COMENTARIO>"/*" { cont++;
	  	   tamComentario += 2; 
	  	   comentario = (string) realloc(comentario, tamComentario * sizeof(char));
	  	   strcat(comentario, "/*");
		 }
		 
<COMENTARIO>"*/" { tamComentario += 2; 
	           comentario = (string) realloc(comentario, tamComentario * sizeof(char));
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
	              comentario = (string) realloc(comentario, tamComentario * sizeof(char));
		      strcat(comentario, yytext);
		    }


<<EOF>>		  { if(tamComentario > 0){

		      if(cont == 1)
			fprintf(stderr,"Erro lexico. Era esperado o \"*/\" ao final de:   %s \n", comentario);
		      else
			fprintf(stderr,"Erro lexico. eram esperados %d \"*/\" ao final de:   %s \n", cont, comentario);
			
			exit(1);

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


{NUM} 		{ /* ASSOCIA O VALOR A SER RETORNADO AO TIPO
			   DEFINIDO NO sintatico.y.
			   O método atoi converte um string para int */
			  yylval.inteiro = atoi(yytext);
			  return NUM;    }

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


{ID}		{ yylval.cstring = strdup(yytext);
			  return ID;  }






{ID}{NUM}({ID}|{NUM})*	{ fprintf(stderr,"Erro lexico. Identificador   %s   eh invalido! \n",yytext);
						  exit(1);	
			}

{NUM}{ID}({ID}|{NUM})*	{ fprintf(stderr,"Erro lexico. Valor nao reconhecido:   %s \n",yytext);
						  exit(1);	
			}

[^{NUM}{ID}{SIMBOL}[:space:]\n\r\t]	{ if(strlen(yytext) > 0){
										fprintf(stderr,"Erro lexico. Simbolo   %s   nao eh reconhecido! \n",yytext);
										exit(1);
									  }	
				}



.|\n|\r

%%

/* 
   não pode exibir a main aqui se
   não vai dar conflito com a main
   criada pelo analisador sintático! 
*/



