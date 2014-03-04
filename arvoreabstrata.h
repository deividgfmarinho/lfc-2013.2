#ifndef ARVOREABSTRATA_H
#define ARVOREABSTRATA_H

#include "simbolos.h"
#include "util.h"




/* 	
    Deivid Goes Farias Marinho
    201110005298
    Trabalho LFC - Parte 03


			GRAM�TICA ABSTRATA PARA A GRAM�TICA DA LINGUAGEM C-
	(gram�tica adaptada do livro de Kenneth C. Louden para aceitar strings)

	Neste arquivo tamb�m est�o contidos as assinaturas das fun��es para inser��o dos n�s.

*/


/*

PROGRAMA : 		DECLARACAOLISTA			
;


	
DECLARACAOLISTA :   	DECLARACAOLISTA DECLARACAO	
		      | DECLARACAO		  	
;


DECLARACAO :   		VARDECLARACAO		
		      | FUNDECLARACAO		  
;


VARDECLARACAO :   	TIPOESPECIFICADOR ID 
		      | TIPOESPECIFICADOR ID NUM  	
;


FUNDECLARACAO :   	TIPOESPECIFICADOR ID PARAMS COMPOSTODECL	
;


PARAMS :   	PARAMLISTA				
	      | VOID					
	      | 					
;


PARAMLISTA :   	PARAMLISTA PARAM	
	      | PARAM					
;


PARAM :   	TIPOESPECIFICADOR ID


COMPOSTODECL :   	LOCALDECLARACOES STATEMENTLISTA
;


LOCALDECLARACOES :   	LOCALDECLARACOES VARDECLARACAO
	      	      | 				
;


STATEMENTLISTA :   	STATEMENTLISTA STATEMENT	
	      	      | 				
;


STATEMENT :   	EXPRESSAODECL				
	      | COMPOSTODECL				
	      | SELECAODECL				
	      | ITERACAODECL				
	      | RETORNODECL				
;


EXPRESSAODECL :   	EXPRESSAO 
	      	      | 
;


SELECAODECL :   EXPRESSAO STATEMENT	
	      | EXPRESSAO STATEMENT STATEMENT	
;	


ITERACAODECL :   EXPRESSAO STATEMENT	
;


RETORNODECL :   	
	      | EXPRESSAO		
;


EXPRESSAO :   	VAR EXPRESSAO		
	      | SIMPLESEXPRESSAO
;


VAR :   	ID				
	      | ID EXPRESSAO	
;


SIMPLESEXPRESSAO :   	SIMPLESEXPRESSAO RELACIONAL SIMPLESEXPRESSAO		
				  | SIMPLESEXPRESSAO SOMA SIMPLESEXPRESSAO	
				  | SIMPLESEXPRESSAO MULT SIMPLESEXPRESSAO
				  | EXPRESSAO	
				  | VAR						
				  | ATIVACAO		
				  | NUM			
				  | STRSTR 
;


RELACIONAL :   	
;

SOMA :   
;

MULT :   
;


ATIVACAO :   	ID ARGS 
;


ARGS :   	ARGLISTA				
	      | 		  
;


ARGLISTA :   	ARGLISTA EXPRESSAO				
	      | EXPRESSAO		  
;

*/


typedef struct AAprograma *Tprograma;
typedef struct AAdeclaracaolista *Tdeclaracaolista;
typedef struct AAdeclaracao *Tdeclaracao;
typedef struct AAvardeclaracao *Tvardeclaracao;
typedef struct AAfundeclaracao *Tfundeclaracao;
typedef struct AAparams *Tparams;
typedef struct AAparamlista *Tparamlista;
typedef struct AAparam *Tparam;
typedef struct AAcompostodecl *Tcompostodecl;
typedef struct AAlocaldeclaracoes *Tlocaldeclaracoes;
typedef struct AAstatementlista *Tstatementlista;
typedef struct AAstatement *Tstatement;
typedef struct AAexpressaodecl *Texpressaodecl;
typedef struct AAselecaodecl *Tselecaodecl;
typedef struct AAiteracaodecl *Titeracaodecl;
typedef struct AAretornodecl *Tretornodecl;
typedef struct AAexpressao *Texpressao;
typedef struct AAvar *Tvar;
typedef struct AAsimplesexpressao *Tsimplesexpressao;
typedef struct AAativacao *Tativacao;
typedef struct AAargs *Targs;
typedef struct AAarglista *Targlista;

// Enumera��es de tipos que n�o precisam ser estruturas
typedef enum {Tint, Tvoid, Tstring, Tstrint} Ttipoespecificador;  // Tstrint : pode ser string ou int
typedef enum {Tmenorigual, Tmenor, Tmaior, Tmaiorigual, Tigual, Tdiferente} Trelacional;
typedef enum {Tmais, Tmenos} Tsoma;
typedef enum {Tmul, Tdiv} Tmult;



/* programa -> declaracao-lista	*/

struct AAprograma {
	Tdeclaracaolista declist;
};

Tprograma programa_declist(Tdeclaracaolista declist);

/* FIM - programa	*/




/* declaracao-lista -> declaracao-lista declaracao | declaracao	*/

struct AAdeclaracaolista {
	
	enum{Fdeclist_declist_decl, Fdeclist_decl} tipo;

	union{	struct{
			Tdeclaracaolista declist;
			Tdeclaracao decl;
		} Tdeclistdec;
		
		Tdeclaracao decl;

	} uniao;

};

// declaracao-lista -> declaracao-lista declaracao 
Tdeclaracaolista declist_declist_decl(Tdeclaracaolista declist, Tdeclaracao decl);

// declaracao-lista -> declaracao 
Tdeclaracaolista declist_decl(Tdeclaracao decl);

/* FIM - declaracao-lista */




/* declaracao -> var-declaracao | fun-declaracao */

struct AAdeclaracao {
	
	enum{Fdecl_vardecl, Fdecl_fundecl} tipo;

	union{	Tvardeclaracao vardecl; 
		Tfundeclaracao fundecl;

	} uniao;
}; 


// declaracao -> var-declaracao 
Tdeclaracao decl_vardecl(Tvardeclaracao vardecl);

// declaracao -> fun-declaracao 
Tdeclaracao decl_fundecl(Tfundeclaracao fundecl);

/* FIM - declaracao */



/* var-declaracao -> tipo-especificador ID | tipo-especificador ID NUM */

struct AAvardeclaracao{
	
	enum{Fvardecl_tesp_id, Fvardecl_tesp_id_num} tipo;

	union{	struct{
			Ttipoespecificador tesp;
			Simbolo id;
		} Ttesp_id; 

		struct{
			Ttipoespecificador tesp;
			Simbolo id;
			int num;
		} Ttesp_id_num;

	} uniao;
};


// var-declaracao -> tipo-especificador ID 
Tvardeclaracao vardecl_tesp_id(Ttipoespecificador tesp, Simbolo id);

// var-declaracao -> tipo-especificador ID NUM 
Tvardeclaracao vardecl_tesp_id_num(Ttipoespecificador tesp, Simbolo id, int num);

/* FIM - var-declaracao */




/* fun-declara��o -> tipo-especificador ID params composto-decl */

struct AAfundeclaracao {
	
	Ttipoespecificador tesp;
	Simbolo id;
	Tparams params;
	Tcompostodecl compdecl;

};



Tfundeclaracao fundecl_tesp_id_param_compdecl(Ttipoespecificador tesp, Simbolo id, Tparams params, Tcompostodecl compdecl);

/* FIM - fun-declara��o */




/* params -> param-lista | void |  */

struct AAparams {
	
	enum{Fparams_parlist, Fparams_vazio} tipo;
	
	Tparamlista paramlist;

};



// params -> param-lista
Tparams params_paramlista(Tparamlista paramlist);

// params -> void
Tparams params_void();

// params -> 
Tparams params_vazio();

/* FIM - params */




/* param-lista -> param-lista param  | param */

struct AAparamlista {
	
	enum{Fparamlist_parlist_param, Fparamlist_param} tipo;
	
	union{	struct{	Tparamlista paramlist;
			Tparam param;
		} Tparlist_param;

		Tparam param;
	} uniao;
};


// param-lista -> param-lista param
Tparamlista paramlist_parlist_param(Tparamlista paramlist, Tparam param);

// param-lista -> param
Tparamlista paramlist_param(Tparam param);

/* FIM - param-lista -> param-lista param  | param */




/* param -> tipo-especificador ID | tipo-especificador ID */

struct AAparam{
	
	enum{Fparam_sem_colchetes, Fparam_com_colchetes} tipo;
	
	// S� precisa de uma estrutura, mas de dois construtores diferentes
  	// apesar de armazenarem sempre os mesmos argumentos
	Ttipoespecificador tesp;
	Simbolo id;

};


// param -> tipo-especificador ID
Tparam param_sem_colchetes(Ttipoespecificador tesp, Simbolo id);

// param -> tipo-especificador ID
Tparam param_com_colchetes(Ttipoespecificador tesp, Simbolo id);

/* FIM - param-lista */




/* composto-decl -> local-declara��es statement-lista */

struct AAcompostodecl {
	
	Tlocaldeclaracoes localdecl;
	Tstatementlista statementlist;

};


Tcompostodecl compostodecl_regra(Tlocaldeclaracoes localdecl, Tstatementlista statementlist);

/* FIM - composto-decl */




/* local-declara��es -> local-declara��es var-declara��o | vazio */

struct AAlocaldeclaracoes {

	enum{Flocdecl_locdecl_vardecl, Flocdecl_vazio} tipo;

	Tlocaldeclaracoes localdecl;
	Tvardeclaracao vardecl;

};


// local-declara��es -> local-declara��es var-declara��o
Tlocaldeclaracoes localdecl_localdecl_vardecl(Tlocaldeclaracoes localdecl, Tvardeclaracao vardecl);

// local-declara��es -> vazio
Tlocaldeclaracoes localdecl_vazio();

/* FIM - local-declara��es */




/* statement-lista -> statement-lista statement | vazio */

struct AAstatementlista {
	
	enum{Fstatm_statmlist_statm, Fstatm_vazio} tipo;
	
	Tstatementlista statementlist;
	Tstatement statement;

};


// statement-lista -> statement-lista statement
Tstatementlista statmlist_statmlist_statm(Tstatementlista statementlist, Tstatement statement);

// statement-lista -> 
Tstatementlista statmlist_vazio();

/* FIM - statement-lista -> statement-lista statement |  */



/* statement -> express�o-decl | composto-decl | sele��o-decl | itera��o-decl | retorno-decl */

struct AAstatement {
	
	enum{Fstatm_expdecl, Fstatm_compdecl, Fstatm_seldecl, Fstatm_itdecl, Fstatm_retdecl} tipo;
	
	union{	Texpressaodecl expdecl; 
		Tcompostodecl compdecl; 
		Tselecaodecl seldecl; 
		Titeracaodecl itdecl; 
		Tretornodecl retdecl;
	
	} uniao;

};


// statement -> express�o-decl
Tstatement statm_expdecl(Texpressaodecl expdecl);

// statement -> composto-decl
Tstatement statm_compdecl(Tcompostodecl compdecl);

// statement -> sele��o-decl
Tstatement statm_seldecl(Tselecaodecl seldecl);

// statement -> itera��o-decl
Tstatement statm_itdecl(Titeracaodecl itdecl);

// statement -> retorno-decl
Tstatement statm_retdecl(Tretornodecl retdecl);

/* FIM - statement */





/* express�o-decl -> express�o |  */

struct AAexpressaodecl {
	
	enum{Fexpdecl_exp, Fexpdecl_vazio} tipo;
	
	Texpressao exp; 

};


// express�o-decl -> express�o 
Texpressaodecl expdecl_exp(Texpressao exp);

// express�o-decl -> 
Texpressaodecl expdecl_();

/* FIM - express�o-decl */



/* sele��o-decl -> express�o statement | express�o statement statement */

struct AAselecaodecl {
	
	enum{Fseldecl_sem_else, Fseldecl_com_else} tipo;
	
	union{	struct{		
			Texpressao exp;
			Tstatement statement;
		} Tif_sem_else;

		struct{	
			Texpressao exp;
			Tstatement statementif;
			Tstatement statementelse;
		} Tif_com_else;
		
	} uniao;	 

};


// sele��o-decl -> express�o statement
Tselecaodecl seldecl_sem_else(Texpressao exp, Tstatement statement);

// sele��o-decl -> express�o statement statement
Tselecaodecl seldecl_com_else(Texpressao exp, Tstatement statementif, Tstatement statementelse);

/* FIM - sele��o-decl */




/* itera��o-decl -> express�o statement */

struct AAiteracaodecl {
	
	Texpressao exp;
	
	Tstatement statement;	 

};


Titeracaodecl itdecl_regra(Texpressao exp, Tstatement statement);

/* FIM - itera��o-decl  */



/* retorno-decl -> | express�o */

struct AAretornodecl {

	enum{Fretdecl_, Fretdecl_exp} tipo;
	
	Texpressao exp;	 

};


// retorno-decl -> 
Tretornodecl retdecl_sem_expressao();

// retorno-decl -> express�o 
Tretornodecl retdecl_com_expressao(Texpressao exp);

/* FIM - retorno-decl */



/* express�o -> var express�o | simples-express�o */

struct AAexpressao {
	
	enum{Fexp_var_exp, Fexp_simplexp} tipo;
	
	union{	struct{	Tvar var;
			Texpressao exp;
		} Tvar_exp;

		Tsimplesexpressao simplexp;
		
	} uniao; 

};


// express�o -> var = express�o
Texpressao exp_var_exp(Tvar var, Texpressao exp);

// express�o -> simples-express�o
Texpressao exp_simplexp(Tsimplesexpressao simplexp);

/* FIM - express�o -> var = express�o | simples-express�o */



/* var -> ID | ID express�o */

struct AAvar {
	
	enum{Fvar_id, Fvar_id_exp} tipo;
	
	union{	Simbolo id;
		struct{	Simbolo id;
			Texpressao exp;
		} Tid_exp;
		
	} uniao; 

};


// var -> ID
Tvar var_id(Simbolo id);

// var -> ID express�o
Tvar var_id_exp(Simbolo id, Texpressao exp);

/* FIM - var -> ID | ID express�o */



/* simples-express�o -> simples-express�o relacional simples-express�o		
					  | simples-express�o soma simples-express�o	
					  | simples-express�o mult simples-express�o
					  | express�o	
					  | var				
					  | ativa��o		
					  | num			
					  | stringValue    */

struct AAsimplesexpressao {
	
	enum{Fsimplexp_simplexp_rel_simplexp, 
		 Fsimplexp_simplexp_soma_simplexp,
		 Fsimplexp_simplexp_mult_simplexp,
		 Fsimplexp_exp,
		 Fsimplexp_var,
		 Fsimplexp_ativacao,
		 Fsimplexp_num,
		 Fsimplexp_str} tipo;
	
	union{	struct{	Tsimplesexpressao simplexp1;
			Trelacional rel;
			Tsimplesexpressao simplexp2;
		} Tsimplexp_rel_simplexp;
		
		struct{	Tsimplesexpressao simplexp1;
			Tsoma soma;
			Tsimplesexpressao simplexp2;
		} Tsimplexp_soma_simplexp;
		
		struct{	Tsimplesexpressao simplexp1;
			Tmult mult;
			Tsimplesexpressao simplexp2;
		} Tsimplexp_mult_simplexp;
		
		Texpressao exp; 
		
		Tvar var;
		
		Tativacao ativacao; 
		
		int num;
		
		string str;	
		
	} uniao; 

}; 


// simples-express�o -> simples-express�o relacional simples-express�o
Tsimplesexpressao simplexp_simplexp_rel_simplexp(Tsimplesexpressao simplexp1, Trelacional rel, Tsimplesexpressao simplexp2);

// simples-express�o -> simples-express�o soma simples-express�o
Tsimplesexpressao simplexp_simplexp_soma_simplexp(Tsimplesexpressao simplexp1, Tsoma soma, Tsimplesexpressao simplexp2);

// simples-express�o -> simples-express�o mult simples-express�o
Tsimplesexpressao simplexp_simplexp_mult_simplexp(Tsimplesexpressao simplexp1, Tmult mult, Tsimplesexpressao simplexp2);

// simples-express�o -> express�o
Tsimplesexpressao simplexp_exp(Texpressao exp);

// simples-express�o -> var
Tsimplesexpressao simplexp_var(Tvar var);

// simples-express�o -> ativa��o
Tsimplesexpressao simplexp_ativacao(Tativacao ativacao);

// simples-express�o -> NUM
Tsimplesexpressao simplexp_num(int num);

// simples-express�o -> stringValue
Tsimplesexpressao simplexp_string(string str);

/* FIM - simples-express�o */





/* ativa��o -> ID args */

struct AAativacao {
	
	Simbolo id; 
	
	Targs args;	

};


Tativacao ativacao_regra(Simbolo id, Targs args);

/* FIM - ativa��o */




/* args -> arg-lista | */

struct AAargs {
	
	enum{Fargs_arglist, Fargs_vazio} tipo;
	
	Targlista arglista; 

};


// args -> arg-lista
Targs args_arglista(Targlista arglista);

// args -> 
Targs args_vazio();

/* FIM - args */



/* arg-lista -> arg-lista express�o | express�o */

struct AAarglista {
	
	enum{Farglista_arglista_exp, Farglista_exp} tipo;
	
	union{	struct{	Targlista arglista;
			Texpressao exp;
		} Targlista_exp; 
		Texpressao exp;	
	} uniao; 

};


// arg-lista -> arg-lista express�o
Targlista arglista_arglista_exp(Targlista arglista, Texpressao exp);

// arg-lista -> express�o
Targlista arglista_exp(Texpressao exp);

/* FIM - arglista */






// destrui a �rvore
void destroiArvore(Tprograma programa);
void destroiDecList(Tdeclaracaolista declist);
void destroiDecl(Tdeclaracao decl);
void destroiVarDecl(Tvardeclaracao vardecl);
void destroiFunDecl(Tfundeclaracao fundecl);
void destroiParams(Tparams params);
void destroiParamList(Tparamlista paramlist);
void destroiParam(Tparam param);
void destroiCompDecl(Tcompostodecl compdecl);
void destroiLocalDecl(Tlocaldeclaracoes localdecl);
void destroiStatmList(Tstatementlista statementlist);
void destroiStatm(Tstatement statement);
void destroiExpDecl(Texpressaodecl expdecl);
void destroiSelDecl(Tselecaodecl seldecl);
void destroiItDecl(Titeracaodecl itdecl);
void destroiRetDecl(Tretornodecl retdecl);
void destroiExp(Texpressao exp);
void destroiVar(Tvar var);
void destroiSimplExp(Tsimplesexpressao simplexp);
void destroiAtivacao(Tativacao ativacao);
void destroiArgs(Targs args);
void destroiArgList(Targlista arglista);




#endif
