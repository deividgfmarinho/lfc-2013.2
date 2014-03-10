#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "simbolos.h"

/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 03
   
   
		ESTRUTURA DE DADOS DA TABELA DE SÍMBOLOS

		 
*/

	
	
/**
  * Função de Hashing
  */	
unsigned int hash(string chave){
	unsigned int indice = 0;
	int i = 0;
	
	while(chave[i] != '\0'){
		indice = indice*65599 + chave[i];
		++i;
	}
	
	return indice;
}		
	
	

/* SIMBOLOS */

	
/**
  * Cria um símbolo
  */				
Simbolo criasimbolo(string nome, Simbolo proxSimbolo) { 
	Simbolo simbol = malloc(sizeof(*simbol));
	simbol->nome = nome; 
	simbol->proxSimbolo = proxSimbolo;
	return simbol;
}	


// Cria a tabela de strings
static Simbolo tabelaDeStrings[SIZE];  


/**
  * Obtém o símbolo na tabela de strings a partir da identificação.
  * Caso o símbolo ainda não tenha sido registrado,
  * esta função o registra na tabela de strings.
  */
Simbolo getSimbolo(string nome) { 

	int indice = hash(nome) % SIZE;
	
	// pega a lista encadeada correspondente ao índice do símbolo
	Simbolo s = tabelaDeStrings[indice]; 
	
	Simbolo simbol;
	
	// verifica que já foi registrado
	for(simbol = s; simbol; simbol = simbol->proxSimbolo)
		if(strcmp(simbol->nome, nome) == 0) 
			// retorna-o
			return simbol;
	
	// se não estava registrado, o registra agora
	// deslocando todos os elementos da lista para a direita
	simbol = criasimbolo(nome, s);
	
	// atualiza o ponteiro da tabela de símbolos
	tabelaDeStrings[indice] = simbol;
	
	return simbol;
}
	
	
/**
  * Obtém o identificador do símbolo.
  */	
string getIdentificadorDoSimbolo(Simbolo simbol) { 
	return simbol->nome;
}


/**
  * Retira da memória todos os simbolos da cadeia de simbolos informada
  */
void destroiSimbolo(Simbolo simbolo){
	
	while(simbolo != NULL){
		//free(simbolo->nome);
		Simbolo s = simbolo;
		simbolo = simbolo->proxSimbolo;
		free(s);
	}
	
}


/**
  * Retira da memória todos os simbolos
  */
void destroiSimbolos(){
	
	int k;
	
	for(k = 0; k < SIZE; k++){
		destroiSimbolo(tabelaDeStrings[k]);
		tabelaDeStrings[k] = NULL;
	}
	
}


/* FIM - SÍMBOLOS */







/* AMBIENTES */
						 

/**
  * Cria a associação entre um símbolo e um valor
  */
Binder criaBinder(Simbolo simbol, void *valor, Binder proximoDaLista, Binder antigoTopoDaPilha){ 
	Binder binder = malloc(sizeof(*binder));
	binder->simbol = simbol; 
	binder->valor = valor; 
	binder->proximoDaLista = proximoDaLista; 
	binder->antigoTopoDaPilha = antigoTopoDaPilha; 
	return binder;
}



		
/**
  * Cria o ambiente
  */				
Ambiente criaAmbiente(){  
	Ambiente ambiente = malloc(sizeof(*ambiente));
	// não tem símbolos ainda 
	ambiente->topoDaPilha = NULL;
	
	int i;
	for (i = 0; i < SIZE; i++)
		ambiente->tabela[i] = NULL;
		
	return ambiente; 
}



/**
  * Procura o símbolo no ambiente
  */
void *procuraSimboloNoAmbiente(Ambiente ambiente, Simbolo simbol) { 
	int indice;
	Binder binder;
	
	indice = ((unsigned) simbol) % SIZE;
	
	for(binder = ambiente->tabela[indice]; binder; binder = binder->proximoDaLista)
		if (binder->simbol == simbol) 
			return binder->valor;
			
	return NULL;
}


// Cria um símbolo para identificar o marcador de início de escopo
static struct TSimbolo marcadorDeEscopo = {"<mark>", 0};


/**
  * Insere um símbolo indicador de início de escopo no ambiente
  */
void inicioDeEscopo(Ambiente ambiente) {  
	addBinder(ambiente, &marcadorDeEscopo, NULL); 
}

/**
  * Remove todos os símbolos da tabela que forem encontrados 
  * até o marcador de início de escopo for encontrado
  */
void finalDeEscopo(Ambiente ambiente) { 
	Simbolo simbol;
	Binder binder; 
	int indice;
	
	do {		
		// pegar o binder do topo da pilha
		// (que é a que vai ser removida)
		binder = ambiente->topoDaPilha;
		// pega o primeiro simbolo da associação
		simbol = binder->simbol;
		// pega o índice dele na tabela do ambiente
		indice = ((unsigned) simbol) % SIZE;
		// atualiza o ponteiro da tabela deslocando 
		// os símbolos para a esquerda da lista encadeada
		ambiente->tabela[indice] = binder->proximoDaLista;
		// atualiza o ponteiro do topo da pilha
		ambiente->topoDaPilha = binder->antigoTopoDaPilha;
		// Com as ligações desfeitas para o símbolo (agora
		// ele não pertence mais a nenhuma cadeia da tabela)
		// remove o símbolo da memória
		free(binder);
	}while(simbol != &marcadorDeEscopo);
}


/**
  * Adiciona a associação entre o símbolo e o tipo no ambiente
  */
void addBinder(Ambiente ambiente, Simbolo simbol, void *valor){ 
	int indice;
	indice = ((unsigned) simbol) % SIZE;
	
	// cria a associação, deslocando a lista para a direita
	Binder binder = criaBinder(simbol, valor, ambiente->tabela[indice], ambiente->topoDaPilha);
	
	// atualiza os ponteiros da pilha e da lista, deslocando todas
	// as associações para a direita da lista encadeada
	ambiente->tabela[indice] = binder;
	ambiente->topoDaPilha = binder;
}



/**
  * Verifica se o símbolo está no ambiente
  */
bool ambienteContemSimboloNoEscopo(Ambiente ambiente, Simbolo simbol){
	Binder binder = ambiente->topoDaPilha;	
	Simbolo satual = (ambiente->topoDaPilha)->simbol;
	
	while(satual != NULL && satual != simbol && satual != &marcadorDeEscopo){
		binder = binder->antigoTopoDaPilha;
		satual = binder->simbol;
	}
	
	if(satual == simbol)
		return TRUE;
	
	return FALSE;
}


/* FIM - AMBIENTES */

