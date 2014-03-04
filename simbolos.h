#ifndef SIMBOLOS_H
#define SIMBOLOS_H

#include "util.h"

/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 03


		 INTERFACE DOS SÍMBOLOS E DOS AMBIENTES 
	
*/


#define SIZE 127


/* Símbolos */
typedef struct TSimbolo *Simbolo;  

struct TSimbolo {	string nome;         
					Simbolo proxSimbolo;
				 };

// Funções

// Obtém o símbolo na tabela de símbolos a partir da identificação.
Simbolo getSimbolo(string nome);   

// Obtém o identificador do símbolo    
string getIdentificadorDoSimbolo(Simbolo simbol); 

// Destrói a cadeia de símbolos
void destroiSimbolo(Simbolo simbolo);

// Destrói todas as cadeias de símbolos da tabela de strings
void destroiSimbolos();





/* Ambientes */
typedef struct TBinder *Binder; 
typedef struct TAmbiente *Ambiente;


// Estrutura que associa um tipo de dado a um identificador
struct TBinder { Simbolo simbol;      
				 void *valor; // deixa o valor do tipo genérico, para que seja possível compartilhar a estrutura
				 Binder proximoDaLista;    // ponteiro para o próximo binder da lista encadeada
				 Binder antigoTopoDaPilha; // ponteiro para o antigo topo da pilha
			   }; 

struct TAmbiente  {	Binder tabela[SIZE];   
					Binder topoDaPilha;  // ponteiro para o último binder inserido
				  };

// Cria um novo ambiente
Ambiente criaAmbiente();

// Procura o símbolo na tabela do ambiente
void *procuraSimboloNoAmbiente(Ambiente ambiente, Simbolo simbol); 

// Insere um símbolo indicador de início de escopo na tabela
void inicioDeEscopo(Ambiente ambiente); 

// Remove todos os símbolos da tabela que forem encontrados até o marcador de início de escopo for encontrado
void finalDeEscopo(Ambiente ambiente);  

// Adiciona a associação entre o símbolo e o tipo na tabela do ambiente
void addBinder(Ambiente ambiente, Simbolo simbol, void *valor);

// Verifica se o símbolo está no escopo corrente do ambiente
bool ambienteContemSimboloNoEscopo(Ambiente ambiente, Simbolo simbol); 


#endif
