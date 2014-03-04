#ifndef SIMBOLOS_H
#define SIMBOLOS_H

#include "util.h"

/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 03


		 INTERFACE DOS S�MBOLOS E DOS AMBIENTES 
	
*/


#define SIZE 127


/* S�mbolos */
typedef struct TSimbolo *Simbolo;  

struct TSimbolo {	string nome;         
					Simbolo proxSimbolo;
				 };

// Fun��es

// Obt�m o s�mbolo na tabela de s�mbolos a partir da identifica��o.
Simbolo getSimbolo(string nome);   

// Obt�m o identificador do s�mbolo    
string getIdentificadorDoSimbolo(Simbolo simbol); 

// Destr�i a cadeia de s�mbolos
void destroiSimbolo(Simbolo simbolo);

// Destr�i todas as cadeias de s�mbolos da tabela de strings
void destroiSimbolos();





/* Ambientes */
typedef struct TBinder *Binder; 
typedef struct TAmbiente *Ambiente;


// Estrutura que associa um tipo de dado a um identificador
struct TBinder { Simbolo simbol;      
				 void *valor; // deixa o valor do tipo gen�rico, para que seja poss�vel compartilhar a estrutura
				 Binder proximoDaLista;    // ponteiro para o pr�ximo binder da lista encadeada
				 Binder antigoTopoDaPilha; // ponteiro para o antigo topo da pilha
			   }; 

struct TAmbiente  {	Binder tabela[SIZE];   
					Binder topoDaPilha;  // ponteiro para o �ltimo binder inserido
				  };

// Cria um novo ambiente
Ambiente criaAmbiente();

// Procura o s�mbolo na tabela do ambiente
void *procuraSimboloNoAmbiente(Ambiente ambiente, Simbolo simbol); 

// Insere um s�mbolo indicador de in�cio de escopo na tabela
void inicioDeEscopo(Ambiente ambiente); 

// Remove todos os s�mbolos da tabela que forem encontrados at� o marcador de in�cio de escopo for encontrado
void finalDeEscopo(Ambiente ambiente);  

// Adiciona a associa��o entre o s�mbolo e o tipo na tabela do ambiente
void addBinder(Ambiente ambiente, Simbolo simbol, void *valor);

// Verifica se o s�mbolo est� no escopo corrente do ambiente
bool ambienteContemSimboloNoEscopo(Ambiente ambiente, Simbolo simbol); 


#endif
