
%{ 
/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 02
*/
#include <stdio.h>
#include <stdlib.h> 
#include "estruturas.h"
%}



%union{
	int inteiro; 
	char* string;
	struct AAprograma* programa;
	struct AAdeclaracaolista* declaracaolista;
	struct AAdeclaracao* declaracao; 
	struct AAvardeclaracao* vardeclaracao;
	struct AAtipoespecificador* tipoespecificador;
	struct AAfundeclaracao* fundeclaracao;
	struct AAparams* params;
	struct AAparamlista* paramlista;
	struct AAparam* param;
	struct AAcompostodecl* compostodecl;
	struct AAlocaldeclaracoes* localdeclaracoes;
	struct AAstatementlista* statementlista;
	struct AAstatement* statement;
	struct AAexpressaodecl* expressaodecl;
	struct AAselecaodecl* selecaodecl;
	struct AAiteracaodecl* iteracaodecl;
	struct AAretornodecl* retornodecl;
	struct AAexpressao* expressao;
	struct AAvar* var; 
	struct AAsimplesexpressao* simplesexpressao; 
	struct AArelacional* relacional;
	struct AAsomaexpressao* somaexpressao;
	struct AAsoma* soma;
	struct AAtermo* termo;
	struct AAmult* mult;
	struct AAfator* fator;
	struct AAativacao* ativacao;
	struct AAargs* args;
	struct AAarglista* arglista;
};


%expect 1



%token ELSE 
%token IF 
%token INT 
%token STR
%token RETURN 
%token VOID 
%token WHILE  

%token MAIS 
%token MENOS
%token ASTERISCO 
%token BARRA 
%token MENOR
%token MENORIGUAL
%token MAIOR
%token MAIORIGUAL
%token IGUAL
%token DIFERENTE
%token ATRIBUICAO
%token PONTOEVIRGULA
%token VIRGULA
%token ABREPARENTESIS
%token FECHAPARENTESIS
%token ABRECOLCHETE
%token FECHACOLCHETE
%token ABRECHAVES
%token FECHACHAVES

%token <inteiro> NUM 
%token <string> STRSTR
%token <string> ID 	

%type <programa> PROGRAMA
%type <declaracaolista> DECLARACAOLISTA
%type <declaracao> DECLARACAO 
%type <vardeclaracao> VARDECLARACAO
%type <tipoespecificador> TIPOESPECIFICADOR
%type <fundeclaracao> FUNDECLARACAO
%type <params> PARAMS
%type <paramlista> PARAMLISTA
%type <param> PARAM
%type <compostodecl> COMPOSTODECL
%type <localdeclaracoes> LOCALDECLARACOES
%type <statementlista> STATEMENTLISTA
%type <statement> STATEMENT
%type <expressaodecl> EXPRESSAODECL
%type <selecaodecl> SELECAODECL
%type <iteracaodecl> ITERACAODECL 
%type <retornodecl> RETORNODECL
%type <expressao> EXPRESSAO
%type <var> VAR 
%type <simplesexpressao> SIMPLESEXPRESSAO 
%type <relacional> RELACIONAL
%type <somaexpressao> SOMAEXPRESSAO
%type <soma> SOMA
%type <termo> TERMO
%type <mult> MULT
%type <fator> FATOR
%type <ativacao> ATIVACAO
%type <args> ARGS
%type <arglista> ARGLISTA


%start PROGRAMA


%%


PROGRAMA : 		DECLARACAOLISTA			{printf ("\tPROGRAMA -> DECLARACAOLISTA\n");}
;


	
DECLARACAOLISTA :   	DECLARACAOLISTA DECLARACAO	{printf ("\tDECLARACAOLISTA -> DECLARACAOLISTA DECLARACAO\n");}
		      | DECLARACAO		  	{printf ("\tDECLARACAOLISTA -> DECLARACAO\n");}
;


DECLARACAO :   		VARDECLARACAO			{printf ("\tDECLARACAO -> VARDECLARACAO\n");}
		      | FUNDECLARACAO		  	{printf ("\tDECLARACAO -> FUNDECLARACAO\n");}
;


VARDECLARACAO :   	TIPOESPECIFICADOR ID PONTOEVIRGULA	{printf ("\tVARDECLARACAO -> TIPOESPECIFICADOR ID PONTOEVIRGULA\n");}
		      | TIPOESPECIFICADOR ID ABRECOLCHETE NUM FECHACOLCHETE PONTOEVIRGULA 	{printf ("\tVARDECLARACAO -> TIPOESPECIFICADOR ID ABRECOLCHETES NUM FECHACOLCHETES PONTOEVIRGULA\n");}
;


TIPOESPECIFICADOR :   	INT				{printf ("\tTIPOESPECIFICADOR -> INT\n");}
		      | VOID				{printf ("\tTIPOESPECIFICADOR -> VOID\n");}
		      | STR				{printf ("\tTIPOESPECIFICADOR -> STRING\n");}
;


FUNDECLARACAO :   	TIPOESPECIFICADOR ID ABREPARENTESIS PARAMS FECHAPARENTESIS COMPOSTODECL	{printf ("\tFUNDECLARACAO -> TIPOESPECIFICADOR ID ABREPARENTESIS PARAMS FECHAPARENTESIS COMPOSTODECL\n");}
;


PARAMS :   	PARAMLISTA				{printf ("\tPARAMS -> PARAMLISTA\n");}
	      | VOID					{printf ("\tPARAMS -> VOID\n");}
	      | 					{printf ("\tPARAMS -> VAZIO\n");}
;


PARAMLISTA :   	PARAMLISTA VIRGULA PARAM		{printf ("\tPARAMLISTA -> PARAMLISTA VIRGULA PARAM\n");}
	      | PARAM					{printf ("\tPARAMLISTA -> PARAMS\n");}
;


PARAM :   	TIPOESPECIFICADOR ID				{printf ("\tPARAM -> TIPOESPECIFICADOR ID\n");}
	      | TIPOESPECIFICADOR ID ABRECOLCHETE FECHACOLCHETE	{printf ("\tPARAM -> TIPOESPECIFICADOR ID ABRECOLCHETE FECHACOLCHETE\n");}
;


COMPOSTODECL :   	ABRECHAVES LOCALDECLARACOES STATEMENTLISTA FECHACHAVES	{printf ("\tCOMPOSTODECL -> ABRECHAVES LOCALDECLARACOES STATEMENTLISTA FECHACHAVES\n");}
;


LOCALDECLARACOES :   	LOCALDECLARACOES VARDECLARACAO	{printf ("\tLOCALDECLARACOES -> LOCALDECLARACOES VARDECLARACAO\n");}
	      	      | 				{printf ("\tLOCALDECLARACOES -> vazio\n");}
;


STATEMENTLISTA :   	STATEMENTLISTA STATEMENT	{printf ("\tSTATEMENTLISTA -> STATEMENTLISTA STATEMENT\n");}
	      	      | 				{printf ("\tSTATEMENTLISTA -> vazio\n");}
;


STATEMENT :   	EXPRESSAODECL				{printf ("\tSTATEMENT -> EXPRESSAODECL\n");}
	      | COMPOSTODECL				{printf ("\tSTATEMENT -> COMPOSTODECL\n");}
	      | SELECAODECL				{printf ("\tSTATEMENT -> SELECAODECL\n");}
	      | ITERACAODECL				{printf ("\tSTATEMENT -> ITERACAODECL\n");}
	      | RETORNODECL				{printf ("\tSTATEMENT -> RETORNODECL\n");}
;


EXPRESSAODECL :   	EXPRESSAO PONTOEVIRGULA		{printf ("\tEXPRESSAODECL -> EXPRESSAO PONTOEVIRGULA\n");}
	      	      | PONTOEVIRGULA	{printf ("\tEXPRESSAODECL -> PONTOEVIRGULA\n");}
;


SELECAODECL :   IF ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT	{printf ("\tSELECAODECL -> IF ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT\n");}
	      | IF ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT ELSE STATEMENT	{printf ("\tSELECAODECL -> IF ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT ELSE STATEMENT\n");}
;


ITERACAODECL :   WHILE ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT	{printf ("\tITERACAODECL -> WHILE ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT\n");}
;


RETORNODECL :   RETURN PONTOEVIRGULA			{printf ("\tRETORNODECL -> RETURN PONTOEVIRGULA\n");}
	      | RETURN EXPRESSAO PONTOEVIRGULA		{printf ("\tRETORNODECL -> RETURN EXPRESSAO PONTOEVIRGULA\n");}
;


EXPRESSAO :   	VAR ATRIBUICAO EXPRESSAO		{printf ("\tEXPRESSAO-> VAR ATRIBUICAO EXPRESSAO\n");}
	      | SIMPLESEXPRESSAO			{printf ("\tEXPRESSAO -> SIMPLESEXPRESSAO\n");}
;


VAR :   	ID					{printf ("\tVAR -> ID\n");}
	      | ID ABRECOLCHETE EXPRESSAO FECHACOLCHETE	{printf ("\tVAR -> ID ABRECOLCHETE EXPRESSAO FECHACOLCHETE\n");}
;


SIMPLESEXPRESSAO :   	SIMPLESEXPRESSAO RELACIONAL SOMAEXPRESSAO	{printf ("\tSIMPLESEXPRESSAO -> SIMPLESEXPRESSAO RELACIONAL SOMAEXPRESSAO\n");}
	      	      | SOMAEXPRESSAO					{printf ("\tSIMPLESEXPRESSAO -> SOMAEXPRESSAO\n");}
;


RELACIONAL :   	MENORIGUAL				{printf ("\tRELACIONAL -> MENORIGUAL\n");}
	      | MENOR					{printf ("\tRELACIONAL -> MENOR\n");}
	      | MAIOR					{printf ("\tRELACIONAL -> MAIOR\n");}
	      | MAIORIGUAL				{printf ("\tRELACIONAL -> MAIORIGUAL\n");}
	      | IGUAL					{printf ("\tRELACIONAL -> IGUAL\n");}
	      | DIFERENTE				{printf ("\tRELACIONAL -> DIFERENTE\n");}
;


SOMAEXPRESSAO :   	SOMAEXPRESSAO SOMA TERMO	{printf ("\tSOMAEXPRESSAO -> SOMAEXPRESSAO SOMA TERMO\n");}
	      	      | TERMO				{printf ("\tSOMAEXPRESSAO -> TERMO\n");}
;


SOMA :   	MAIS					{printf ("\tSOMA -> MAIS\n");}
	      | MENOS					{printf ("\tSOMA -> MENOS\n");}
;


TERMO :   	TERMO MULT FATOR			{printf ("\tTERMO -> TERMO MULT FATOR\n");}
	      | FATOR					{printf ("\tTERMO -> FATOR\n");}
;


MULT :   	ASTERISCO				{printf ("\tMULT -> ASTERISCO\n");}
	      | BARRA					{printf ("\tMULT -> BARRA\n");}
;


FATOR :   	ABREPARENTESIS EXPRESSAO FECHAPARENTESIS	{printf ("\tFATOR -> ABREPARENTESIS EXPRESSAO FECHAPARENTESIS\n");}
	      | VAR						{printf ("\tFATOR -> VAR\n");}
	      | ATIVACAO					{printf ("\tFATOR -> ATIVACAO\n");}
	      | NUM						{printf ("\tFATOR -> NUM\n");}
	      | STRSTR						{printf ("\tFATOR -> \"STRING\"\n");}
;


ATIVACAO :   	ID ABREPARENTESIS ARGS FECHAPARENTESIS	{printf ("\tATIVACAO -> ID ABREPARENTESIS ARGS FECHAPARENTESIS\n");}
;


ARGS :   	ARGLISTA				{printf ("\tSOMA -> ARGLISTA\n");}
	      | 					{printf ("\tARGS -> vazio\n");}
;


ARGLISTA :   	ARGLISTA VIRGULA EXPRESSAO		{printf ("\tARGLISTA -> ARGLISTA VIRGULA EXPRESSAO\n");}
	      | EXPRESSAO				{printf ("\tARGLISTA -> EXPRESSAO\n");}
;


%%

main(){	
	
  yyparse();
	
  return 0;
}


int yyerror(char* s){
  printf("Erro:  %s\n", s);
  return 0;
}
