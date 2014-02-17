%{ 


/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 02
   
   
						ANALISADOR SINTÁTICO PARA A LINGUAGEM C-
	     (gramática adaptada do livro de Kenneth C. Louden para aceitar strings)

		 
*/


#include "estruturas.h"
#include "arvoreabstrata.h"

// Cria a função de erro
void yyerror(char *s);

%}


%expect 1


%union{
	int inteiro; 
	char* string;
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
	Tsomaexpressao somaexpressao;
	Tsoma soma;
	Ttermo termo;
	Tmult mult;
	Tfator fator;
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


PROGRAMA : 		DECLARACAOLISTA			{$$ = programa_declist($1);}
;


	
DECLARACAOLISTA :   	DECLARACAOLISTA DECLARACAO	{$$ = declist_declist_decl($1, $2);}
		      | DECLARACAO		  	{$$ = declist_decl($1);}
;


DECLARACAO :   		VARDECLARACAO			{$$ = decl_vardecl($1);}
		      | FUNDECLARACAO		  	{$$ = decl_fundecl($1);}
;


VARDECLARACAO :   	TIPOESPECIFICADOR ID PONTOEVIRGULA	{$$ = vardecl_tesp_id_ptvirg($1, $2);}
		      | TIPOESPECIFICADOR ID ABRECOLCHETE NUM FECHACOLCHETE PONTOEVIRGULA 	
								{$$ = vardecl_tesp_id_acol_num_fcol_ptvirg($1, $2, $4);}
;


TIPOESPECIFICADOR :   	INT				{$$ = tesp("int");}
		      | VOID				{$$ = tesp("void");}
		      | STR				{$$ = tesp("string");}
;


FUNDECLARACAO :   	TIPOESPECIFICADOR ID ABREPARENTESIS PARAMS FECHAPARENTESIS COMPOSTODECL	
							{$$ = fundecl_tesp_id_apar_param_fpar_compdecl($1, $2, $4, $6);}
;


PARAMS :   	PARAMLISTA				{$$ = params_paramlista($1);}
	      | VOID					{$$ = params_void("void");}
	      | 					{$$ = params_vazio();}
;


PARAMLISTA :   	PARAMLISTA VIRGULA PARAM		{$$ = paramlist_parlist_virg_param($1, $3);}
	      | PARAM					{$$ = paramlist_param($1);}
;


PARAM :   	TIPOESPECIFICADOR ID				{$$ = param_tesp_id($1, $2);}
	      | TIPOESPECIFICADOR ID ABRECOLCHETE FECHACOLCHETE	{$$ = param_tesp_id_acol_fcol($1, $2);}
;


COMPOSTODECL :   	ABRECHAVES LOCALDECLARACOES STATEMENTLISTA FECHACHAVES	
							{$$ = compostodecl_achv_localdecl_statmlist_fchv($2, $3);}
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


EXPRESSAODECL :   	EXPRESSAO PONTOEVIRGULA		{$$ = expdecl_exp_ptvirg($1);}
	      	      | PONTOEVIRGULA			{$$ = expdecl_ptvirg();}
;


SELECAODECL :   IF ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT	
							{$$ = seldecl_sem_else($3, $5);}
	      | IF ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT ELSE STATEMENT	
							{$$ = seldecl_com_else($3, $5, $7);}
;	


ITERACAODECL :   WHILE ABREPARENTESIS EXPRESSAO FECHAPARENTESIS STATEMENT	
							{$$ = itdecl_while_apar_exp_fpar_statm($3, $5);}
;


RETORNODECL :   RETURN PONTOEVIRGULA			{$$ = retdecl_sem_expressao();}
	      | RETURN EXPRESSAO PONTOEVIRGULA		{$$ = retdecl_com_expressao($2);}
;


EXPRESSAO :   	VAR ATRIBUICAO EXPRESSAO		{$$ = exp_var_atrib_exp($1, $3);}
	      | SIMPLESEXPRESSAO			{$$ = exp_simplexp($1);}
;


VAR :   	ID					{$$ = var_id($1);}
	      | ID ABRECOLCHETE EXPRESSAO FECHACOLCHETE	{$$ = var_id_acol_exp_fcol($1, $3);}
;


SIMPLESEXPRESSAO :   	SOMAEXPRESSAO RELACIONAL SOMAEXPRESSAO	
							{$$ = simplexp_somaexp_rel_somaexp($1, $2, $3);}
	      	      | SOMAEXPRESSAO			{$$ = simplexp_somaexp($1);}
;


RELACIONAL :   	MENORIGUAL				{$$ = relacional("<=");}
	      | MENOR					{$$ = relacional("<");}
	      | MAIOR					{$$ = relacional(">");}
	      | MAIORIGUAL				{$$ = relacional(">=");}
	      | IGUAL					{$$ = relacional("==");}
	      | DIFERENTE				{$$ = relacional("!=");}
;


SOMAEXPRESSAO :   	SOMAEXPRESSAO SOMA TERMO	{$$ = somaexp_somaexp_soma_termo($1, $2, $3);}
	      	      | TERMO				{$$ = somaexp_termo($1);}
;


SOMA :   	MAIS					{$$ = soma('+');}
	      | MENOS					{$$ = soma('-');}
;


TERMO :   	TERMO MULT FATOR			{$$ = termo_termo_mult_fator($1, $2, $3);}
	      | FATOR					{$$ = termo_fator($1);}
;


MULT :   	ASTERISCO				{$$ = mult('*');}
	      | BARRA					{$$ = mult('/');}
;


FATOR :   	ABREPARENTESIS EXPRESSAO FECHAPARENTESIS	{$$ = fator_apar_exp_fpar($2);}
	      | VAR						{$$ = fator_var($1);}
	      | ATIVACAO					{$$ = fator_ativacao($1);}
	      | NUM						{$$ = fator_num($1);}
	      | STRSTR						{$$ = fator_string($1);}
;


ATIVACAO :   	ID ABREPARENTESIS ARGS FECHAPARENTESIS	{$$ = ativacao_regra($1, $3);}
;


ARGS :   	ARGLISTA				{$$ = args_arglista($1);}
	      | 					{$$ = args_vazio();}
;


ARGLISTA :   	ARGLISTA VIRGULA EXPRESSAO		{$$ = arglista_arglista_virg_exp($1, $3);}
	      | EXPRESSAO				{$$ = arglista_exp($1);}
;


%%

#include <stdlib.h>
#include <stdio.h>

void yyerror(char *s)
{
   fprintf(stderr,"Erro sintático.\n");
   exit(1);
}

main(){	
	
  yyparse();
	
  return 0;
}
