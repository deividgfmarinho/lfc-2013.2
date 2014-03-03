#include "util.h"
#include "arvoreabstrata.h"


/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 03
   
   
				INTERFACE DA GERAÇÃO DE CÓDIGO DE C- PARA PASCAL

		 
*/



typedef struct GCvariaveis *Pvariaveis; 
typedef struct GCfuncoes *Pfuncoes; // funções e procedimentos
typedef struct GCstatements *Pstatements; // o restante



struct GCvariaveis {
	
	enum{GFtiposimples, GFtipolista} tipo;
	
	string identificador;
	Ttipoespecificador tipoesp;
	int num;
	Pvariaveis proximaVariavel;

};


struct GCfuncoes {
	
	string identificador;
	Ttipoespecificador tipo;
	Pvariaveis argumentos;
	Pvariaveis variaveis;
	Pstatements statements;
	Pstatements ultimoStatement;
	
	Pfuncoes proximaFuncao;

};



struct GCstatements {
	
	string statement;
	
	Pstatements proximoStatement;

};


Pvariaveis pascal_variavel_simples(string identificador, Ttipoespecificador tipoesp);
Pvariaveis pascal_variavel_lista(string identificador, Ttipoespecificador tipoesp, int num);
Pfuncoes pascal_funcao(string identificador, Ttipoespecificador tipo);
Pstatements pascal_statement(string statement);






// estrutura do programa
string nomeDoPrograma;
Pvariaveis variaveisGlobais;  // as da main também entram aqui
Pfuncoes funcoes; // funções e procedimentos


// se não existir, cria um novo
void addVariavelGlobal(Pvariaveis variavel);
void addFuncao(Pfuncoes funcao);
void addParametroNaFuncaoCorrente(Pvariaveis argumento);
bool variavelEstaNaFuncaoCorrente(string id);
void addVariavelNaFuncaoCorrente(Pvariaveis variavel);
bool addStatementNaFuncaoCorrente(Pstatements statement);
string getVariavelDaAtribuicao();
string getFuncaoDeAtivacao(int *posArg);


// util
string traduzTipo(Ttipoespecificador tipo);
string traduzRelacional(Trelacional rel);
string traduzSoma(Tsoma soma);
string traduzMult(Tmult mult);
string traduzString(string str);
string traduzNomeDaFuncao(string funcao);
string traduzNomeDaVariavel(string variavel);
bool compareInsensitiveStrings(string str1, string str2);
void replaceSubstring(string str, string sub, string new);



void inicializaEstruturaDaGeracao();				
void geraCodigo(string nomeDoArquivo);
void escreveArquivo();
void escreveVariaveisGlobais();
void escreveFuncoes();
