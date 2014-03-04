#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simbolos.c"
#include "geradordecodigo.c"
#include "arvoreabstrata.h"
#include "util.h"
#include "semantico.h"


/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 03
   
   
						ANÁLISE SEMÂNTICA PARA A LINGUAGEM C-
	     (gramática adaptada do livro de Kenneth C. Louden para aceitar strings)

		 
*/




// nome do arquivo para a geração de código 
string arquivo = "codigogerado";



/**
  * Destrói o ambiente
  */
void destroiAmbiente(Ambiente ambiente){
	
	Binder binder = ambiente->topoDaPilha;
	
	while(binder != NULL){
		Binder b = binder;
		binder = binder->antigoTopoDaPilha;
		
		if(b->valor != NULL){
			Tbindingtipos binding = (Tbindingtipos) binder->valor;
			while(binding != NULL){
				Tbindingtipos bt = binding;
				if(binding->tipo == Ftipofuncao)
					binding = binding->uniao.Ttipofuncao.argumentoAnterior;
				else
					binding = NULL;
				free(bt);
			}
		}
		
		free(b);
	}
	
	free(ambiente);
}



// Definição dos construtores de bindings de tipos

Tbindingtipos binding_tipo_simples(Ttipoespecificador tipo){
	Tbindingtipos binding = malloc(sizeof(*binding));
	binding->tipo = Ftiposimples;
	binding->uniao.tipo = tipo; 
	return binding;
}

Tbindingtipos binding_tipo_lista(Ttipoespecificador tipo, int num){
	Tbindingtipos binding = malloc(sizeof(*binding));
	binding->tipo = Ftipolista;
	binding->uniao.Ttipolista.tipo = tipo; 
	binding->uniao.Ttipolista.num = num;
	return binding;
}

Tbindingtipos binding_tipo_funcao(Ttipoespecificador tipo, Tbindingtipos argumento, bool ehVetor){
	Tbindingtipos binding = malloc(sizeof(*binding));
	binding->tipo = Ftipofuncao;
	binding->uniao.Ttipofuncao.tipo = tipo; 
	binding->uniao.Ttipofuncao.ehVetor = ehVetor;
	binding->uniao.Ttipofuncao.argumentoAnterior = argumento;
	return binding;
}






// Auxiliares

// Variáveis auxiliares
unsigned int contWhiles;   // flag que auxilia na contagem dos while
unsigned int contIfs;     // flag que auxilia na contagem dos if
unsigned int contBlocos;  // flag que auxiliar na contagem da abertura de blocos
unsigned int totalBlocosInternosComDeclaracao; // flag para auxiliar a geração de código
unsigned int contChamadasInputInteger; // flag que auxiliar na contagem da ativação do 'input()' do tipo 'int' na mesma expressão 
unsigned int contChamadasInputString;  // flag que auxiliar na contagem da ativação do 'input()' do tipo 'string' na mesma expressão 
unsigned int totalVarTempInputInteger; // conta quantas variáveis temporárias foram criadas para tratar o 'input()' do tipo 'int'
unsigned int totalVarTempInputString;  // conta quantas variáveis temporárias foram criadas para tratar o 'input()' do tipo 'string'
unsigned int identacao;  // auxilia na identação do código gerado
bool inicioDeBloco;
bool funcaoCorrenteTemRetorno;






/**
  * Retorna a string com o statement corretamente identado
  */
string getStatementIdentado(string statement){
	
	string espacos;
	espacos = (string) malloc((identacao + 1) * sizeof(char));
	memset(espacos, ' ', identacao);
	espacos[identacao + 1] = '\0';
	
	string temp; 
	temp = (string) malloc((strlen(espacos) + strlen(statement) + 1) * sizeof(char));
	sprintf(temp, "%s%s", espacos, statement);
	
	temp[strlen(espacos) + strlen(statement) + 1] = '\0';
	
	return temp;

}




/**
  * Compara os bindings de tipos. 
  *
  * Retorna TRUE se corresponderem ao mesmo tipo. Retorna FALSE caso contrario
  */
bool tiposSaoCompativeis(Tbindingtipos binding1, Tbindingtipos binding2){
	
	// não é possível comparar um vetor com um tipo simples
	if( (binding1->tipo == Ftiposimples && binding2->tipo == Ftipolista) ||
		(binding1->tipo == Ftipolista && binding2->tipo == Ftiposimples) ||
		(binding1->tipo == Ftipofuncao && binding2->tipo == Ftipolista) ||
		(binding1->tipo == Ftipolista && binding2->tipo == Ftipofuncao))
			return FALSE;
	
	Ttipoespecificador tipo1 = Tvoid;
	Ttipoespecificador tipo2 = Tvoid;
	
	if(binding1->tipo == Ftiposimples)
		tipo1 = binding1->uniao.tipo;
	else if(binding1->tipo == Ftipolista)
		tipo1 = binding1->uniao.Ttipolista.tipo;
	else if(binding1->tipo == Ftipofuncao)
		tipo1 = binding1->uniao.Ttipofuncao.tipo;
	
	if(binding2->tipo == Ftiposimples)
		tipo2 = binding2->uniao.tipo;
	else if(binding2->tipo == Ftipolista)
		tipo2 = binding2->uniao.Ttipolista.tipo;
	else if(binding2->tipo == Ftipofuncao)
		tipo2 = binding2->uniao.Ttipofuncao.tipo;
	
	if( tipo1 == tipo2 || 
	   (tipo1 == Tstrint && (tipo2 == Tint || tipo2 == Tstring)) ||
	   (tipo2 == Tstrint && (tipo1 == Tint || tipo1 == Tstring)) )
			return TRUE;
		
	return FALSE;			
	
}





/**
  * Analisa se a função possui todos os returns necessários
  */ 
void analisaRetornoDaFuncaoCorrente(Ambiente ambiente_funcoes){
	
	Binder funcaoCorrente = ambiente_funcoes->topoDaPilha;
	
	Tbindingtipos binding = (Tbindingtipos) funcaoCorrente->valor;
	
	if(binding->uniao.Ttipofuncao.tipo != Tvoid && !funcaoCorrenteTemRetorno){
		fprintf(stderr,"Erro semantico. A funcao  '%s' deve ter um return no mesmo nivel lexico do bloco principal da funcao!\n",
				funcaoCorrente->simbol->nome);
		destroiGeracaoDeCodigo();   
		exit(1);
	}	

} 



/**
  * Analisa se os argumentos passados para a função corresponde aos tipos ordenados definidos
  */ 
Ttipoespecificador analisaChamadaDeFuncao(string nomeDaFuncao, Tbindingtipos bindingFuncao, Tbindingtipos bindingArgs){
	
	Ttipoespecificador tipoDaFuncao = bindingFuncao->uniao.Ttipofuncao.tipo;
		
	bindingFuncao = bindingFuncao->uniao.Ttipofuncao.argumentoAnterior;
	
	// Compara tipos dos argumentos com os definidos da funcao
	while(bindingFuncao != NULL && bindingArgs != NULL){
		  
		// tem que coicidir do parâmetro e do informado ser ou não vetor  
		if(bindingFuncao->uniao.Ttipofuncao.ehVetor != bindingArgs->uniao.Ttipofuncao.ehVetor)
			break; 
		
		// como o argumento de uma função não pode ser do tipo void, se for um
		// argumento do tipo  Tstrint, então sempre será válido, caso contrário,
		// deve-se avaliar o tipo informado do argumento e do informado na ativação
		if( bindingFuncao->uniao.Ttipofuncao.tipo != Tstrint && bindingArgs->uniao.Ttipofuncao.tipo != Tstrint &&
		    bindingFuncao->uniao.Ttipofuncao.tipo != bindingArgs->uniao.Ttipofuncao.tipo)
				break;
		
		
		bindingFuncao = bindingFuncao->uniao.Ttipofuncao.argumentoAnterior;
		bindingArgs = bindingArgs->uniao.Ttipofuncao.argumentoAnterior;
		
	}
		  
	if(bindingFuncao != NULL || bindingArgs != NULL){
		fprintf(stderr,"Erro semantico. Argumento(s) nao compativel(is) com o(s) da funcao '%s'!\n", nomeDaFuncao);
		destroiGeracaoDeCodigo();   
		exit(1);
	}
	
	return tipoDaFuncao;
}



/**
  * Adiciona o correto statement da chamada de função
  */ 
void adicionaStatementDeChamadaDeFuncao(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, string idFuncao){
	
	// input  pode ser chamado no "meio" de uma expressão
	if(strcmp(idFuncao, "input") == 0){
		
		// => deve fazer com que uma variável temporária seja criada globalmente
		// usá-la numa linha acima para fazer o readln e substituir pelo input da expressão
		
		Ttipoespecificador tipoesp = Tvoid;
	
		// tem que descobrir o tipo do dado que está chamando
		string id = getVariavelDaAtribuicao();
		
		if(id == NULL){
		
			// verificar se é chamada de função
			int posArg = 0;
			id = getFuncaoDeAtivacao(&posArg);
			
			if(id == NULL)
				// está dentro de uma expressão
				// logo deve ser do tipo inteiro!
				tipoesp = Tint; // só é permitido operações com inteiro
			else{
			
				// remove os underscores e espaços para obter o id da função original
				replaceSubstring(id, "__", "");
				replaceSubstring(id, "_", "");
				
				// Verifica o tipo do argumento
				Tbindingtipos binding = procuraSimboloNoAmbiente(ambiente_funcoes, getSimbolo(id));
				
				if(binding == NULL)
					// deu algum problema com o id que não era pra dar!
					return;
				
				
				binding = (Tbindingtipos) binding;	
					
				Tbindingtipos bindArgs = binding->uniao.Ttipofuncao.argumentoAnterior; // pega o último argumento
				
				int contArgs, k;
				
				// descobre quantos argumentos existem
				for(contArgs = 0; bindArgs != NULL; contArgs++)
					bindArgs = bindArgs->uniao.Ttipofuncao.argumentoAnterior;
				

				bindArgs = binding->uniao.Ttipofuncao.argumentoAnterior;
				
				// vai até o binding do argumento da posição almejada
				for(k = contArgs; k > posArg; k--)
					bindArgs = bindArgs->uniao.Ttipofuncao.argumentoAnterior;
				
				// finalmente pega o tipo do parâmetro
				tipoesp = bindArgs->uniao.Ttipofuncao.tipo;
			}
				
		}else if(strcmp(id, "<NEW STATEMENT>") == 0){
			// tipo inteiro!
			tipoesp = Tint; // por enquanto!
			
		}else{
			
			// remove os underscores e espaços para obter o id da variável original
			replaceSubstring(id, "__", "");
			replaceSubstring(id, "_", "");
			replaceSubstring(id, " ", "");
			
			bool ehVetor = removeAPartirDeAbreColchete(id);
		
			// procura o ID para achar o valor de retorno
			Tbindingtipos binding = procuraSimboloNoAmbiente(ambiente_variaveis, getSimbolo(id));
			
			if(binding == NULL)
				// deu algum problema com o id que não era pra dar!
				return;
			
			
			binding = (Tbindingtipos) binding;
			
			if(ehVetor)
				tipoesp = binding->uniao.Ttipolista.tipo;
			else
				tipoesp = binding->uniao.tipo;
				
		}
		
		// verificar se já existe.. se não existe, criá-la como variável global
		if(tipoesp == Tint){
			contChamadasInputInteger++;
			
			id = (string) malloc((7 + getTotalCasasDecimais(contChamadasInputInteger)) * sizeof(char));
			sprintf(id, "_tempI%d", contChamadasInputInteger);
			
			if(contChamadasInputInteger > totalVarTempInputInteger){
				totalVarTempInputInteger++;
				addVariavelGlobal(pascal_variavel_simples(id, Tint));
			}
	
		}else{		
			contChamadasInputString++;
			
			id = (string) malloc((7 + getTotalCasasDecimais(contChamadasInputString)) * sizeof(char));
			sprintf(id, "_tempS%d", contChamadasInputString);
			
			if(contChamadasInputString > totalVarTempInputString){
				totalVarTempInputString++;
				addVariavelGlobal(pascal_variavel_simples(id, Tstring));
			}
		}
		
		// faz uso da variável temporária
		addStatementNaFuncaoCorrente(pascal_statement(id));
		
		string anterior;
		anterior = (string) malloc((strlen(id) + 10 + 1));
		sprintf(anterior, "readln(%s);\n", id);
			
		// acrescentar um statement na linha anterior usando o readln	
		addNoStatementAnteriorDaFuncaoCorrente(pascal_statement(getStatementIdentado(anterior)));
	
	}else if(strcmp(idFuncao, "output") == 0)
		addStatementNaFuncaoCorrente(pascal_statement("writeln"));
	
	else if(strcmp(idFuncao, "main") == 0) // é estranho chamar a main, mas é válido
		addStatementNaFuncaoCorrente(pascal_statement("main"));
		
	else
		addStatementNaFuncaoCorrente(pascal_statement(traduzNomeDaFuncao(idFuncao)));
	
}

	










/**
  * Adiciona as funcões pre-definidas no ambiente global
  */
void preparaAmbiente(Ambiente ambiente_funcoes){
	
	inicioDeBloco = FALSE;
	
	contChamadasInputInteger = 0; 
	contChamadasInputString = 0;   
	totalVarTempInputInteger = 0;
	totalVarTempInputString = 0;
	
	identacao = 0;
	
	/* Cria o binder da função
		  {string|int} input(void)
	*/
	addBinder(ambiente_funcoes, getSimbolo("input"), 
			  binding_tipo_funcao(Tstrint, NULL, FALSE));
			  
			  
	/* Cria o binder da função
		  void output({string|int} x)
	*/
	addBinder(ambiente_funcoes, getSimbolo("output"), 
			  binding_tipo_funcao(Tvoid, binding_tipo_funcao(Tstrint, NULL, FALSE), FALSE));		 
	
}







// Análise Semântica

/**
  * Análise Semântica de  programa
  */
void semantica_programa(Tprograma programa){
	
	// Cria os ambientes para variáveis e funções
	Ambiente ambiente_variaveis = criaAmbiente();
	Ambiente ambiente_funcoes = criaAmbiente();
	
	inicioDeEscopo(ambiente_variaveis);
	inicioDeEscopo(ambiente_funcoes);
	
	preparaAmbiente(ambiente_funcoes);
	
	
	inicializaEstruturaDaGeracao();
	
	
	semantica_declist(ambiente_variaveis, ambiente_funcoes, programa->declist);
	
	Binder ultimaFuncao = ambiente_funcoes->topoDaPilha;
	
	// Verifica se tem funcões declaradas. Se tiver, a ultima 
	// obrigatoriamente deve ser a   void main(void)
	if(ultimaFuncao != NULL){
		
		if(ultimaFuncao->simbol != getSimbolo("main")){
			fprintf(stderr,"Erro semantico. A ultima funcao declarada deve ser a funcao  'main'!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		Tbindingtipos bindingMain = (Tbindingtipos) ultimaFuncao->valor;
		
		if(bindingMain->uniao.Ttipofuncao.tipo != Tvoid){
			fprintf(stderr,"Erro semantico. A funcao  'main' deve ser tipo 'void'!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		if(bindingMain->uniao.Ttipofuncao.argumentoAnterior != NULL){
			fprintf(stderr,"Erro semantico. Parametro da funcao 'main' deve ser ou vazio ou um unico e do tipo 'void'!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		}
	   
	}
	
	finalDeEscopo(ambiente_variaveis);
	finalDeEscopo(ambiente_funcoes);
	
	
	geraCodigo(arquivo);
	
	// destrói os ambientes
	destroiAmbiente(ambiente_variaveis);
	destroiAmbiente(ambiente_funcoes);

}


/**
  * Análise Semântica de  declaração-lista
  */
void semantica_declist(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tdeclaracaolista declist){
	
	if(declist->tipo == Fdeclist_declist_decl){
		
		semantica_declist(ambiente_variaveis, ambiente_funcoes, declist->uniao.Tdeclistdec.declist);
		
		semantica_decl(ambiente_variaveis, ambiente_funcoes, declist->uniao.Tdeclistdec.decl);
		
	}else if(declist->tipo == Fdeclist_decl)
		semantica_decl(ambiente_variaveis, ambiente_funcoes, declist->uniao.decl);
		
}


/**
  * Análise Semântica de  declaração
  */
void semantica_decl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tdeclaracao decl){
	
	if(decl->tipo == Fdecl_vardecl)
		semantica_vardecl(ambiente_variaveis, decl->uniao.vardecl);
		
	else if(decl->tipo == Fdecl_fundecl)
		semantica_fundecl(ambiente_variaveis, ambiente_funcoes, decl->uniao.fundecl);	
	
}


/**
  * Análise Semântica de  var-declaração
  */
void semantica_vardecl(Ambiente ambiente_variaveis, Tvardeclaracao vardecl){
	
	// declaracao de variavel sempre sobrescreve uma de mesmo nome, só que externa ao bloco
	
	if(vardecl->tipo == Fvardecl_tesp_id){
		
		// Verifica se o ID da variavel ja foi declarada no escopo corrente
		if(ambienteContemSimboloNoEscopo(ambiente_variaveis, vardecl->uniao.Ttesp_id.id)){
			fprintf(stderr,"Erro semantico. Variavel '%s' redeclarada!\n", 
					getIdentificadorDoSimbolo(vardecl->uniao.Ttesp_id.id));
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// Nao e possivel declarar o tipo de uma variavel como void
		if(vardecl->uniao.Ttesp_id.tesp == Tvoid){
			fprintf(stderr,"Erro semantico. Variavel '%s' nao pode ser do tipo void!\n", 
					getIdentificadorDoSimbolo(vardecl->uniao.Ttesp_id.id));
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// cria o binder e adiciona na tabela do ambiente
		addBinder(ambiente_variaveis, vardecl->uniao.Ttesp_id.id, 
				  binding_tipo_simples(vardecl->uniao.Ttesp_id.tesp));
		
		

		// adiciona a variável na estrutura da geração de código
		string varID = traduzNomeDaVariavel(getIdentificadorDoSimbolo(vardecl->uniao.Ttesp_id.id)); 
		

		// antes, deve-se verificar se é um início e final de escopo, 
		// dentro de uma função e que não faz parte de um if ou while
		if(contBlocos > 0){
			// declaração dentro de um bloco interno
			// usa um número ao final da variável
			// para poder diferenciar de outras declarações externas ao bloco
			string temp = (string) malloc(strlen(varID) * sizeof(char));
			strcpy(temp, varID);
			
			varID = (string) malloc((strlen(temp) + getTotalCasasDecimais(totalBlocosInternosComDeclaracao) + 1) * sizeof(char));
			sprintf(varID, "%s%d", temp, totalBlocosInternosComDeclaracao);
			
	
			free(temp);
		}
		
		addVariavelNaFuncaoCorrente(pascal_variavel_simples(varID, vardecl->uniao.Ttesp_id.tesp));
		
	}else if(vardecl->tipo == Fvardecl_tesp_id_num){
		
		// Verifica se o ID da variavel ja foi declarada no escopo corrente
		if(ambienteContemSimboloNoEscopo(ambiente_variaveis, vardecl->uniao.Ttesp_id_num.id)){
			fprintf(stderr,"Erro semantico. Variavel '%s' redeclarada!\n", 
					getIdentificadorDoSimbolo(vardecl->uniao.Ttesp_id_num.id));
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// Nao e possivel declarar o tipo de uma variavel como void
		if(vardecl->uniao.Ttesp_id_num.tesp == Tvoid){
			fprintf(stderr,"Erro semantico. Variavel '%s' nao pode ser do tipo void!\n", 
					getIdentificadorDoSimbolo(vardecl->uniao.Ttesp_id.id));
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// Tamanho do vetor deve ser maior que zero
		if(vardecl->uniao.Ttesp_id_num.num <= 0){
			fprintf(stderr,"Erro semantico. Tamanho do vetor '%s' deve ser um numero inteiro positivo!\n", 
					getIdentificadorDoSimbolo(vardecl->uniao.Ttesp_id.id));
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// cria o binder e adiciona na tabela do ambiente
		addBinder(ambiente_variaveis, vardecl->uniao.Ttesp_id_num.id, 
				  binding_tipo_lista(vardecl->uniao.Ttesp_id_num.tesp, vardecl->uniao.Ttesp_id_num.num));
		
		

		// adiciona a variável na estrutura da geração de código
		string varID = traduzNomeDaVariavel(getIdentificadorDoSimbolo(vardecl->uniao.Ttesp_id.id)); 
		
	
		// antes, deve-se verificar se é um início e final de escopo, 
		// dentro de uma função e que não faz parte de um if ou while
		if(contBlocos > 0){
			// declaração dentro de um bloco interno
			// usa um número ao final da variável
			// para poder diferenciar de outras declarações externas ao bloco
			string temp = (string) malloc(strlen(varID) * sizeof(char));
			strcpy(temp, varID);
			
			varID = (string) malloc((strlen(temp) + getTotalCasasDecimais(totalBlocosInternosComDeclaracao) + 1) * sizeof(char));
			sprintf(varID, "%s%d", temp, totalBlocosInternosComDeclaracao);
			
			free(temp);
		}
		
		addVariavelNaFuncaoCorrente(pascal_variavel_lista(varID, vardecl->uniao.Ttesp_id_num.tesp, vardecl->uniao.Ttesp_id_num.num));
	}
}



/**
  * Análise Semântica de  fun-declaração
  */
void semantica_fundecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tfundeclaracao fundecl){
	
	//  Nao ha chamadas recursivas.
	
	// Verifica se o ID da funcao ainda esta no ambiente
	if(procuraSimboloNoAmbiente(ambiente_funcoes, fundecl->id) != NULL){
		fprintf(stderr,"Erro semantico. Funcao '%s' redeclarada!\n", 
				getIdentificadorDoSimbolo(fundecl->id));
		destroiGeracaoDeCodigo();   
		exit(1);
	}
	
	// Cria o binder e adiciona na tabela do ambiente
	addBinder(ambiente_funcoes, fundecl->id, 
			  binding_tipo_funcao(fundecl->tesp, NULL, FALSE));
	
	// Uma variavel declarada dentro de uma funcao (isto tambem inclui os parametros) sobrepõe a global de mesmo nome
	
	
	// inicia um novo escopo de variaveis
	inicioDeEscopo(ambiente_variaveis);
	
	// Inicializa as variáveis auxiliares => para averiguar retorno da função
	contWhiles = 0;
	contIfs = 0;
	contBlocos = 0;
	totalBlocosInternosComDeclaracao = 0;
	inicioDeBloco = FALSE;
	funcaoCorrenteTemRetorno = FALSE;
	identacao = 4;
	

	// adiciona a função na estrutura da geração de código
	string funID = traduzNomeDaFuncao(getIdentificadorDoSimbolo(fundecl->id));

	
	addFuncao(pascal_funcao(funID, fundecl->tesp));
	
	
	
	// verifica a semantica dos parametros
	semantica_params(ambiente_variaveis, ambiente_funcoes, fundecl->params);
	
	// verifica a semantica do bloco
	semantica_compdecl(ambiente_variaveis, ambiente_funcoes, fundecl->compdecl, FALSE);
	
	// Valida se tem retorno no mesmo nível léxico da função principal
	analisaRetornoDaFuncaoCorrente(ambiente_funcoes);
	
	// O escopo e terminado na analise da semantica de composto-decl

}


/**
  * Análise Semântica de  params
  */
void semantica_params(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tparams params){

	if(params->tipo == Fparams_parlist)
		semantica_paramlist(ambiente_variaveis, ambiente_funcoes, params->paramlist);
	
	// nao precisa fazer nada se os params for vazio ou void
}


/**
  * Análise Semântica de  param-lista
  */
void semantica_paramlist(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tparamlista paramlist){
	
	if(paramlist->tipo == Fparamlist_parlist_param){
		
		semantica_paramlist(ambiente_variaveis, ambiente_funcoes, paramlist->uniao.Tparlist_param.paramlist);
		
		semantica_param(ambiente_variaveis, ambiente_funcoes, paramlist->uniao.Tparlist_param.param);
		
	}else if(paramlist->tipo == Fparamlist_param)
		semantica_param(ambiente_variaveis, ambiente_funcoes, paramlist->uniao.param);
		
}


/**
  * Análise Semântica de  param
  */
void semantica_param(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tparam param){
	
	// Verifica se o ID do parametro ja foi declarado no escopo
	if(ambienteContemSimboloNoEscopo(ambiente_variaveis, param->id)){
		fprintf(stderr,"Erro semantico. Parametro '%s' redeclarado!\n", 
				getIdentificadorDoSimbolo(param->id));
		destroiGeracaoDeCodigo();   
		exit(1);
	}
	
	// Nao é possível declarar o tipo de uma parametro como void
	if(param->tesp == Tvoid){
		fprintf(stderr,"Erro semantico. Parametro '%s' nao pode ser do tipo void!\n", 
				getIdentificadorDoSimbolo(param->id));
		destroiGeracaoDeCodigo();   
		exit(1);
	}

	
	if(param->tipo == Fparam_sem_colchetes){
		
		// cria o binder e adiciona na tabela do ambiente
		addBinder(ambiente_variaveis, param->id, 
				  binding_tipo_simples(param->tesp));
		
		// registra os tipos de cada parametro
		Binder funcaoCorrente = ambiente_funcoes->topoDaPilha;
		
		Tbindingtipos binding = (Tbindingtipos) funcaoCorrente->valor;
		
		// associa no binding da funcao o tipo do argumento
		binding->uniao.Ttipofuncao.argumentoAnterior = binding_tipo_funcao(param->tesp, 
																   binding->uniao.Ttipofuncao.argumentoAnterior, FALSE);
		
		// adiciona o parâmetro na estrutura da geração de código
		addParametroNaFuncaoCorrente(pascal_variavel_simples(traduzNomeDaVariavel(getIdentificadorDoSimbolo(param->id)), 
															 param->tesp));
		
	}else if(param->tipo == Fparam_com_colchetes){

		// cria o binder e adiciona na tabela do ambiente
		addBinder(ambiente_variaveis, param->id,
				  binding_tipo_lista(param->tesp, -1)); // -1 se refere a uma lista de tamanho nao especificado
		
		// registra os tipos de cada parametro
		Binder funcaoCorrente = ambiente_funcoes->topoDaPilha;
		
		Tbindingtipos binding = (Tbindingtipos) funcaoCorrente->valor;
		
		// associa no binding da funcao o tipo do argumento
		binding->uniao.Ttipofuncao.argumentoAnterior = binding_tipo_funcao(param->tesp, 
																   binding->uniao.Ttipofuncao.argumentoAnterior, TRUE);
		
		// adiciona o parâmetro na estrutura da geração de código
		addParametroNaFuncaoCorrente(pascal_variavel_lista(traduzNomeDaVariavel(getIdentificadorDoSimbolo(param->id)),
														   param->tesp, 0));
	}
	
}


/**
  * Análise Semântica de  composto-decl
  */
void semantica_compdecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tcompostodecl compdecl, bool iniciarescopo){
	
	if(iniciarescopo){
		inicioDeEscopo(ambiente_variaveis);
		
		inicioDeBloco = TRUE;
		
		if(contIfs == 0 && contWhiles == 0){
			addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado("begin\n")));
			identacao += 4;
		}
		
		contBlocos++;
	}
	

	semantica_localdecl(ambiente_variaveis, compdecl->localdecl);
	
	semantica_statementlist(ambiente_variaveis, ambiente_funcoes, compdecl->statementlist);
	
	finalDeEscopo(ambiente_variaveis);
	
	
	if(contBlocos > 0){
		contBlocos--;
		if(contIfs == 0 && contWhiles == 0){
		// se for um bloco interno (sem ser de um IF ou WHILE)
			identacao -= 4;
			addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado("end;\n")));
		}
	}
		
}


/**
  * Análise Semântica de  local-declarações
  */
void semantica_localdecl(Ambiente ambiente_variaveis, Tlocaldeclaracoes localdecl){
	
	if(localdecl->tipo == Flocdecl_locdecl_vardecl){ 
		
		if(inicioDeBloco)
			totalBlocosInternosComDeclaracao++;
		
		inicioDeBloco = FALSE;
		
		semantica_localdecl(ambiente_variaveis, localdecl->localdecl);
		
		semantica_vardecl(ambiente_variaveis, localdecl->vardecl);

	}else
		inicioDeBloco = FALSE;
	
}


/**
  * Análise Semântica de  statement-lista
  */
void semantica_statementlist(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tstatementlista statementlist){
	
	if(statementlist->tipo == Fstatm_statmlist_statm){ 
		
		semantica_statementlist(ambiente_variaveis, ambiente_funcoes, statementlist->statementlist);
		
		semantica_statement(ambiente_variaveis, ambiente_funcoes, statementlist->statement);
		
	}
}


/**
  * Análise Semântica de  statement-lista
  */
void semantica_statement(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tstatement statement){
	
	if(statement->tipo == Fstatm_expdecl)
		semantica_expdecl(ambiente_variaveis, ambiente_funcoes, statement->uniao.expdecl);
	
	else if(statement->tipo == Fstatm_compdecl)
		semantica_compdecl(ambiente_variaveis, ambiente_funcoes, statement->uniao.compdecl, TRUE);
		
	else if(statement->tipo == Fstatm_seldecl)
		semantica_seldecl(ambiente_variaveis, ambiente_funcoes, statement->uniao.seldecl);	
	
	else if(statement->tipo == Fstatm_itdecl)
		semantica_itdecl(ambiente_variaveis, ambiente_funcoes, statement->uniao.itdecl);

	else if(statement->tipo == Fstatm_retdecl)
		semantica_retdecl(ambiente_variaveis, ambiente_funcoes, statement->uniao.retdecl);
		
}



/**
  * Análise Semântica de  expressão-decl
  */
void semantica_expdecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Texpressaodecl expdecl){
	
	if(expdecl->tipo == Fexpdecl_exp){
		addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado("")));
		semantica_exp(ambiente_variaveis, ambiente_funcoes, expdecl->exp);
		addStatementNaFuncaoCorrente(pascal_statement(";\n"));
	}else
		addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado(";\n")));
	
	contChamadasInputString = 0; 
	contChamadasInputInteger = 0; 
}



/**
  * Análise Semântica de  seleção-decl
  */
void semantica_seldecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tselecaodecl seldecl){
	
	// não contabiliza os ifs que estão dentro de um while
	if(contWhiles == 0) 
		contIfs++;
	
	addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado("if(")));
	
	
	if(seldecl->tipo == Fseldecl_sem_else){
		
		Tbindingtipos expressao = semantica_exp(ambiente_variaveis, ambiente_funcoes, seldecl->uniao.Tif_sem_else.exp);
		
		// deve-se analisar o valor da expressao
		if( (expressao->tipo == Ftiposimples && expressao->uniao.tipo != Tint) ||
			(expressao->tipo == Ftipolista) ||
			(expressao->tipo == Ftipofuncao && expressao->uniao.Ttipofuncao.tipo != Tint) ){
				fprintf(stderr,"Erro semantico. Expressao condicional do 'if' eh invalida!!\n");
				destroiGeracaoDeCodigo();   
				exit(1);
		}
		
		addStatementNaFuncaoCorrente(pascal_statement(") then begin\n"));
		
		contChamadasInputString = 0; 
		contChamadasInputInteger = 0;
		
		identacao += 4;
		
		semantica_statement(ambiente_variaveis, ambiente_funcoes, seldecl->uniao.Tif_sem_else.statement);
		
		identacao -= 4;
		
		addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado("end;\n")));
		
		contChamadasInputString = 0; 
		contChamadasInputInteger = 0;
		
	}else{ // seldecl->tipo == Fseldecl_com_else
		
		Tbindingtipos expressao = semantica_exp(ambiente_variaveis, ambiente_funcoes, seldecl->uniao.Tif_com_else.exp);
		
		// deve-se analisar o valor da expressao
		if( (expressao->tipo == Ftiposimples && expressao->uniao.tipo != Tint) ||
			(expressao->tipo == Ftipolista) ||
			(expressao->tipo == Ftipofuncao && expressao->uniao.Ttipofuncao.tipo != Tint) ){
				fprintf(stderr,"Erro semantico. Expressao condicional do 'if' eh invalida!!\n");
				destroiGeracaoDeCodigo();   
				exit(1);
		}
		
		addStatementNaFuncaoCorrente(pascal_statement(") then begin\n"));
		
		identacao += 4;
		
		contChamadasInputString = 0; 
		contChamadasInputInteger = 0;
		
		semantica_statement(ambiente_variaveis, ambiente_funcoes, seldecl->uniao.Tif_com_else.statementif);
		
		identacao -= 4;		
		
		string temp1 = getStatementIdentado("end\n");
		
		string temp2 = getStatementIdentado("else begin\n");
		
		string temp = (string) malloc((strlen(temp1) + strlen(temp2) + 1) * sizeof(char));
		
		sprintf(temp, "%s%s", temp1, temp2);
		
		free(temp1);
		free(temp2);
		
		addStatementNaFuncaoCorrente(pascal_statement(temp));
		
		contChamadasInputString = 0; 
		contChamadasInputInteger = 0;
		
		identacao += 4;
		
		semantica_statement(ambiente_variaveis, ambiente_funcoes, seldecl->uniao.Tif_com_else.statementelse);
		
		identacao -= 4;
		
		addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado("end;\n")));
		
		contChamadasInputString = 0; 
		contChamadasInputInteger = 0;
		
	}
	
	
	if(contWhiles == 0)
		contIfs--;
	
}


/**
  * Análise Semântica de  iteração-decl
  */
void semantica_itdecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Titeracaodecl itdecl){
	
	contWhiles++;
	
	addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado("while(")));
	
	Tbindingtipos expressao = semantica_exp(ambiente_variaveis, ambiente_funcoes, itdecl->exp);
		
	// deve-se analisar o valor da expressão
	if( (expressao->tipo == Ftiposimples && expressao->uniao.tipo != Tint) ||
		(expressao->tipo == Ftipofuncao && expressao->uniao.Ttipofuncao.tipo != Tint) ){
			fprintf(stderr,"Erro semantico. Expressao condicional do 'while' eh invalida!!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
	}
	
	addStatementNaFuncaoCorrente(pascal_statement(") do begin\n"));
	
	contChamadasInputString = 0; 
	contChamadasInputInteger = 0;
	
	identacao += 4;
	
	semantica_statement(ambiente_variaveis, ambiente_funcoes, itdecl->statement);
	
	identacao -= 4;
	
	addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado("end;\n")));
	
	contChamadasInputString = 0; 
	contChamadasInputInteger = 0;

	contWhiles--;
}



/**
  * Análise Semântica de  retorno-decl
  */
void semantica_retdecl(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tretornodecl retdecl){
	
	if(retdecl->tipo == Fretdecl_exp){
		
		Binder funcaoCorrente = ambiente_funcoes->topoDaPilha;
		
		
		addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado(traduzNomeDaFuncao(getIdentificadorDoSimbolo(funcaoCorrente->simbol)))));
		addStatementNaFuncaoCorrente(pascal_statement(" := "));
		
		
		Tbindingtipos expressao = semantica_exp(ambiente_variaveis, ambiente_funcoes, retdecl->exp);
		
		
		
		Tbindingtipos bindingFuncao = (Tbindingtipos) funcaoCorrente->valor;
	
		//Ttipoespecificador tipoDaFuncao = ((Tbindingtipos) funcaoCorrente->valor)->uniao.Ttipofuncao.tipo;
		
		// O tipo da expressão de retorno deve ser o mesmo do da funcao corrente
		if(expressao->tipo == Ftipolista ||  !tiposSaoCompativeis(bindingFuncao, expressao)){
			fprintf(stderr,"Erro semantico. Tipo retornado nao corresponde ao tipo da funcao '%s'!\n",
					funcaoCorrente->simbol->nome);
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		string temp1 = getStatementIdentado("exit;\n");
		
		string temp = (string) malloc((2 + strlen(temp1) + 1) * sizeof(char));
		
		sprintf(temp, ";\n%s", temp1);
		
		free(temp1);
		
		
		addStatementNaFuncaoCorrente(pascal_statement(temp));
		
		contChamadasInputString = 0; 
		contChamadasInputInteger = 0;
		
		if(contWhiles == 0 && contIfs == 0 && contBlocos == 0)
			funcaoCorrenteTemRetorno = TRUE;
		
	}else if(retdecl->tipo == Fretdecl_){
		
		Binder funcaoCorrente = ambiente_funcoes->topoDaPilha;
		
		Ttipoespecificador tipoDaFuncao = ((Tbindingtipos) funcaoCorrente->valor)->uniao.Ttipofuncao.tipo;
		
		// return ;  só pode se referir a uma função do tipo void
		if(tipoDaFuncao != Tvoid){
			fprintf(stderr,"Erro semantico. Tipo retornado nao corresponde ao tipo da funcao '%s'!\n",
					funcaoCorrente->simbol->nome);
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		
		addStatementNaFuncaoCorrente(pascal_statement(getStatementIdentado("exit;\n")));
		
		contChamadasInputString = 0; 
		contChamadasInputInteger = 0;
		
	}
}



/**
  * Análise Semântica de  expressão
  */
Tbindingtipos semantica_exp(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Texpressao exp){
	
	if(exp->tipo == Fexp_var_exp){
		
		// atribuição é uma operacao booleana
		
		Tbindingtipos bindingVar = semantica_var(ambiente_variaveis, ambiente_funcoes, exp->uniao.Tvar_exp.var);
		
		// Verificação, pois alguma falha pode ter acontecido que o tipo de var nao foi corretamente alocado
		if(bindingVar->uniao.tipo == Tvoid){
			fprintf(stderr,"Erro semantico. Tipo 'void' nao recebe valores!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		} 
		
		
		addStatementNaFuncaoCorrente(pascal_statement(" := "));
		
		
		Tbindingtipos bindingExp = semantica_exp(ambiente_variaveis, ambiente_funcoes, exp->uniao.Tvar_exp.exp);

		// Avalia a atribuição
		if(!tiposSaoCompativeis(bindingVar, bindingExp)){
			fprintf(stderr,"Erro semantico. Atribuicao entre tipos incompativeis!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		return binding_tipo_simples(Tint); // atribuição que dá certo tem retorno do tipo inteiro
		
	}
	
	if(exp->tipo == Fexp_simplexp)
		return semantica_simplexp(ambiente_variaveis, ambiente_funcoes, exp->uniao.simplexp);
		
	
	return binding_tipo_simples(Tvoid);
	
}


/**
  * Análise Semântica de  var
  */
Tbindingtipos semantica_var(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tvar var){
	
	if(var->tipo == Fvar_id){
		
		Tbindingtipos binding = procuraSimboloNoAmbiente(ambiente_variaveis, var->uniao.id);
		
		if(binding == NULL){
			fprintf(stderr,"Erro semantico. Variavel '%s' nao declarada!\n",
					getIdentificadorDoSimbolo(var->uniao.id));
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		
		
		string varID = traduzNomeDaVariavel(getIdentificadorDoSimbolo(var->uniao.id)); 
		
		if(contBlocos > 0){
			// uso de uma variável dentro de um bloco... deve-se verificar
			// se esta variável foi declarada dentro ou se é fora do escopo
			string temp = (string) malloc((strlen(varID) + getTotalCasasDecimais(totalBlocosInternosComDeclaracao)) * sizeof(char));
			sprintf(temp, "%s%d" , varID, totalBlocosInternosComDeclaracao);
			
			if(variavelEstaNaFuncaoCorrente(temp)){
				varID = (string) malloc(strlen(temp) * sizeof(char));
				strcpy(varID, temp);
			}
			
			free(temp);
		}
		
		addStatementNaFuncaoCorrente(pascal_statement(varID));
		
		
		return binding;
		
	}
	
	if(var->tipo == Fvar_id_exp){
		
		Tbindingtipos binding = procuraSimboloNoAmbiente(ambiente_variaveis, var->uniao.Tid_exp.id);
		
		if(binding == NULL){
			fprintf(stderr,"Erro semantico. Variavel '%s' nao declarada!\n",
					getIdentificadorDoSimbolo(var->uniao.Tid_exp.id));
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// pega o verdadeiro índice traduzido
		string varID = traduzNomeDaVariavel(getIdentificadorDoSimbolo(var->uniao.Tid_exp.id)); 
		
		if(contBlocos > 0){
			// uso de uma variável dentro de um bloco... deve-se verificar
			// se esta variável foi declarada dentro ou se é fora do escopo
			string temp = (string) malloc((strlen(varID) + getTotalCasasDecimais(totalBlocosInternosComDeclaracao)) * sizeof(char));
			sprintf(temp, "%s%d" , varID, totalBlocosInternosComDeclaracao);
			
			if(variavelEstaNaFuncaoCorrente(temp)){
				varID = (string) malloc(strlen(temp) * sizeof(char));
				strcpy(varID, temp);
			}
			
			free(temp);
			
		}
		
		
		addStatementNaFuncaoCorrente(pascal_statement(varID));
		
		//addStatementNaFuncaoCorrente(pascal_statement(getIdentificadorDoSimbolo(var->uniao.Tid_exp.id)));
		addStatementNaFuncaoCorrente(pascal_statement("["));
		
		Tbindingtipos expressao = semantica_exp(ambiente_variaveis, ambiente_funcoes, var->uniao.Tid_exp.exp);
		
		// o valor dentro do colchete deve ser do tipo inteiro simples
		if(expressao->tipo != Ftiposimples || expressao->uniao.tipo != Tint){
			fprintf(stderr,"Erro semantico. indice de '%s' deve ser um valor inteiro!\n",
					getIdentificadorDoSimbolo(var->uniao.Tid_exp.id));
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// o índice em C equivale a o índice + 1 em Pascal
		addStatementNaFuncaoCorrente(pascal_statement(" + 1]"));
		
		// string str[10];
		// str    // tipo: string[]
		// str[0] // tipo: string
		return binding_tipo_simples(binding->uniao.Ttipolista.tipo);
	
	}
	
	return binding_tipo_simples(Tvoid);
	
}



/**
  * Análise Semântica de  simples-expressão
  */
Tbindingtipos semantica_simplexp(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tsimplesexpressao simplexp){
	
	
	if(simplexp->tipo == Fsimplexp_simplexp_rel_simplexp){
		
		Tbindingtipos simplexp1 = semantica_simplexp(ambiente_variaveis, ambiente_funcoes, 
													 simplexp->uniao.Tsimplexp_rel_simplexp.simplexp1);
		
		
		addStatementNaFuncaoCorrente(pascal_statement(traduzRelacional(simplexp->uniao.Tsimplexp_rel_simplexp.rel)));

		
		Tbindingtipos simplexp2 = semantica_simplexp(ambiente_variaveis, ambiente_funcoes, 
													 simplexp->uniao.Tsimplexp_rel_simplexp.simplexp2);
		
		// Avalia a relacao
		if(!tiposSaoCompativeis(simplexp1, simplexp2)){
			fprintf(stderr,"Erro semantico. Operador condicional entre tipos incompativeis!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// nao existe operacao relacional entre tipos string ou entre listas
		if( (simplexp1->tipo == Ftiposimples && simplexp1->uniao.tipo == Tstring) ||
			(simplexp1->tipo == Ftipofuncao && simplexp1->uniao.Ttipofuncao.tipo == Tstring) ||
			(simplexp1->tipo == Ftipolista) ){
				fprintf(stderr,"Erro semantico. Operacao relacional eh restrita somente a tipos 'int'!\n");
				destroiGeracaoDeCodigo();   
				exit(1);
		}
		
		// operacao relacional retorna um tipo inteiro (como se fosse o booleano)
		return binding_tipo_simples(Tint);
		
	}
	
	if(simplexp->tipo == Fsimplexp_simplexp_soma_simplexp){
	
		Tbindingtipos simplexp1 = semantica_simplexp(ambiente_variaveis, ambiente_funcoes, 
													 simplexp->uniao.Tsimplexp_soma_simplexp.simplexp1);


		addStatementNaFuncaoCorrente(pascal_statement(traduzSoma(simplexp->uniao.Tsimplexp_soma_simplexp.soma)));
		
		
		Tbindingtipos simplexp2 = semantica_simplexp(ambiente_variaveis, ambiente_funcoes, 
													 simplexp->uniao.Tsimplexp_soma_simplexp.simplexp2);
		
		// Avalia a relacao
		if(!tiposSaoCompativeis(simplexp1, simplexp2)){
			fprintf(stderr,"Erro semantico. Operador de soma entre tipos incompativeis!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// nao existe operacao de soma (concatenação) ou subtração entre tipos string ou entre listas
		if( (simplexp1->tipo == Ftiposimples && simplexp1->uniao.tipo == Tstring) ||
			(simplexp1->tipo == Ftipofuncao && simplexp1->uniao.Ttipofuncao.tipo == Tstring) ||
			(simplexp1->tipo == Ftipolista) ){
				fprintf(stderr,"Erro semantico. Operacao de soma ou subtracao eh restrita somente a tipos 'int'!\n");
				destroiGeracaoDeCodigo();   
				exit(1);
		}
		
		// Só pode ser do tipo inteiro e simples....
		return binding_tipo_simples(Tint);
		
	}
	
	if(simplexp->tipo == Fsimplexp_simplexp_mult_simplexp){
		
		Tbindingtipos simplexp1 = semantica_simplexp(ambiente_variaveis, ambiente_funcoes, 
													 simplexp->uniao.Tsimplexp_mult_simplexp.simplexp1);

		
		
		addStatementNaFuncaoCorrente(pascal_statement(traduzMult(simplexp->uniao.Tsimplexp_mult_simplexp.mult)));
		
		
		Tbindingtipos simplexp2 = semantica_simplexp(ambiente_variaveis, ambiente_funcoes, 
													 simplexp->uniao.Tsimplexp_mult_simplexp.simplexp2);
		
		// Avalia a relacao
		if(!tiposSaoCompativeis(simplexp1, simplexp2)){
			fprintf(stderr,"Erro semantico. Operador de soma entre tipos incompativeis!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		// nao existe operacao de multiplicação ou divisão entre tipos string ou entre listas
		if( (simplexp1->tipo == Ftiposimples && simplexp1->uniao.tipo == Tstring) ||
			(simplexp1->tipo == Ftipofuncao && simplexp1->uniao.Ttipofuncao.tipo == Tstring) ||
			(simplexp1->tipo == Ftipolista) ){
				fprintf(stderr,"Erro semantico. Operacao de multiplicacao ou divisao eh restrita somente a tipos 'int'!\n");
				destroiGeracaoDeCodigo();   
				exit(1);
		}
		
		// Só pode ser do tipo inteiro e simples....
		return binding_tipo_simples(Tint);
		
	}
	
	if(simplexp->tipo == Fsimplexp_exp)
		return semantica_exp(ambiente_variaveis, ambiente_funcoes, simplexp->uniao.exp);
	
	if(simplexp->tipo == Fsimplexp_var)
		return semantica_var(ambiente_variaveis, ambiente_funcoes, simplexp->uniao.var);
	
	if(simplexp->tipo == Fsimplexp_ativacao)
		return semantica_ativacao(ambiente_variaveis, ambiente_funcoes, simplexp->uniao.ativacao);
	
	if(simplexp->tipo == Fsimplexp_num){
		
		string numero;

		numero = (string) malloc(getTotalCasasDecimais(simplexp->uniao.num) * sizeof(char));
	
		sprintf(numero, "%d", simplexp->uniao.num);
		
		addStatementNaFuncaoCorrente(pascal_statement(numero));
	
		return binding_tipo_simples(Tint);
	}
	
	if(simplexp->tipo == Fsimplexp_str){
		
		addStatementNaFuncaoCorrente(pascal_statement(traduzString(simplexp->uniao.str)));
		
		return binding_tipo_simples(Tstring);
	}
	
	return binding_tipo_simples(Tvoid);
}



/**
  * Análise Semântica de  ativação
  */
Tbindingtipos semantica_ativacao(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Tativacao ativacao){
	
	Tbindingtipos bindingFuncao = procuraSimboloNoAmbiente(ambiente_funcoes, ativacao->id);
	
	if(bindingFuncao == NULL){
		fprintf(stderr,"Erro semantico. Funcao '%s' nao declarada!\n",
				getIdentificadorDoSimbolo(ativacao->id));
		destroiGeracaoDeCodigo();   
		exit(1);
	}
	


	adicionaStatementDeChamadaDeFuncao(ambiente_variaveis, ambiente_funcoes, getIdentificadorDoSimbolo(ativacao->id));
	

	Tbindingtipos bindingArgs = semantica_args(ambiente_variaveis, ambiente_funcoes, ativacao->args);
	
	
	Ttipoespecificador tipoDaFuncao = analisaChamadaDeFuncao(getIdentificadorDoSimbolo(ativacao->id), 
															 (Tbindingtipos) bindingFuncao, bindingArgs);
	
	
	return binding_tipo_simples(tipoDaFuncao);
	
}



/**
  * Análise Semântica de  args
  */
Tbindingtipos semantica_args(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Targs args){
	
	if(args->tipo == Fargs_arglist){
		addStatementNaFuncaoCorrente(pascal_statement("("));
		Tbindingtipos binding = semantica_arglista(ambiente_variaveis, ambiente_funcoes, args->arglista);
		addStatementNaFuncaoCorrente(pascal_statement(")"));
		return binding;
	}
	// significa que nao tem parametros
	// e argumento = NULL
	return NULL;
	
}


/**
  * Análise Semântica de  arg-lista
  */
Tbindingtipos semantica_arglista(Ambiente ambiente_variaveis, Ambiente ambiente_funcoes, Targlista arglista){
	
	if(arglista->tipo == Farglista_arglista_exp){
		
		Tbindingtipos bindingArgs = semantica_arglista(ambiente_variaveis, ambiente_funcoes, 
													   arglista->uniao.Targlista_exp.arglista);
		
		addStatementNaFuncaoCorrente(pascal_statement(", "));
		
		Tbindingtipos bindingExp = semantica_exp(ambiente_variaveis, ambiente_funcoes, arglista->uniao.Targlista_exp.exp);
		
		bool ehVetor = FALSE;
		Ttipoespecificador tipo = Tvoid;
		
		if(bindingExp->tipo == Ftiposimples)
			tipo = bindingExp->uniao.tipo;
			
		else if(bindingExp->tipo == Ftipolista){
			tipo = bindingExp->uniao.Ttipolista.tipo;
			ehVetor = TRUE;
			
		}else if(bindingExp->tipo == Ftipofuncao)
			tipo = bindingExp->uniao.Ttipofuncao.tipo;
		
		else{
			fprintf(stderr,"Erro semantico. Argumento(s) invalido!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		return binding_tipo_funcao(tipo, bindingArgs, ehVetor);
		
	}else if(arglista->tipo == Farglista_exp){
		
		Tbindingtipos bindingExp = semantica_exp(ambiente_variaveis, ambiente_funcoes, arglista->uniao.exp);
		
		bool ehVetor = FALSE;
		Ttipoespecificador tipo = Tvoid;
		
		if(bindingExp->tipo == Ftiposimples)
			tipo = bindingExp->uniao.tipo;
			
		else if(bindingExp->tipo == Ftipolista){
			tipo = bindingExp->uniao.Ttipolista.tipo;
			ehVetor = TRUE;
			
		}else if(bindingExp->tipo == Ftipofuncao)
			tipo = bindingExp->uniao.Ttipofuncao.tipo;
		
		else{
			fprintf(stderr,"Erro semantico. Argumento(s) invalido(s)!\n");
			destroiGeracaoDeCodigo();   
			exit(1);
		}
		
		return binding_tipo_funcao(tipo, NULL, ehVetor);
		
	}
	
	return NULL;
}