#include "util.h"
#include "arvoreabstrata.h"


/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 03
   
   
				INTERFACE PARA ANÁLISE SEMÂNTICA PARA A LINGUAGEM C-
	     (gramática adaptada do livro de Kenneth C. Louden para aceitar strings)

		 
*/



typedef struct SMbindingtipos *Tbindingtipos;


// Binding de tipos

struct SMbindingtipos {
	
	enum{Ftiposimples, Ftipolista, Ftipofuncao} tipo;

	union{	Ttipoespecificador tipo;
	
			struct{
			Ttipoespecificador tipo;
			int num;
		} Ttipolista;
		
		struct{
			Ttipoespecificador tipo;
			bool ehVetor;  // variável que serve para dizer se o argumento é um vetor ou não
			Tbindingtipos argumentoAnterior; // a ordem dos argumentos fica na ordem reversa da declarada
		} Ttipofuncao;

	} uniao;

};

Tbindingtipos binding_tipo_simples(Ttipoespecificador tipo);
Tbindingtipos binding_tipo_lista(Ttipoespecificador tipo, int num);
Tbindingtipos binding_tipo_funcao(Ttipoespecificador tipo, Tbindingtipos argumentoAnterior, bool ehVetor);




// Assinatura das funções da análise semântica

void semantica_programa(Tprograma programa);
void semantica_declist(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tdeclaracaolista declist);
void semantica_decl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tdeclaracao decl);
void semantica_vardecl(Ambiente ambiente_variaveis, Tvardeclaracao vardecl);
void semantica_fundecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tfundeclaracao fundecl);
void semantica_params(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tparams params);
void semantica_paramlist(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tparamlista paramlist);
void semantica_param(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tparam param);
void semantica_compdecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tcompostodecl compdecl, bool iniciarescopo);
void semantica_localdecl(Ambiente ambiente_variaveis, Tlocaldeclaracoes localdecl);
void semantica_statementlist(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tstatementlista statementlist);
void semantica_statement(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tstatement statement);
void semantica_expdecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Texpressaodecl expdecl);
void semantica_seldecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tselecaodecl seldecl);
void semantica_itdecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Titeracaodecl itdecl);
void semantica_retdecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tretornodecl retdecl);
Tbindingtipos semantica_exp(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Texpressao exp);
Tbindingtipos semantica_var(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tvar var);
Tbindingtipos semantica_simplexp(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tsimplesexpressao simplexp);
Tbindingtipos semantica_ativacao(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tativacao ativacao);
Tbindingtipos semantica_args(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Targs args);
Tbindingtipos semantica_arglista(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Targlista arglista);