#include <stdlib.h>
#include "estruturas.h"


/* 	
    Deivid Goes Farias Marinho
    201110005298
    Trabalho LFC - Parte 02


	FUNÇÕES DAS ESTRUTURAS USADAS PARA A GRAMÁTICA LIVRE DE CONTEXTO PARA A LINGUAGEM C-
	     (gramática adaptada do livro de Kenneth C. Louden para aceitar strings)



*/



// programa -> declaracao-lista */
Tprograma programa_declist(Tdeclaracaolista declist){
	Tprograma program = malloc(sizeof(*program));
	program->declist = declist;
	return program;
}





// declaracao-lista -> declaracao-lista declaracao 
Tdeclaracaolista declist_declist_decl(Tdeclaracaolista declist, Tdeclaracao decl){
	Tdeclaracaolista dl = malloc(sizeof(*dl));
	dl->tipo = Fdeclist_declist_decl;
	dl->uniao.Tdeclistdec.declist = declist;
	dl->uniao.Tdeclistdec.decl = decl;
	return dl;
}


// declaracao-lista -> declaracao 
Tdeclaracaolista declist_decl(Tdeclaracao decl){
	Tdeclaracaolista dl = malloc(sizeof(*dl));
	dl->tipo = Fdeclist_decl;
	dl->uniao.decl = decl;
	return dl;
}




// declaracao -> var-declaracao 
Tdeclaracao decl_vardecl(Tvardeclaracao vardecl){
	Tdeclaracao dec = malloc(sizeof(*dec));
	dec->tipo = Fdecl_vardecl;
	dec->uniao.vardecl = vardecl;
	return dec;
}

// declaracao -> fun-declaracao 
Tdeclaracao decl_fundecl(Tfundeclaracao fundecl){
	Tdeclaracao dec = malloc(sizeof(*dec));
	dec->tipo = Fdecl_fundecl;
	dec->uniao.fundecl = fundecl;
	return dec;
}




// var-declaracao -> tipo-especificador ID ;
Tvardeclaracao vardecl_tesp_id_ptvirg(Ttipoespecificador tesp, char* id){
	Tvardeclaracao vdec = malloc(sizeof(*vdec));
	vdec->tipo = Fvardecl_tesp_id_ptvirg;
	vdec->uniao.T_tesp_id_ptvirg.tesp = tesp;
	vdec->uniao.T_tesp_id_ptvirg.id = id;
	return vdec;
}

// var-declaracao -> tipo-especificador ID [ NUM ] ;
Tvardeclaracao vardecl_tesp_id_acol_num_fcol_ptvirg(Ttipoespecificador tesp, char* id, int num){
	Tvardeclaracao vdec = malloc(sizeof(*vdec));
	vdec->tipo = Fvardecl_tesp_id_acol_num_fcol_ptvirg;
	vdec->uniao.T_tesp_id_acol_num_fcol_ptvirg.tesp = tesp;
	vdec->uniao.T_tesp_id_acol_num_fcol_ptvirg.id = id;
	vdec->uniao.T_tesp_id_acol_num_fcol_ptvirg.num = num;
	return vdec;
}



// tipo-especificador -> int | void | string
Ttipoespecificador tesp(char* tesp){
	Ttipoespecificador tipo = malloc(sizeof(*tipo));
	tipo->tesp = tesp;
	return tipo;
}



// fun-declaração -> tipo-especificador ID ( params ) composto-decl */
Tfundeclaracao fundecl_tesp_id_apar_param_fpar_compdecl(Ttipoespecificador tesp, 
							char* id, Tparams params, Tcompostodecl compdecl){
	Tfundeclaracao funcao = malloc(sizeof(*funcao));
	funcao->tesp_id_apar_param_fpar_compdecl.tesp = tesp;
	funcao->tesp_id_apar_param_fpar_compdecl.params = params;
	funcao->tesp_id_apar_param_fpar_compdecl.compdecl = compdecl;
	return funcao;					
}



// params -> param-lista
Tparams params_paramlista(Tparamlista paramlist){
	Tparams params = malloc(sizeof(*params));
	params->tipo = Fparams_paramlista;
	params->uniao.paramlist = paramlist;
	return params;
}

// params -> void
Tparams params_void(char* tvoid){
	Tparams params = malloc(sizeof(*params));
	params->tipo = Fparams_void;
	params->uniao.tvoid = tvoid;
	return params;
}

// params -> vazio
Tparams params_vazio(){
	Tparams params = malloc(sizeof(*params));
	// nothing...
	return params;
}



// param-lista -> param-lista, param
Tparamlista paramlist_parlist_virg_param(Tparamlista paramlist, Tparam param){
	Tparamlista plist = malloc(sizeof(*plist));
	plist->tipo = Fparamlist_parlist_virg_param;
	plist->uniao.Tparlist_virg_param.paramlist = paramlist;
	plist->uniao.Tparlist_virg_param.param = param;
	return plist;
}

// param-lista -> param
Tparamlista paramlist_param(Tparam param){
	Tparamlista plist = malloc(sizeof(*plist));
	plist->tipo = Fparamlist_param;
	plist->uniao.param = param;
	return plist;
}



// param -> tipo-especificador ID
Tparam param_tesp_id(Ttipoespecificador tesp, char* id){
	Tparam param = malloc(sizeof(*param));
	param->Ttesp_id.tesp = tesp;
	param->Ttesp_id.id = id;
	return param;
}

// param -> tipo-especificador ID []
Tparam param_tesp_id_acol_fcol(Ttipoespecificador tesp, char* id){
	Tparam param = malloc(sizeof(*param));
	param->Ttesp_id.tesp = tesp;
	param->Ttesp_id.id = id;
	return param;
}



// composto-decl -> { local-declarações statement-lista } */
Tcompostodecl compostodecl_achv_localdecl_statmlist_fchv(Tlocaldeclaracoes localdecl, Tstatementlista statementlist){
	Tcompostodecl compdecl = malloc(sizeof(*compdecl));
	compdecl->Tachv_localdecl_statmlist_fchv.localdecl = localdecl;
	compdecl->Tachv_localdecl_statmlist_fchv.statementlist = statementlist;
	return compdecl;
}



// local-declarações -> local-declarações var-declaração
Tlocaldeclaracoes localdecl_localdecl_vardecl(Tlocaldeclaracoes localdecl, Tvardeclaracao vardecl){
	Tlocaldeclaracoes locdecl = malloc(sizeof(*locdecl));
	locdecl->Tachv_localdecl_vardecl.localdecl = localdecl;
	locdecl->Tachv_localdecl_vardecl.vardecl = vardecl;
	return localdecl;
}

// local-declarações -> vazio
Tlocaldeclaracoes localdecl_vazio(){
	Tlocaldeclaracoes locdecl = malloc(sizeof(*locdecl));
	// nothing . . .
	return locdecl;
}


// statement-lista -> statement-lista statement
Tstatementlista statmlist_statmlist_statm(Tstatementlista statementlist, Tstatement statement){
	Tstatementlista statmlist = malloc(sizeof(*statmlist));
	statmlist->Tstatmlist_statm.statementlist = statementlist; 
	statmlist->Tstatmlist_statm.statement = statement; 
	return statmlist;
}

// statement-lista -> vazio
Tstatementlista statmlist_vazio(){
	Tstatementlista statmlist = malloc(sizeof(*statmlist));
	// nothing . . .
	return statmlist;
}



// statement -> expressão-decl
Tstatement statm_expdecl(Texpressaodecl expdecl){
	Tstatement statm = malloc(sizeof(*statm));
	statm->tipo = Fstatm_expdecl;
	statm->uniao.expdecl = expdecl;
	return statm;
}

// statement -> composto-decl
Tstatement statm_compdecl(Tcompostodecl compdecl){
	Tstatement statm = malloc(sizeof(*statm));
	statm->tipo = Fstatm_compdecl;
	statm->uniao.compdecl = compdecl;
	return statm;
}

// statement -> seleção-decl
Tstatement statm_seldecl(Tselecaodecl seldecl){
	Tstatement statm = malloc(sizeof(*statm));
	statm->tipo = Fstatm_compdecl;
	statm->uniao.seldecl = seldecl;
	return statm;
}

// statement -> iteração-decl
Tstatement statm_itdecl(Titeracaodecl itdecl){
	Tstatement statm = malloc(sizeof(*statm));
	statm->tipo = Fstatm_itdecl;
	statm->uniao.itdecl = itdecl;
	return statm;
}

// statement -> retorno-decl
Tstatement statm_retdecl(Tretornodecl retdecl){
	Tstatement statm = malloc(sizeof(*statm));
	statm->tipo = Fstatm_retdecl;
	statm->uniao.retdecl = retdecl;
	return statm;
}



// expressão-decl -> expressão ;
Texpressaodecl expdecl_exp_ptvirg(Texpressao exp){
	Texpressaodecl expdecl = malloc(sizeof(*expdecl));
	expdecl->exp = exp;
	return expdecl;
}

// expressão-decl -> ;
Texpressaodecl expdecl_ptvirg(){
	Texpressaodecl expdecl = malloc(sizeof(*expdecl));
	// nada a armazenar
	return expdecl;
}



// seleção-decl -> if ( expressão ) statement
Tselecaodecl seldecl_sem_else(Texpressao exp, Tstatement statement){
	Tselecaodecl seldecl = malloc(sizeof(*seldecl));
	seldecl->tipo = Fseldecl_sem_else;
	seldecl->uniao.Tif_sem_else.exp = exp;
	seldecl->uniao.Tif_sem_else.statement = statement;
	return seldecl;
}

// seleção-decl -> if ( expressão ) statement else statement
Tselecaodecl seldecl_com_else(Texpressao exp, Tstatement statementif, Tstatement statementelse){
	Tselecaodecl seldecl = malloc(sizeof(*seldecl));
	seldecl->tipo = Fseldecl_com_else;
	seldecl->uniao.Tif_com_else.exp = exp;
	seldecl->uniao.Tif_com_else.statementif = statementif;
	seldecl->uniao.Tif_com_else.statementelse = statementelse;
	return seldecl;
}



// iteração-decl -> while ( expressão ) statement 
Titeracaodecl itdecl_while_apar_exp_fpar_statm(Texpressao exp, Tstatement statement){
	Titeracaodecl itdecl = malloc(sizeof(*itdecl));
	itdecl->Twhile_apar_exp_fpar_statm.exp = exp;
	itdecl->Twhile_apar_exp_fpar_statm.statement = statement;
	return itdecl;
}




// retorno-decl -> return ;
Tretornodecl retdecl_sem_expressao(){
	Tretornodecl retdecl = malloc(sizeof(*retdecl));
	// nada a armazenar
	return retdecl;
}

// return expressão ;
Tretornodecl retdecl_com_expressao(Texpressao exp){
	Tretornodecl retdecl = malloc(sizeof(*retdecl));
	retdecl->exp = exp;
	return retdecl;
}



// expressão -> var = expressão
Texpressao exp_var_atrib_exp(Tvar var, Texpressao exp){
	Texpressao expressao = malloc(sizeof(*expressao));
	expressao->tipo = Fexp_var_atrib_exp;
	expressao->uniao.Tvar_atrib_exp.var = var;
	expressao->uniao.Tvar_atrib_exp.exp = exp;
	return expressao;
}

// expressão -> simples-expressão
Texpressao exp_simplexp(Tsimplesexpressao simplexp){
	Texpressao expressao = malloc(sizeof(*expressao));
	expressao->tipo = Fexp_simplexp;
	expressao->uniao.simplexp = simplexp;
	return expressao;
}



// var -> ID
Tvar var_id(char* id){
	Tvar var = malloc(sizeof(*var));
	var->tipo = Fvar_id;
	var->uniao.id = id;
	return var;
}

// var -> ID [ expressão ]
Tvar var_id_acol_exp_fcol(char* id, Texpressao exp){
	Tvar var = malloc(sizeof(*var));
	var->tipo = Fvar_id_acol_exp_fcol;
	var->uniao.Tid_acol_exp_fcol.id = id;
	var->uniao.Tid_acol_exp_fcol.exp = exp;
	return var;
}



// simples-expressão -> soma-expressão relacional soma-expressão
Tsimplesexpressao simplexp_somaexp_rel_somaexp(Tsomaexpressao somaexp1, Trelacional rel, Tsomaexpressao somaexp2){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_somaexp_rel_somaexp;
	simplexp->uniao.TTsomaexp_rel_somexp.somaexp1 = somaexp1;
	simplexp->uniao.TTsomaexp_rel_somexp.rel = rel;
	simplexp->uniao.TTsomaexp_rel_somexp.somaexp2 = somaexp2;
	return simplexp;
}

// simples-expressão -> soma-expressão 
Tsimplesexpressao simplexp_somaexp(Tsomaexpressao somaexp){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_somaexp;
	simplexp->uniao.somaexp = somaexp;
	return simplexp;
}



// relacional -> <= | < | > | >= | == | !=
Trelacional relacional(char* rel){
	Trelacional oprel = malloc(sizeof(*oprel));
	oprel->rel = rel;
	return oprel;
}



// soma-expressão -> soma-expressão soma termo
Tsomaexpressao somaexp_somaexp_soma_termo(Tsomaexpressao somaexp, Tsoma soma, Ttermo termo){
	Tsomaexpressao sexp = malloc(sizeof(*sexp));
	sexp->tipo = Fsomaexp_somaexp_soma_termo;
	sexp->uniao.TTsomaexp_rel_somexp.somaexp = somaexp;
	sexp->uniao.TTsomaexp_rel_somexp.soma = soma;
	sexp->uniao.TTsomaexp_rel_somexp.termo = termo;
	return sexp;
}

// soma-expressão -> termo
Tsomaexpressao somaexp_termo(Ttermo termo){
	Tsomaexpressao sexp = malloc(sizeof(*sexp));
	sexp->tipo = Fsimplexp_termo;
	sexp->uniao.termo = termo;
	return sexp;
}


// soma -> + | -
Tsoma soma(char op){
	Tsoma soma = malloc(sizeof(*soma));
	soma->op = op;
	return soma;
}



// termo -> termo mult fator
Ttermo termo_termo_mult_fator(Ttermo termo, Tmult mult, Tfator fator){
	Ttermo term = malloc(sizeof(*term));
	term->tipo = Ftermo_termo_mult_fator;
	term->uniao.Ttermo_mult_fator.termo = termo;
	term->uniao.Ttermo_mult_fator.mult = mult;
	term->uniao.Ttermo_mult_fator.fator = fator;
	return term;
}

// termo -> fator
Ttermo termo_fator(Tfator fator){
	Ttermo term = malloc(sizeof(*term));
	term->tipo = Ftermo_fator;
	term->uniao.fator = fator;
	return term;
}



// mult -> * | /
Tmult mult(char op){
	Tmult mult = malloc(sizeof(*mult));
	mult->op = op;
	return mult;
}



// fator -> ( expressão )
Tfator fator_apar_exp_fpar(Texpressao exp){
	Tfator fator = malloc(sizeof(*fator));
	fator->tipo = Ffator_apar_exp_fpar;
	fator->uniao.exp = exp;
	return fator;
}

// fator -> var
Tfator fator_var(Tvar var){
	Tfator fator = malloc(sizeof(*fator));
	fator->tipo = Ffator_var;
	fator->uniao.var = var;
	return fator;
}

// fator -> ativação
Tfator fator_ativacao(Tativacao ativacao){
	Tfator fator = malloc(sizeof(*fator));
	fator->tipo = Ffator_ativacao;
	fator->uniao.ativacao = ativacao;
	return fator;
}

// fator -> NUM
Tfator fator_num(int num){
	Tfator fator = malloc(sizeof(*fator));
	fator->tipo = Ffator_num;
	fator->uniao.num = num;
	return fator;
}

// fator -> STRING
Tfator fator_string(char* str){
	Tfator fator = malloc(sizeof(*fator));
	fator->tipo = Ffator_string;
	fator->uniao.str = str;
	return fator;
}



// ativação -> ID ( args ) */
Tativacao ativacao_regra(char* id, Targs args){
	Tativacao ativacao = malloc(sizeof(*ativacao));
	ativacao->Tid_apar_args_fpar.id = id;
	ativacao->Tid_apar_args_fpar.args = args;
	return ativacao;
}



// args -> arg-lista
Targs args_arglista(Targlista arglista){
	Targs args = malloc(sizeof(*args));
	args->arglista = arglista;
	return args;
}

// args -> vazio
Targs args_vazio(){
	Targs args = malloc(sizeof(*args));
	// nothing ...
	return args;
}


// arg-lista -> arg-lista, expressão
Targlista arglista_arglista_virg_exp(Targlista arglista, Texpressao exp){
	Targlista alist = malloc(sizeof(*alist));
	alist->tipo = Farglista_arglista_virg_exp;
	alist->uniao.Targlista_virg_exp.arglista = arglista;
	alist->uniao.Targlista_virg_exp.exp = exp;
	return alist;
}

// arg-lista -> expressão
Targlista arglista_exp(Texpressao exp){
	Targlista alist = malloc(sizeof(*alist));
	alist->tipo = Farglista_exp;
	alist->uniao.exp = exp;
	return alist;
}
