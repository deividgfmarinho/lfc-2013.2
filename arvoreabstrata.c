#include <stdlib.h>
#include "simbolos.h"
#include "arvoreabstrata.h"
#include "util.h"



/* 	
    Deivid Goes Farias Marinho
    201110005298
    Trabalho LFC - Parte 03


			  FUNÇÕES DA GRAMÁTICA ABSTRATA DA GRAMÁTICA DA LINGUAGEM C-
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




// var-declaracao -> tipo-especificador ID
Tvardeclaracao vardecl_tesp_id(Ttipoespecificador tesp, Simbolo id){
	Tvardeclaracao vdec = malloc(sizeof(*vdec));
	vdec->tipo = Fvardecl_tesp_id;
	vdec->uniao.Ttesp_id.tesp = tesp;
	vdec->uniao.Ttesp_id.id = id;
	return vdec;
}

// var-declaracao -> tipo-especificador ID NUM 
Tvardeclaracao vardecl_tesp_id_num(Ttipoespecificador tesp, Simbolo id, int num){
	Tvardeclaracao vdec = malloc(sizeof(*vdec));
	vdec->tipo = Fvardecl_tesp_id_num;
	vdec->uniao.Ttesp_id_num.tesp = tesp;
	vdec->uniao.Ttesp_id_num.id = id;
	vdec->uniao.Ttesp_id_num.num = num;
	return vdec;
}



// fun-declaração -> tipo-especificador ID params composto-decl */
Tfundeclaracao fundecl_tesp_id_param_compdecl(Ttipoespecificador tesp, 
							Simbolo id, Tparams params, Tcompostodecl compdecl){
	Tfundeclaracao funcao = malloc(sizeof(*funcao));
	funcao->Ttesp_id_param_compdecl.tesp = tesp;
	funcao->Ttesp_id_param_compdecl.id = id;
	funcao->Ttesp_id_param_compdecl.params = params;
	funcao->Ttesp_id_param_compdecl.compdecl = compdecl;
	return funcao;					
}



// params -> param-lista
Tparams params_paramlista(Tparamlista paramlist){
	Tparams params = malloc(sizeof(*params));
	params->tipo = Fparams_parlist;
	params->paramlist = paramlist;
	return params;
}

// params -> void
Tparams params_void(){
	return params_vazio();
}

// params -> vazio
Tparams params_vazio(){
	Tparams params = malloc(sizeof(*params));
	params->tipo = Fparams_vazio;
	// nothing...
	return params;
}



// param-lista -> param-lista param
Tparamlista paramlist_parlist_param(Tparamlista paramlist, Tparam param){
	Tparamlista plist = malloc(sizeof(*plist));
	plist->tipo = Fparamlist_parlist_param;
	plist->uniao.Tparlist_param.paramlist = paramlist;
	plist->uniao.Tparlist_param.param = param;
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
Tparam param_sem_colchetes(Ttipoespecificador tesp, Simbolo id){
	Tparam param = malloc(sizeof(*param));
	param->tipo = Fparam_sem_colchetes;
	param->Ttesp_id.tesp = tesp;
	param->Ttesp_id.id = id;
	return param;
}

// param -> tipo-especificador ID
Tparam param_com_colchetes(Ttipoespecificador tesp, Simbolo id){
	Tparam param = malloc(sizeof(*param));
	param->tipo = Fparam_com_colchetes;
	param->Ttesp_id.tesp = tesp;
	param->Ttesp_id.id = id;
	return param;
}



// composto-decl -> local-declarações statement-lista */
Tcompostodecl compostodecl_regra(Tlocaldeclaracoes localdecl, Tstatementlista statementlist){
	Tcompostodecl compdecl = malloc(sizeof(*compdecl));
	compdecl->Tlocaldecl_statmlist.localdecl = localdecl;
	compdecl->Tlocaldecl_statmlist.statementlist = statementlist;
	return compdecl;
}



// local-declarações -> local-declarações var-declaração
Tlocaldeclaracoes localdecl_localdecl_vardecl(Tlocaldeclaracoes localdecl, Tvardeclaracao vardecl){
	Tlocaldeclaracoes locdecl = malloc(sizeof(*locdecl));
	locdecl->tipo = Flocdecl_locdecl_vardecl;
	locdecl->Tlocaldecl_vardecl.localdecl = localdecl;
	locdecl->Tlocaldecl_vardecl.vardecl = vardecl;
	return locdecl;
}

// local-declarações -> vazio
Tlocaldeclaracoes localdecl_vazio(){
	Tlocaldeclaracoes locdecl = malloc(sizeof(*locdecl));
	locdecl->tipo = Flocdecl_vazio;
	// nothing . . .
	return locdecl;
}


// statement-lista -> statement-lista statement
Tstatementlista statmlist_statmlist_statm(Tstatementlista statementlist, Tstatement statement){
	Tstatementlista statmlist = malloc(sizeof(*statmlist));
	statmlist->tipo = Fstatm_statmlist_statm;
	statmlist->Tstatmlist_statm.statementlist = statementlist; 
	statmlist->Tstatmlist_statm.statement = statement; 
	return statmlist;
}

// statement-lista -> vazio
Tstatementlista statmlist_vazio(){
	Tstatementlista statmlist = malloc(sizeof(*statmlist));
	statmlist->tipo = Fstatm_vazio;
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
	statm->tipo = Fstatm_seldecl;
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



// expressão-decl -> expressão
Texpressaodecl expdecl_exp(Texpressao exp){
	Texpressaodecl expdecl = malloc(sizeof(*expdecl));
	expdecl->tipo = Fexpdecl_exp;
	expdecl->exp = exp;
	return expdecl;
}

// expressão-decl -> ;
Texpressaodecl expdecl_(){
	Texpressaodecl expdecl = malloc(sizeof(*expdecl));
	expdecl->tipo = Fexpdecl_vazio;
	// nada a armazenar
	return expdecl;
}



// seleção-decl -> expressão statement
Tselecaodecl seldecl_sem_else(Texpressao exp, Tstatement statement){
	Tselecaodecl seldecl = malloc(sizeof(*seldecl));
	seldecl->tipo = Fseldecl_sem_else;
	seldecl->uniao.Tif_sem_else.exp = exp;
	seldecl->uniao.Tif_sem_else.statement = statement;
	return seldecl;
}

// seleção-decl -> expressão statement statement
Tselecaodecl seldecl_com_else(Texpressao exp, Tstatement statementif, Tstatement statementelse){
	Tselecaodecl seldecl = malloc(sizeof(*seldecl));
	seldecl->tipo = Fseldecl_com_else;
	seldecl->uniao.Tif_com_else.exp = exp;
	seldecl->uniao.Tif_com_else.statementif = statementif;
	seldecl->uniao.Tif_com_else.statementelse = statementelse;
	return seldecl;
}



// iteração-decl -> expressão statement 
Titeracaodecl itdecl_regra(Texpressao exp, Tstatement statement){
	Titeracaodecl itdecl = malloc(sizeof(*itdecl));
	itdecl->Texp_statm.exp = exp;
	itdecl->Texp_statm.statement = statement;
	return itdecl;
}




// retorno-decl -> return ;
Tretornodecl retdecl_sem_expressao(){
	Tretornodecl retdecl = malloc(sizeof(*retdecl));
	retdecl->tipo = Fretdecl_;
	// nada a armazenar
	return retdecl;
}

// return expressão ;
Tretornodecl retdecl_com_expressao(Texpressao exp){
	Tretornodecl retdecl = malloc(sizeof(*retdecl));
	retdecl->tipo = Fretdecl_exp;
	retdecl->exp = exp;
	return retdecl;
}



// expressão -> var expressão
Texpressao exp_var_exp(Tvar var, Texpressao exp){
	Texpressao expressao = malloc(sizeof(*expressao));
	expressao->tipo = Fexp_var_exp;
	expressao->uniao.Tvar_exp.var = var;
	expressao->uniao.Tvar_exp.exp = exp;
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
Tvar var_id(Simbolo id){
	Tvar var = malloc(sizeof(*var));
	var->tipo = Fvar_id;
	var->uniao.id = id;
	return var;
}

// var -> ID expressão
Tvar var_id_exp(Simbolo id, Texpressao exp){
	Tvar var = malloc(sizeof(*var));
	var->tipo = Fvar_id_exp;
	var->uniao.Tid_exp.id = id;
	var->uniao.Tid_exp.exp = exp;
	return var;
}



// simples-expressão -> soma-expressão relacional soma-expressão
Tsimplesexpressao simplexp_simplexp_rel_simplexp(Tsimplesexpressao simplexp1, Trelacional rel, Tsimplesexpressao simplexp2){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_simplexp_rel_simplexp;
	simplexp->uniao.Tsimplexp_rel_simplexp.simplexp1 = simplexp1;
	simplexp->uniao.Tsimplexp_rel_simplexp.rel = rel;
	simplexp->uniao.Tsimplexp_rel_simplexp.simplexp2 = simplexp2;
	return simplexp;
}

// simples-expressão -> simples-expressão soma simples-expressão
Tsimplesexpressao simplexp_simplexp_soma_simplexp(Tsimplesexpressao simplexp1, Tsoma soma, Tsimplesexpressao simplexp2){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_simplexp_soma_simplexp;
	simplexp->uniao.Tsimplexp_soma_simplexp.simplexp1 = simplexp1;
	simplexp->uniao.Tsimplexp_soma_simplexp.soma = soma;
	simplexp->uniao.Tsimplexp_soma_simplexp.simplexp2 = simplexp2;
	return simplexp;
}

// simples-expressão -> simples-expressão mult simples-expressão
Tsimplesexpressao simplexp_simplexp_mult_simplexp(Tsimplesexpressao simplexp1, Tmult mult, Tsimplesexpressao simplexp2){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_simplexp_mult_simplexp;
	simplexp->uniao.Tsimplexp_mult_simplexp.simplexp1 = simplexp1;
	simplexp->uniao.Tsimplexp_mult_simplexp.mult = mult;
	simplexp->uniao.Tsimplexp_mult_simplexp.simplexp2 = simplexp2;
	return simplexp;
}


// simples-expressão -> expressão
Tsimplesexpressao simplexp_exp(Texpressao exp){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_exp;
	simplexp->uniao.exp = exp;
	return simplexp;
}

// simples-expressão -> var
Tsimplesexpressao simplexp_var(Tvar var){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_var;
	simplexp->uniao.var = var;
	return simplexp;
}

// simples-expressão -> ativação
Tsimplesexpressao simplexp_ativacao(Tativacao ativacao){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_ativacao;
	simplexp->uniao.ativacao = ativacao;
	return simplexp;
}

// simples-expressão -> NUM
Tsimplesexpressao simplexp_num(int num){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_num;
	simplexp->uniao.num = num;
	return simplexp;
}

// simples-expressão -> stringValue
Tsimplesexpressao simplexp_string(string str){
	Tsimplesexpressao simplexp = malloc(sizeof(*simplexp));
	simplexp->tipo = Fsimplexp_str;
	simplexp->uniao.str = str;
	return simplexp;
}


// ativação -> ID args */
Tativacao ativacao_regra(Simbolo id, Targs args){
	Tativacao ativacao = malloc(sizeof(*ativacao));
	ativacao->Tid_args.id = id;
	ativacao->Tid_args.args = args;
	return ativacao;
}



// args -> arg-lista
Targs args_arglista(Targlista arglista){
	Targs args = malloc(sizeof(*args));
	args->tipo = Fargs_arglist;
	args->arglista = arglista;
	return args;
}

// args -> vazio
Targs args_vazio(){
	Targs args = malloc(sizeof(*args));
	args->tipo = Fargs_vazio;
	// nothing ...
	return args;
}


// arg-lista -> arg-lista, expressão
Targlista arglista_arglista_exp(Targlista arglista, Texpressao exp){
	Targlista alist = malloc(sizeof(*alist));
	alist->tipo = Farglista_arglista_exp;
	alist->uniao.Targlista_exp.arglista = arglista;
	alist->uniao.Targlista_exp.exp = exp;
	return alist;
}

// arg-lista -> expressão
Targlista arglista_exp(Texpressao exp){
	Targlista alist = malloc(sizeof(*alist));
	alist->tipo = Farglista_exp;
	alist->uniao.exp = exp;
	return alist;
}





// DESTRUIR A ÁRVORE
void destroiArvore(Tprograma programa){

	if(programa == NULL)
		return;

	destroiDecList(programa->declist);
	
	free(programa);
}

// declaracao-lista 
void destroiDecList(Tdeclaracaolista declist){
	
	if(declist == NULL)
		return;
	
	if(declist->tipo == Fdeclist_declist_decl){
		destroiDecList(declist->uniao.Tdeclistdec.declist);
		destroiDecl(declist->uniao.Tdeclistdec.decl);
	}else if(declist->tipo == Fdeclist_decl)
		destroiDecl(declist->uniao.decl);
	
	free(declist);
	
}


// declaração
void destroiDecl(Tdeclaracao decl){
	
	if(decl == NULL)
		return;
	
	if(decl->tipo == Fdecl_vardecl)
		destroiVarDecl(decl->uniao.vardecl);
	else if(decl->tipo == Fdecl_fundecl)
		destroiFunDecl(decl->uniao.fundecl);
	
	free(decl);
	
}

// var-declaracao 
void destroiVarDecl(Tvardeclaracao vardecl){

	if(vardecl == NULL)
		return;
	
	if(vardecl->tipo == Fvardecl_tesp_id)
		vardecl->uniao.Ttesp_id.id = NULL;
	else if(vardecl->tipo == Fvardecl_tesp_id_num)
		vardecl->uniao.Ttesp_id_num.id = NULL;
	
	
	free(vardecl);
}

// fun-declaracao 
void destroiFunDecl(Tfundeclaracao fundecl){
	
	if(fundecl == NULL)
		return;
	
	fundecl->Ttesp_id_param_compdecl.id = NULL;
	destroiParams(fundecl->Ttesp_id_param_compdecl.params);
	destroiCompDecl(fundecl->Ttesp_id_param_compdecl.compdecl);
	
	free(fundecl);
	
}


// params
void destroiParams(Tparams params){

	if(params == NULL)
		return;
	
	if(params->tipo == Fparams_parlist)
		destroiParamList(params->paramlist);
	
	free(params);

}



// param-lista
void destroiParamList(Tparamlista paramlist){

	if(paramlist == NULL)
		return;
	
	if(paramlist->tipo == Fparamlist_parlist_param){
		destroiParamList(paramlist->uniao.Tparlist_param.paramlist);
		destroiParam(paramlist->uniao.Tparlist_param.param);
	}else if(paramlist->tipo == Fparamlist_param)
		destroiParam(paramlist->uniao.param);
	
	free(paramlist);
}

// param
void destroiParam(Tparam param){

	if(param == NULL)
		return;
	
	param->Ttesp_id.id = NULL;
	
	free(param);
}



// comp-decl
void destroiCompDecl(Tcompostodecl compdecl){
  
	if(compdecl == NULL)
		return;
	
	destroiLocalDecl(compdecl->Tlocaldecl_statmlist.localdecl);
	
	destroiStatmList(compdecl->Tlocaldecl_statmlist.statementlist);
	
	free(compdecl);
}




// local-declarações
void destroiLocalDecl(Tlocaldeclaracoes localdecl){
	
	if(localdecl == NULL)
		return;
	
	if(localdecl->tipo == Flocdecl_locdecl_vardecl){
		destroiLocalDecl(localdecl->Tlocaldecl_vardecl.localdecl);
		destroiVarDecl(localdecl->Tlocaldecl_vardecl.vardecl);
	}
	
	free(localdecl);
}


// statement-lista
void destroiStatmList(Tstatementlista statementlist){
	
	if(statementlist == NULL)
		return;
	
	if(statementlist->tipo == Fstatm_statmlist_statm){
		destroiStatmList(statementlist->Tstatmlist_statm.statementlist);
		destroiStatm(statementlist->Tstatmlist_statm.statement);
	}
	
	free(statementlist);
	
}


// statement
void destroiStatm(Tstatement statement){
	
	if(statement == NULL)
		return;
	
	if(statement->tipo == Fstatm_expdecl)
		destroiExpDecl(statement->uniao.expdecl);
	else if(statement->tipo == Fstatm_compdecl)
		destroiCompDecl(statement->uniao.compdecl);
	else if(statement->tipo == Fstatm_seldecl)
		destroiSelDecl(statement->uniao.seldecl);
	else if(statement->tipo == Fstatm_itdecl)
		destroiItDecl(statement->uniao.itdecl);
	else if(statement->tipo == Fstatm_retdecl)
		destroiRetDecl(statement->uniao.retdecl);
	
	free(statement);
}



// expressão-decl
void destroiExpDecl(Texpressaodecl expdecl){
	
	if(expdecl == NULL)
		return;
	
	if(expdecl->tipo == Fexpdecl_exp)
		destroiExp(expdecl->exp);
	
	free(expdecl);
	
}

// seleção-decl
void destroiSelDecl(Tselecaodecl seldecl){
	
	if(seldecl == NULL)
		return;
	
	if(seldecl->tipo == Fseldecl_sem_else){
		destroiExp(seldecl->uniao.Tif_sem_else.exp);
		destroiStatm(seldecl->uniao.Tif_sem_else.statement);
	}else if(seldecl->tipo == Fseldecl_com_else){
		destroiExp(seldecl->uniao.Tif_com_else.exp);
		destroiStatm(seldecl->uniao.Tif_com_else.statementif);
		destroiStatm(seldecl->uniao.Tif_com_else.statementelse);
	}
	
	free(seldecl);
	
}


// iteração-decl
void destroiItDecl(Titeracaodecl itdecl){
	
	if(itdecl == NULL)
		return;
	
	destroiExp(itdecl->Texp_statm.exp);
	
	destroiStatm(itdecl->Texp_statm.statement);
	
	free(itdecl);
	
}


// retorno-decl
void destroiRetDecl(Tretornodecl retdecl){
	
	if(retdecl == NULL)
		return;
	
	if(retdecl->tipo == Fretdecl_exp)
		destroiExp(retdecl->exp);
	
	free(retdecl);
	
}


// expressão
void destroiExp(Texpressao exp){
	
	if(exp == NULL)
		return;
	
	if(exp->tipo == Fexp_var_exp){
		destroiVar(exp->uniao.Tvar_exp.var);
		destroiExp(exp->uniao.Tvar_exp.exp);
	}else if(exp->tipo == Fexp_simplexp)
		destroiSimplExp(exp->uniao.simplexp);
		
	free(exp);
	
}

// var
void destroiVar(Tvar var){
	
	if(var == NULL)
		return;
	
	if(var->tipo == Fvar_id)
		var->uniao.id = NULL;
	else if(var->tipo == Fvar_id_exp){
		var->uniao.Tid_exp.id = NULL;
		destroiExp(var->uniao.Tid_exp.exp);
	}
	
	free(var);
	
}


// simples-expressão
void destroiSimplExp(Tsimplesexpressao simplexp){
	
	if(simplexp == NULL)
		return;
	
	if(simplexp->tipo == Fsimplexp_simplexp_rel_simplexp){
		destroiSimplExp(simplexp->uniao.Tsimplexp_rel_simplexp.simplexp1);
		destroiSimplExp(simplexp->uniao.Tsimplexp_rel_simplexp.simplexp2);
	}else if(simplexp->tipo == Fsimplexp_simplexp_soma_simplexp){
		destroiSimplExp(simplexp->uniao.Tsimplexp_soma_simplexp.simplexp1);
		destroiSimplExp(simplexp->uniao.Tsimplexp_soma_simplexp.simplexp2);
	}else if(simplexp->tipo == Fsimplexp_simplexp_mult_simplexp){
		destroiSimplExp(simplexp->uniao.Tsimplexp_mult_simplexp.simplexp1);
		destroiSimplExp(simplexp->uniao.Tsimplexp_mult_simplexp.simplexp2);
	}else if(simplexp->tipo == Fsimplexp_exp)
		destroiExp(simplexp->uniao.exp);
	else if(simplexp->tipo == Fsimplexp_var)
		destroiVar(simplexp->uniao.var);
	else if(simplexp->tipo == Fsimplexp_ativacao)
		destroiAtivacao(simplexp->uniao.ativacao);
	else if(simplexp->tipo == Fsimplexp_str)
		free(simplexp->uniao.str);
	
	free(simplexp);
	
}


// ativação
void destroiAtivacao(Tativacao ativacao){
	
	if(ativacao == NULL)
		return;
	
	ativacao->Tid_args.id = NULL;
	
	destroiArgs(ativacao->Tid_args.args);
	
	free(ativacao);
}


// args
void destroiArgs(Targs args){
	
	if(args == NULL)
		return;
	
	if(args->tipo == Fargs_arglist)
		destroiArgList(args->arglista);
	
	free(args);
	
}



// arg-lista
void destroiArgList(Targlista arglista){
	
	if(arglista == NULL)
		return;
	
	if(arglista->tipo == Farglista_arglista_exp){
		destroiArgList(arglista->uniao.Targlista_exp.arglista);
		destroiExp(arglista->uniao.Targlista_exp.exp);
	}else if(arglista->tipo == Farglista_exp)
		destroiExp(arglista->uniao.exp);
		
	free(arglista);
	
}

