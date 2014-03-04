%{ 


/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 03
   
   
				ANALISADOR SINTÁTICO E SEMÂNTICO PARA A LINGUAGEM C-
	     (gramática adaptada do livro de Kenneth C. Louden para aceitar strings)

		 
*/


#include "semantico.c"
#include "arvoreabstrata.h"
#include "arvoreabstrata.c"
#include "util.h"


Tprograma program;

%}

%expect 1


%union{
	int inteiro; 
	char* cstring;
	Tprograma programa;
	Tdeclaracaolista declaracaolista;
	Tdeclaracao declaracao; 
	Tvardeclaracao vardeclaracao;
	Ttipoespecificador tipoespecificador;
	Tfundeclaracao fundeclaracao;
	Tparams params;
	Tparamlista paramlista;
	Tparam param;
	Tcompostodecl compostodecl;
	Tlocaldeclaracoes localdeclaracoes;
	Tstatementlista statementlista;
	Tstatement statement;
	Texpressaodecl expressaodecl;
	Tselecaodecl selecaodecl;
	Titeracaodecl iteracaodecl;
	Tretornodecl retornodecl;
	Texpressao expressao;
	Tvar var; 
	Tsimplesexpressao simplesexpressao; 
	Trelacional relacional;
	Tsoma soma;
	Tmult mult;
	Tativacao ativacao;
	Targs args;
	Targlista arglista;
};



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
%token <cstring> STRSTR
%token <cstring> ID 	

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
%type <simplesexpressao> SIMPLESEXPRESSAO SOMAEXPRESSAO TERMO FATOR
%type <relacional> RELACIONAL
%type <soma> SOMA
%type <mult> MULT
%type <ativacao> ATIVACAO
%type <args> ARGS
%type <arglista> ARGLISTA


%start PROGRAMA


%%


PROGRAMA : 		DECLARACAOLISTA			{program = programa_declist($1);
										 $$ = program;}
;


	
DECLARACAOLISTA :   	DECLARACAOLISTA DECLARACAO	{$$ = declist_declist_decl($1, $2);}
		      | DECLARACAO		  	{$$ = declist_decl($1);}
;


DECLARACAO :   		VARDECLARACAO			{$$ = decl_vardecl($1);}
		      | FUNDECLARACAO		  	{$$ = decl_fundecl($1);}
;


VARDECLARACAO :   	TIPOESPECIFICADOR ID PONTOEVIRGULA	{$$ = vardecl_tesp_id($1, getSimbolo($2));}
		      | TIPOESPECIFICADOR ID ABRECOLCHETE NUM FECHACOLCHETE PONTOEVIRGULA 	
								{$$ = vardecl_tesp_id_num($1, getSimbolo($2), $4);}
;


TIPOESPECIFICADOR :   	INT				{$$ = Tint;}
		      | VOID				{$$ = Tvoid;}
		      | STR				{$$ = Tstring;}
;


FUNDECLARACAO :   	TIPOESPECIFICADOR ID ABREPARENTESIS PARAMS FECHAPARENTESIS COMPOSTODECL	
							{$$ = fundecl_tesp_id_param_compdecl($1, getSimbolo($2), $4, $6);}
;


PARAMS :   	PARAMLISTA				{$$ = params_paramlista($1);}
	      | VOID					{$$ = params_void();}
	      | 					{$$ = params_vazio();}
;


PARAMLISTA :   	PARAMLISTA VIRGULA PARAM		{$$ = paramlist_parlist_param($1, $3);}
	      | PARAM					{$$ = paramlist_param($1);}
;


PARAM :   	TIPOESPECIFICADOR ID				{$$ = param_sem_colchetes($1, getSimbolo($2));}
	      | TIPOESPECIFICADOR ID ABRECOLCHETE FECHACOLCHETE	{$$ = param_com_colchetes($1, getSimbolo($2));}
;


COMPOSTODECL :   	ABRECHAVES LOCALDECLARACOES STATEMENTLISTA FECHACHAVES	
							{$$ = compostodecl_regra($2, $3);}
;


LOCALDECLARACOES :   	LOCALDECLARACOES VARDECLARACAO	{$$ = localdecl_localdecl_vardecl($1, $2);}
	      	      | 				{$$ = localdecl_vazio();}
;


STATEMENTLISTA :   	STATEMENTLISTA STATEMENT	{$$ = statmlist_statmlist_statm($1, $2);}
	      	      | 				{$$ = statmlist_vazio();}
;


STATEMENT :   	EXPRESSAODECL				{$$ = statm_expdecl($1);}
	      | COMPOSTODECL				{$$ = statm_compdecl($1);}
	      | SELECAODECL				{$$ = statm_seldecl($1);}
	      | ITERACAODECL				{$$ = statm_itdecl($1);}
	      | RETORNODECL				{$$ = statm_retdecl($1);}
;


EXPRESSAODECL :   	EXPRESSAO PONTOEVIRGULA		{$$ = expdecl_exp($1);}
	      	      | PONTOEVIRGULA			{$$ = expdecl_();}
;


SELECAODECL :   IF ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT	
							{$$ = seldecl_sem_else($3, $5);}
	      | IF ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT ELSE STATEMENT	
							{$$ = seldecl_com_else($3, $5, $7);}
;	


ITERACAODECL :   WHILE ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT	
							{$$ = itdecl_regra($3, $5);}
;


RETORNODECL :   RETURN PONTOEVIRGULA			{$$ = retdecl_sem_expressao();}
	      | RETURN EXPRESSAO PONTOEVIRGULA		{$$ = retdecl_com_expressao($2);}
;


EXPRESSAO :   	VAR ATRIBUICAO EXPRESSAO		{$$ = exp_var_exp($1, $3);}
	      | SIMPLESEXPRESSAO			{$$ = exp_simplexp($1);}
;


VAR :   	ID					{$$ = var_id(getSimbolo($1));}
	      | ID ABRECOLCHETE EXPRESSAO FECHACOLCHETE	{$$ = var_id_exp(getSimbolo($1), $3);}
;


SIMPLESEXPRESSAO :   	SOMAEXPRESSAO RELACIONAL SOMAEXPRESSAO	
							{$$ = simplexp_simplexp_rel_simplexp($1, $2, $3);}
	      	      | SOMAEXPRESSAO			{$$ = $1;}
;


RELACIONAL :   	MENORIGUAL				{$$ = Tmenorigual;}
	      | MENOR					{$$ = Tmenor;}
	      | MAIOR					{$$ = Tmaior;}
	      | MAIORIGUAL				{$$ = Tmaiorigual;}
	      | IGUAL					{$$ = Tigual;}
	      | DIFERENTE				{$$ = Tdiferente;}
;


SOMAEXPRESSAO :   	SOMAEXPRESSAO SOMA TERMO	{$$ = simplexp_simplexp_soma_simplexp($1, $2, $3);}
	      	      | TERMO				{$$ = $1;}
;


SOMA :   	MAIS					{$$ = Tmais;}
	      | MENOS					{$$ = Tmenos;}
;


TERMO :   	TERMO MULT FATOR			{$$ = simplexp_simplexp_mult_simplexp($1, $2, $3);}
	      | FATOR					{$$ = $1;}
;


MULT :   	ASTERISCO				{$$ = Tmul;}
	      | BARRA					{$$ = Tdiv;}
;


FATOR :   	ABREPARENTESIS EXPRESSAO FECHAPARENTESIS	{$$ = simplexp_exp($2);}
	      | VAR						{$$ = simplexp_var($1);}
	      | ATIVACAO					{$$ = simplexp_ativacao($1);}
	      | NUM						{$$ = simplexp_num($1);}
	      | STRSTR						{$$ = simplexp_string($1);}
;


ATIVACAO :   	ID ABREPARENTESIS ARGS FECHAPARENTESIS	{$$ = ativacao_regra(getSimbolo($1), $3);}
;


ARGS :   	ARGLISTA				{$$ = args_arglista($1);}
	      | 					{$$ = args_vazio();}
;


ARGLISTA :   	ARGLISTA VIRGULA EXPRESSAO		{$$ = arglista_arglista_exp($1, $3);}
	      | EXPRESSAO				{$$ = arglista_exp($1);}
;


%%

#include <stdlib.h>
#include <stdio.h>

yyerror(char *s)
{
   fprintf(stderr,"Erro sintatico\n");
   exit(1);
}

main(){	
	
	// faz a análise sintática, preenchendo
	// a tabela de strings
	int aux = yyparse();
	
	// faz a análise semântica
	if(!aux) 
		semantica_programa(program);
	
	// destrói os símbolos
	destroiSimbolos();
	
	// destrói a árvore abstrata
	destroiArvore(program);
	
	return(0);
}
