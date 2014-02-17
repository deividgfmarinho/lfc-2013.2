#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


/* 	
    Deivid Goes Farias Marinho
    201110005298
    Trabalho LFC - Parte 02


	ESTRUTURAS USADAS PARA A GRAM�TICA LIVRE DE CONTEXTO PARA A LINGUAGEM C-
	(gram�tica adaptada do livro de Kenneth C. Louden para aceitar strings)

	Neste arquivo tamb�m est�o contidos as assinaturas das fun��es para inser��o dos n�s.

*/


typedef struct AAprograma *Tprograma;
typedef struct AAdeclaracaolista *Tdeclaracaolista;
typedef struct AAdeclaracao *Tdeclaracao;
typedef struct AAvardeclaracao *Tvardeclaracao;
typedef struct AAtipoespecificador *Ttipoespecificador;
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
typedef struct AArelacional *Trelacional;
typedef struct AAsomaexpressao *Tsomaexpressao;
typedef struct AAsoma *Tsoma;
typedef struct AAtermo *Ttermo;
typedef struct AAmult *Tmult;
typedef struct AAfator *Tfator;
typedef struct AAativacao *Tativacao;
typedef struct AAargs *Targs;
typedef struct AAarglista *Targlista;





/* programa -> declaracao-lista	*/

struct AAprograma {
	Tdeclaracaolista declist;
};


/* Cria a chamada do m�todo 
   A implementa��o do m�todo 
   est� em "arvoreabstrata.c" */
Tprograma programa_declist(Tdeclaracaolista declist);

/* FIM - programa -> declaracao-lista	*/




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


	/* Cria os m�todos para cada regra */

// declaracao-lista -> declaracao-lista declaracao 
Tdeclaracaolista declist_declist_decl(Tdeclaracaolista declist, Tdeclaracao decl);

// declaracao-lista -> declaracao 
Tdeclaracaolista declist_decl(Tdeclaracao decl);

/* FIM - declaracao-lista -> declaracao-lista declaracao | declaracao */




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

/* FIM - declaracao -> var-declaracao | fun-declaracao */



/* var-declaracao -> tipo-especificador ID ; | tipo-especificador ID [ NUM ] ; */

struct AAvardeclaracao{
	
	enum{Fvardecl_tesp_id_ptvirg, Fvardecl_tesp_id_acol_num_fcol_ptvirg} tipo;

	union{	struct{
			Ttipoespecificador tesp;
			char* id;
			// o ponto-e-v�rgula n�o precisa ser armazenado ?
		} T_tesp_id_ptvirg; 

		struct{
			Ttipoespecificador tesp;
			char* id;
			// o ponto-e-v�rgula e os colchetes n�o precisam ser armazenados ?
			int num;
		} T_tesp_id_acol_num_fcol_ptvirg;

	} uniao;
};


// var-declaracao -> tipo-especificador ID ;
Tvardeclaracao vardecl_tesp_id_ptvirg(Ttipoespecificador tesp, char* id);

// var-declaracao -> tipo-especificador ID [ NUM ] ;
Tvardeclaracao vardecl_tesp_id_acol_num_fcol_ptvirg(Ttipoespecificador tesp, char* id, int num);

/* FIM - var-declaracao -> tipo-especificador ID ; | tipo-especificador ID [ NUM ] ; */




/* tipo-especificador -> int | void | string */

struct AAtipoespecificador{
	
	// como os tr�s s�o do mesmo tipo (char*), n�o precisa usar uni�o
	// j� que nesse caso n�o h� polimorfismo
	// mas � necess�rio dois construtores diferentes para saber
	// qual foi o tipo especificador
	char* tesp;

};


Ttipoespecificador tesp(char* tesp);

/* FIM - tipo-especificador -> int | void | string  */




/* fun-declara��o -> tipo-especificador ID ( params ) composto-decl */

struct AAfundeclaracao {
	
	struct{	Ttipoespecificador tesp;
		char* id;
		// parenteses n�o precisam ser armazenados ?
		Tparams params;
		Tcompostodecl compdecl;
	} tesp_id_apar_param_fpar_compdecl;
};



Tfundeclaracao fundecl_tesp_id_apar_param_fpar_compdecl(Ttipoespecificador tesp, char* id, Tparams params, Tcompostodecl compdecl);

/* FIM - fun-declara��o -> tipo-especificador ID ( params ) composto-decl */




/* params -> param-lista | void | vazio */

struct AAparams {
	
	enum{Fparams_paramlista, Fparams_void} tipo;

	union{	Tparamlista paramlist;
		char* tvoid;
	} uniao;
};



// params -> param-lista
Tparams params_paramlista(Tparamlista paramlist);

// params -> void
Tparams params_void(char* tvoid);

// params -> vazio
Tparams params_vazio();

/* FIM - params -> param-lista | void */




/* param-lista -> param-lista, param  | param */

struct AAparamlista {
	
	enum{Fparamlist_parlist_virg_param, Fparamlist_param} tipo;
	
	union{	struct{	Tparamlista paramlist;
			// virgula n�o precisa ser armazenada?
			Tparam param;
		} Tparlist_virg_param;

		Tparam param;
	} uniao;
};


// param-lista -> param-lista, param
Tparamlista paramlist_parlist_virg_param(Tparamlista paramlist, Tparam param);

// param-lista -> param
Tparamlista paramlist_param(Tparam param);

/* FIM - param-lista -> param-lista, param  | param */




/* param -> tipo-especificador ID | tipo-especificador ID [] */

struct AAparam{
	
	enum{Fparam_tesp_id, Fparam_tesp_id_acol_fcol} tipo;
	
	// S� precisa de uma estrutura, mas de dois construtores diferentes
  	// apesar de armazenarem sempre os mesmos argumentos
	struct{	Ttipoespecificador tesp;
		char* id;
	
	} Ttesp_id;
};


// param -> tipo-especificador ID
Tparam param_tesp_id(Ttipoespecificador tesp, char* id);

// param -> tipo-especificador ID []
Tparam param_tesp_id_acol_fcol(Ttipoespecificador tesp, char* id);

/* FIM - param-lista -> param-lista, param  | param */




/* composto-decl -> { local-declara��es statement-lista } */

struct AAcompostodecl {
	
	struct{	// colchetes devem ser ignorados?
		Tlocaldeclaracoes localdecl;
		Tstatementlista statementlist;
	} Tachv_localdecl_statmlist_fchv;
};


Tcompostodecl compostodecl_achv_localdecl_statmlist_fchv(Tlocaldeclaracoes localdecl, Tstatementlista statementlist);

/* FIM - composto-decl -> { local-declara��es statement-lista } */




/* local-declara��es -> local-declara��es var-declara��o | vazio */

struct AAlocaldeclaracoes {

	struct{	Tlocaldeclaracoes localdecl;
		Tvardeclaracao vardecl;
	} Tachv_localdecl_vardecl;

};


// local-declara��es -> local-declara��es var-declara��o
Tlocaldeclaracoes localdecl_localdecl_vardecl(Tlocaldeclaracoes localdecl, Tvardeclaracao vardecl);

// local-declara��es -> vazio
Tlocaldeclaracoes localdecl_vazio();

/* FIM - local-declara��es -> local-declara��es var-declara��o | vazio */




/* statement-lista -> statement-lista statement | vazio */

struct AAstatementlista {
	
	struct{	Tstatementlista statementlist;
		Tstatement statement;
	
	} Tstatmlist_statm;

};


// statement-lista -> statement-lista statement
Tstatementlista statmlist_statmlist_statm(Tstatementlista statementlist, Tstatement statement);

// statement-lista -> vazio
Tstatementlista statmlist_vazio();

/* FIM - statement-lista -> statement-lista statement | vazio */



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

/* FIM - statement -> express�o-decl | composto-decl | sele��o-decl | itera��o-decl | retorno-decl */





/* express�o-decl -> express�o ; | ; */

struct AAexpressaodecl {
	
	Texpressao exp; 

};


// express�o-decl -> express�o ;
Texpressaodecl expdecl_exp_ptvirg(Texpressao exp);

// express�o-decl -> ;
Texpressaodecl expdecl_ptvirg();

/* FIM - express�o-decl -> express�o ; | ; */



/* sele��o-decl -> if ( express�o ) statement |  if ( express�o ) statement else statement */

struct AAselecaodecl {
	
	enum{Fseldecl_sem_else, Fseldecl_com_else} tipo;
	
	union{	struct{	// parenteses e "if" ignorados?	
			Texpressao exp;
			Tstatement statement;
		} Tif_sem_else;

		struct{	// parenteses, "if" e "else" ignorados?	
			Texpressao exp;
			Tstatement statementif;
			Tstatement statementelse;
		} Tif_com_else;
		
	} uniao;	 

};


// sele��o-decl -> if ( express�o ) statement
Tselecaodecl seldecl_sem_else(Texpressao exp, Tstatement statement);

// sele��o-decl -> if ( express�o ) statement else statement
Tselecaodecl seldecl_com_else(Texpressao exp, Tstatement statementif, Tstatement statementelse);

/* FIM - sele��o-decl -> if ( express�o ) statement |  if ( express�o ) statement else statement */




/* itera��o-decl -> while ( express�o ) statement */

struct AAiteracaodecl {
	
	struct{	// parenteses e "while" ignorados?	
		Texpressao exp;
		Tstatement statement;
		
	} Twhile_apar_exp_fpar_statm;	 

};


Titeracaodecl itdecl_while_apar_exp_fpar_statm(Texpressao exp, Tstatement statement);

/* FIM - itera��o-decl -> while ( express�o ) statement */



/* retorno-decl -> return ; | return express�o ; */

struct AAretornodecl {

	// "return" e "ponto-e-v�rgula" ignorados?
	Texpressao exp;	 

};


// retorno-decl -> return ;
Tretornodecl retdecl_sem_expressao();

// return express�o ;
Tretornodecl retdecl_com_expressao(Texpressao exp);

/* FIM - retorno-decl -> return ; | return express�o ; */



/* express�o -> var = express�o | simples-express�o */

struct AAexpressao {
	
	enum{Fexp_var_atrib_exp, Fexp_simplexp} tipo;
	
	union{	struct{	Tvar var;
			// atribui��o ignorada?
			Texpressao exp;
		} Tvar_atrib_exp;

		Tsimplesexpressao simplexp;
		
	} uniao; 

};


// express�o -> var = express�o
Texpressao exp_var_atrib_exp(Tvar var, Texpressao exp);

// express�o -> simples-express�o
Texpressao exp_simplexp(Tsimplesexpressao simplexp);

/* FIM - express�o -> var = express�o | simples-express�o */



/* var -> ID | ID [ express�o ] */

struct AAvar {
	
	enum{Fvar_id, Fvar_id_acol_exp_fcol} tipo;
	
	union{	char* id;
		struct{	char* id;
			// colchetes ignorados?
			Texpressao exp;
		} Tid_acol_exp_fcol;
		
	} uniao; 

};


// var -> ID
Tvar var_id(char* id);

// var -> ID [ express�o ]
Tvar var_id_acol_exp_fcol(char* id, Texpressao exp);

/* FIM - var -> ID | ID [ express�o ] */



/* simples-express�o -> soma-express�o relacional soma-express�o | soma-express�o */

struct AAsimplesexpressao {
	
	enum{Fsimplexp_somaexp_rel_somaexp, Fsimplexp_somaexp} tipo;
	
	union{	struct{	Tsomaexpressao somaexp1;
			Trelacional rel;
			Tsomaexpressao somaexp2;
		} TTsomaexp_rel_somexp;
		
		Tsomaexpressao somaexp;
		
	} uniao; 

}; 


// simples-express�o -> soma-express�o relacional soma-express�o
Tsimplesexpressao simplexp_somaexp_rel_somaexp(Tsomaexpressao somaexp1, Trelacional rel, Tsomaexpressao somaexp2);

// simples-express�o -> soma-express�o 
Tsimplesexpressao simplexp_somaexp(Tsomaexpressao somaexp);

/* FIM - simples-express�o -> soma-express�o relacional soma-express�o | soma-express�o */
 



/* relacional -> <= | < | > | >= | == | != */

struct AArelacional {
	
	char* rel;

};



Trelacional relacional(char* rel);

/* FIM - relacional -> <= | < | > | >= | == | != */




/* soma-express�o -> soma-express�o soma termo | termo */

struct AAsomaexpressao {
	
	enum{Fsomaexp_somaexp_soma_termo, Fsimplexp_termo} tipo;
	
	union{	struct{	Tsomaexpressao somaexp;
			Tsoma soma;
			Ttermo termo;
		} TTsomaexp_rel_somexp;
		
		Ttermo termo;
		
	} uniao; 

};


// soma-express�o -> soma-express�o soma termo
Tsomaexpressao somaexp_somaexp_soma_termo(Tsomaexpressao somaexp, Tsoma soma, Ttermo termo);

// soma-express�o -> termo
Tsomaexpressao somaexp_termo(Ttermo termo);

/* FIM - soma-express�o -> soma-express�o soma termo | termo */



/* soma -> + | - */

struct AAsoma {
	
	char op;

};


Tsoma soma(char op);

/* FIM - soma -> + | - */



/* termo -> termo mult fator | fator */

struct AAtermo {
	
	enum{Ftermo_termo_mult_fator, Ftermo_fator} tipo;
	
	union{	struct{	Ttermo termo;
			Tmult mult;
			Tfator fator;
		} Ttermo_mult_fator;
		
		Tfator fator;
		
	} uniao; 

};


// termo -> termo mult fator
Ttermo termo_termo_mult_fator(Ttermo termo, Tmult mult, Tfator fator);

// termo -> fator
Ttermo termo_fator(Tfator fator);

/* FIM - termo -> termo mult fator | fator */




/* mult -> * | / */

struct AAmult {
	
	char op;

};

Tmult mult(char op);

/* FIM - mult -> * | / */



/* fator -> ( express�o ) | var | ativa��o | NUM | STRING */

struct AAfator {
	
	enum{Ffator_apar_exp_fpar, Ffator_var, Ffator_ativacao, Ffator_num, Ffator_string} tipo;
	
	union{	Texpressao exp; 
		Tvar var;
		Tativacao ativacao; 
		int num;
		char* str;	
	} uniao; 

};


// fator -> ( express�o )
Tfator fator_apar_exp_fpar(Texpressao exp);

// fator -> var
Tfator fator_var(Tvar var);

// fator -> ativa��o
Tfator fator_ativacao(Tativacao ativacao);

// fator -> NUM
Tfator fator_num(int num);

// fator -> STRING
Tfator fator_string(char* str);

/* FIM - fator -> ( express�o ) | var | ativa��o | NUM | STRING */



/* ativa��o -> ID ( args ) */

struct AAativacao {
	
	struct{	char* id; 
		Targs args;	
	} Tid_apar_args_fpar; 

};


Tativacao ativacao_regra(char* id, Targs args);

/* FIM - ativa��o -> ID ( args )  */




/* args -> arg-lista | vazio */

struct AAargs {
	
	Targlista arglista; 

};


// args -> arg-lista
Targs args_arglista(Targlista arglista);

// args -> vazio
Targs args_vazio();

/* FIM - args -> arg-lista | vazio */



/* arg-lista -> arg-lista, express�o | express�o */

struct AAarglista {
	
	enum{Farglista_arglista_virg_exp, Farglista_exp} tipo;
	
	union{	struct{	Targlista arglista;
			Texpressao exp;
		} Targlista_virg_exp; 
		Texpressao exp;	
	} uniao; 

};


// arg-lista -> arg-lista, express�o
Targlista arglista_arglista_virg_exp(Targlista arglista, Texpressao exp);

// arg-lista -> express�o
Targlista arglista_exp(Texpressao exp);

/* FIM - args -> arg-lista | vazio */


#endif
