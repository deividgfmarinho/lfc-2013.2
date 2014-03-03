#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geradordecodigo.h"
#include "util.h"

/*
   Deivid Goes Farias Marinho
   201110005298
   Trabalho de LFC - Parte 03
   
   
				GERAÇÃO DE CÓDIGO DE C- PARA PASCAL

		 
*/

// Global
FILE* arqsaida;




Pvariaveis pascal_variavel_simples(string identificador, Ttipoespecificador tipoesp){
	Pvariaveis v = malloc(sizeof(*v));
	v->tipo = GFtiposimples;
	v->identificador = identificador;
	v->tipoesp = tipoesp;
	v->num = 0;
	v->proximaVariavel = NULL;	
	return v;
}


Pvariaveis pascal_variavel_lista(string identificador, Ttipoespecificador tipoesp, int num){
	Pvariaveis v = malloc(sizeof(*v));
	v->tipo = GFtipolista;
	v->identificador = identificador;
	v->tipoesp = tipoesp;
	v->num = num;
	v->proximaVariavel = NULL;		
	return v;
}


Pfuncoes pascal_funcao(string identificador, Ttipoespecificador tipo){
	Pfuncoes f = malloc(sizeof(*f));
	f->identificador = identificador;
	f->tipo = tipo;
	f->argumentos = NULL;
	f->variaveis = NULL;
	f->statements = NULL;
	f->ultimoStatement = NULL;
	f->proximaFuncao = NULL;
	return f;				
}


Pstatements pascal_statement(string statement){
	Pstatements s = malloc(sizeof(*s));
	s->statement = statement;
	s->proximoStatement = NULL;
	return s;
}




/**
  * Recupera um tipo definido. Se não foi, o define e o retorna.
  */
/*Ptipos getTipo(int tamanho, Ttipoespecificador tipo){
	
	Ptipos t;
	Ptipos tAnterior = NULL;
	int cont = 1;
	
	for(t = tiposNecessarios; t != NULL; t = t->proximoTipo){
		cont++;
		tAnterior = t;
		if (t->tamanho == tamanho && t->tipo == tipo) 
			return t;
	}
	
	string id;
	
	// Como os argumentos de C não determinam o valor
	// e as variáveis declaradas tem valor fixo de 
	// elementos do vetor, set tamanho = 0 e defina
	// um tipo que vai dar erro na compilação do arquivo
	// pascal, para que o usuário modifique isso manualmente
	if(tamanho == 0){
		
		id = (string) malloc(7 * sizeof(char));
		
		strcpy(id, "vetArg");
		
		if(tipo == Tint)
			strcat(id, "I"); // integer
		else
			strcat(id, "S"); // string
		
	}else{
		
		id = (string) malloc((3 + getTotalCasasDecimais(cont)) * sizeof(char));

		sprintf(id, "vet%d", cont);
	}
	
	t = pascal_define_tipo(id, tamanho, tipo, NULL);
	
	if(tAnterior != NULL)
		tAnterior->proximoTipo = t;
	else
		tiposNecessarios = t;
	
	return t;
} */


/**
  * Adiciona uma variável à estrutura
  */
void addVariavelGlobal(Pvariaveis variavel){
	
	if(variaveisGlobais == NULL)
		variaveisGlobais = variavel;
		
	else{
	
		Pvariaveis v = variaveisGlobais;
		
		for(; v->proximaVariavel != NULL; v = v->proximaVariavel)
			;
		
		v->proximaVariavel = variavel;

	}
	
}


/**
  * Adiciona uma função à estrutura
  */
void addFuncao(Pfuncoes funcao){
	
	if(funcoes == NULL)
		funcoes = funcao;
		
	else{
	
		Pfuncoes f = NULL;
		
		for(f = funcoes; f->proximaFuncao != NULL; f = f->proximaFuncao)
			;
		
		f->proximaFuncao = funcao;
	}
	
}




/**
  * Adiciona um statement na função corrente
  */
void addParametroNaFuncaoCorrente(Pvariaveis argumento){
	
	if(funcoes == NULL)
		return;
		
	Pfuncoes f = NULL;
		
	for(f = funcoes; f->proximaFuncao != NULL; f = f->proximaFuncao)
		;
	
	
	if(f->argumentos == NULL)
		f->argumentos = argumento;
		
	else{
		
		Pvariaveis a = f->argumentos;
		
		for(; a->proximaVariavel != NULL; a = a->proximaVariavel)
			;
		
		a->proximaVariavel = argumento;

	}
	
}


/**
  * Procura pela variável nas variáveis globais
  *//*
bool variavelEhGlobal(string id){
	
	Pvariaveis v = variaveisGlobais;
		
	for(; v != NULL && strcmp(v->identificador, id) != 0; v = v->proximaVariavel)
		;
		
	if(v == NULL)
		return FALSE;
	
	return TRUE;
} */

/**
  * Procura pela variável na função corrente
  */
bool variavelEstaNaFuncaoCorrente(string id){
	
	Pvariaveis v = NULL;
	
	if(funcoes == NULL){
	
		// variavel é global
		if(variaveisGlobais == NULL)
			return FALSE;
			
		 v = variaveisGlobais;
		 
	}else{
	
		Pfuncoes f = NULL;
			
		for(f = funcoes; f->proximaFuncao != NULL; f = f->proximaFuncao)
			;
	
	
		if(strcmp(f->identificador, "main") == 0)
			v = variaveisGlobais;
		
		else{ 
			if(f->variaveis == NULL)
				return FALSE;
				
			v = f->variaveis;	
		}
		
	}
		
	for(; v != NULL && strcmp(v->identificador, id) != 0; v = v->proximaVariavel)
		;
		
	if(v == NULL)
		return FALSE;
	
	return TRUE;
}


/**
  * Adiciona uma variável na função corrente
  */
void addVariavelNaFuncaoCorrente(Pvariaveis variavel){
	
	if(funcoes == NULL){
		addVariavelGlobal(variavel);
		return;
	}
	
	Pfuncoes f = NULL;
		
	for(f = funcoes; f->proximaFuncao != NULL; f = f->proximaFuncao)
		;
	
	
	if(strcmp(f->identificador, "main") == 0){
		addVariavelGlobal(variavel);
		return;
	}
	
	if(f->variaveis == NULL)
		f->variaveis = variavel;
		
	else{
		
		Pvariaveis v = f->variaveis;
		
		for(; v->proximaVariavel != NULL; v = v->proximaVariavel)
			;
		
		v->proximaVariavel = variavel;

	}	
	
}


/**
  * Adiciona um statement anterior a última inserida
  */
void addNoStatementAnteriorDaFuncaoCorrente(Pstatements statement){
	
	if(funcoes == NULL)
		return;
		
	Pfuncoes f = NULL;
		
	for(f = funcoes; f->proximaFuncao != NULL; f = f->proximaFuncao)
		;
	
	
	if(f->ultimoStatement == NULL){
		f->statements = statement;
		f->ultimoStatement = statement;
	}else{
	
		Pstatements s = NULL;
		
		for(s = f->statements; s->proximoStatement != NULL && s->proximoStatement != f->ultimoStatement; s = s->proximoStatement)
			;
		
		statement->proximoStatement = f->ultimoStatement;
		
		s->proximoStatement = statement;
		
	}
	
}


/**
  * Adiciona um statement na função corrente
  *
  * Retorna TRUE se um novo statement foi adicionado
  * Retorna FALSE se este foi adicionado a um incompleto
  */
bool addStatementNaFuncaoCorrente(Pstatements statement){
	
	if(funcoes == NULL)
		return;
		
	Pfuncoes f = NULL;
		
	for(f = funcoes; f->proximaFuncao != NULL; f = f->proximaFuncao)
		;
	
	
	if(f->ultimoStatement == NULL){
		f->statements = statement;
		f->ultimoStatement = statement;
	}else{
	
		Pstatements s = f->ultimoStatement;
		
		string stat = s->statement;
		
		int len = strlen(stat);
		
		
		if(stat[len - 1] == '\n'){
			// não terminou o statement
			f->ultimoStatement = statement;
			s->proximoStatement = statement;
			
			return TRUE;
		}
		
		// acrescenta no final
		s->statement = (string) malloc((strlen(stat) + strlen(statement->statement) + 1) * sizeof(char));
		sprintf(s->statement, "%s%s", stat, statement->statement);
		
		// o libera da memória
		free(statement);
		
		return FALSE;
		
	}
	
}


/**
  * Do statement corrente da função corrente, verifica se é uma atribuição.
  *
  * Retorna NULL se não for uma atribuição
  * Retorna <NEW STATEMENT> caso deva ser um novo statement
  */
string getVariavelDaAtribuicao(){
	
	if(funcoes == NULL)
		return NULL;
		
	Pfuncoes f = NULL;
		
	for(f = funcoes; f->proximaFuncao != NULL; f = f->proximaFuncao)
		;
	
	
	if(f->ultimoStatement == NULL)
		return NULL;
	
	Pstatements s = f->ultimoStatement;
		
	int len = strlen(s->statement);	
		
	//string stat = s->statement;
	string stat;
	
	stat = (string) malloc(len * sizeof(char));
	
	strcpy(stat, s->statement);
	
	// remove os espaços
	replaceSubstring(stat, " ", "");
	
	if(stat[len - 1] == '\n')
		// significa que um novo statement deve ser declarado
		return "<NEW STATEMENT>";
	
	stat = s->statement;	
		
	len = strlen(stat);	
		
	int k;	
	
	string var;
	
	int ident = 0; // possível identação
	
	bool inicioVazio = TRUE;
		
	for(k = 0; k < len; k++){
		
		if(stat[k] == ' ' && inicioVazio){
			ident++;
			continue;
		}else
			inicioVazio = FALSE;
			
		
		if(k < len - 1 && stat[k] == ':' && stat[k + 1] == '=')
			break;
		
		var = (string) malloc((k + 2) * sizeof(char));
		
		strncpy (var, stat, k + 1);
		
		//sprintf(var, "%s%s", stat, statement->statement);
		
	}
	

	if(strcmp(var, stat) == 0){
		free(var);
		return NULL;
	}
	
	if(ident > 0){
		// remove a identação
		len = strlen(var);
		
		for(k = 0; k < len - ident; k++)
			var[k] = var[k + ident];
			
		for(k = len - ident; k < len; k++)
			var[k] = '\0';
		
	}
	
	replaceSubstring(var, " ", "");
	
	return var;
}




/**
  * Do statement corrente da função corrente, verifica se é uma função que foi ativada.
  *
  * Retorna NULL se não for uma ativação
  * Retorna <NEW STATEMENT> caso deva ser um novo statement
  */
string getFuncaoDeAtivacao(int *posArg){
	if(funcoes == NULL)
		return NULL;
		
	Pfuncoes f = NULL;
		
	for(f = funcoes; f->proximaFuncao != NULL; f = f->proximaFuncao)
		;
	
	
	if(f->ultimoStatement == NULL)
		return NULL;
	
	Pstatements s = f->ultimoStatement;
		
	int len = strlen(s->statement);	
		
	//string stat = s->statement;
	string stat;
	
	stat = (string) malloc(len * sizeof(char));
	
	strcpy(stat, s->statement);
	
	// remove os espaços
	replaceSubstring(stat, " ", "");
		
	
	
	if(stat[len - 1] == '\n')
		// significa que um novo statement deve ser declarado
		return "<NEW STATEMENT>";
	
	
	stat = s->statement;
		
	len = strlen(stat);		
		
	int k, j;	
	
	*posArg = 1;
	
	for(k = len - 1; stat[k] != '(' && k > -1; k--){
		
		if(stat[k] == ',')
			*posArg = *posArg + 1;
		
		if(stat[k] == ')'){ // ativação de função dentro de outra ativação ?
			// vai voltando até achar '('
			int contA = 0;
			int contF = 1;
			
			for(k = k - 1; contF != contA && k > 0; k--){
				if(stat[k] == ')')
					contF++;
				else if(stat[k] == '(')
					contA++;
			}			
		}
		
	}	
	
	// a expressão pode começar com um parêntesis
	if(k <= 0)
		return NULL;
	
	// k : achou o limite superior!
	
	
	bool ehUmOperador(char c){
		if(stat[j] == '+' || stat[j] == '-' || stat[j] == '*' || 
		   stat[j] == '=' || stat[j] == '>' || stat[j] == '<' || 
		   stat[j] == ']' || stat[j] == '[' || stat[j] == ')' ||
		   stat[j] == '(' || stat[j] == ',' || stat[j] == ' ')
			return TRUE;
		return FALSE;
	}
	
	
	// procura o limite superior do nome da função
	for(j = k - 1; j > -1; j--){

		if(ehUmOperador(stat[j]))
			break;
			
		if(j == k - 1 && j >= 3 && 
		   (stat[j] == 'v' || stat[j] == 'V') && (stat[j - 1] == 'i' || stat[j - 1] == 'I') &&
		   (stat[j - 2] == 'd' || stat[j - 2] == 'D') && ehUmOperador(stat[j - 3]))
				break;

		
	}
	
	if(j == k - 1)
		return NULL;
	
	// j : achou o limite inferior!
	
	string fun;
	
	j++;
	
	fun = (string) malloc((k - j + 1) * sizeof(char));

	memset(fun, 0, k - j + 1);
	
	
	int w;
	
	
	for(w = j; w < k; w++)
		fun[w - j] = stat[w];
	
	
	return fun;
}





/**
  * Remove tudo a partir de '[' da variável
  */
bool removeAPartirDeAbreColchete(string str){
	
	int len = strlen(str);
	
	string s = str;
	
	int k;
	
	for(k = 0; s[k] != '[' && k < len; k++){
		
		str = (string) malloc((k + 2) * sizeof(char));
		
		strncpy (str, s, k + 1);
		
	}
	
	if(k < len)
		return TRUE;
		
	return FALSE;
}







// UTIL


/**
  * Imprime o texto no arquivo de saída
*/
void print(string text){
	fprintf(arqsaida, "%s", text);
}

/**
  * Retorna o total de casas decimais do número
  */
int getTotalCasasDecimais(int num){
	
	int cont = 1;
	
	while(num / 10 > 1){
		cont++;
		num = num / 10;
	}
	
	return cont;
}

/**
  * Converte a cadeia para letras minúsculas
  */
string toLowerCase(string str){
	
	int i = 0;
	
	string s;
	
	s = (string) malloc(strlen(str) * sizeof(char));
	
	while (str[i]){
		s[i] = tolower(str[i]);
		i++;
	}
	
	return s;
}



// pascal é case insensitive ! LEMBRAR DE FAZER AS MUDANÇAS NOS NOMES!!
bool compareInsensitiveStrings(string str1, string str2){
	
	if(strcmp(toLowerCase(str1), toLowerCase(str2)) == 0)
		return TRUE;
	
	return FALSE;
	
}

/**
  * Substitue as ocorrências de sub em str por new
  */
void replaceSubstring(string str, string sub, string new){
	int stringLen, subLen, newLen;
	int i = 0,j,k;
	int flag = 0, start, end;
	
	stringLen = strlen(str);
	subLen = strlen(sub);
	newLen = strlen(new);

	for(i = 0; i < stringLen; i++){
	
		flag = 0;
		
		start = i;
		
		/* Checks for the substring */
		for(j = 0; str[i] == sub[j]; j++, i++) 
			if(j == subLen - 1)
				flag = 1; /* flag sets when substring is identified */
		
		end = i;
		
		if(flag == 0)
			i -= j;
		else{
			/* Delete the substring */
			for(j = start; j < end; j++){ 
				for(k = start; k < stringLen; k++)
					str[k] = str[k + 1];
				stringLen--;
				i--;
			}
			
			/* Inserting new substring */
			for(j = start; j < start + newLen; j++){    
				for(k = stringLen; k >= j; k--)
					str[k+1] = str[k];
					
				str[j] = new[j - start];
				stringLen++;
				i++;
			}
		}
	}
}





/**
  * A partir do tipo especificador, retorna o nome equivalente na linguagem pascal
  */
string traduzTipo(Ttipoespecificador tipo){
	
	if(tipo == Tint)
		return "integer";
		
	if(tipo == Tstring)
		return "string";
	
	return "";
}


/**
  * A partir do operador relacional, retorna o nome equivalente na linguagem pascal
  */
string traduzRelacional(Trelacional rel){
	
	if(rel == Tmenorigual)
		return " <= ";
		
	if(rel == Tmenor)
		return " < ";
		
	if(rel == Tmaior)
		return " > ";
		
	if(rel == Tmaiorigual)
		return " >= ";
	
	if(rel == Tigual)
		return " = ";
	
	if(rel == Tdiferente)
		return " <> ";
	
	return "";
}


/**
  * A partir do operador de soma/subtração, retorna o nome equivalente na linguagem pascal
  */
string traduzSoma(Tsoma soma){
	
	if(soma == Tmais)
		return " + ";
		
	if(soma == Tmenos)
		return " - ";
	
	return "";
}


/**
  * A partir do operador de soma/subtração, retorna o nome equivalente na linguagem pascal
  */
string traduzMult(Tmult mult){
	
	if(mult == Tmul)
		return " * ";
		
	if(mult == Tdiv)
		return " div ";
	
	return "";
	
}


/**
  * A partir do conteúdo string em C, traduz para o conteúdo string equivalente na linguagem pascal
  */
string traduzString(string str){

	string s;
	
	s = (string) malloc((strlen(str) + 3) * sizeof(char));
	
	memset(s, 0, strlen(str) + 3);
	
	sprintf(s, "\'%s\'", str);
		
	// remove os caracteres especiais..
	// o caracter " continua
	replaceSubstring(s, "\\n", "");
	replaceSubstring(s, "\\t", "");
	replaceSubstring(s, "\\", "");
	
	return s;
}




/**
  * A partir do nome da função, traduz para um nome que seja válido em pascal
  * e trate do case insensitive e que não pode ser igual ao nome de uma variável
  */
string traduzNomeDaFuncao(string funcao){
	
	// essas três funções (tudo em minúsculo) são casos especiais
	if(strcmp(funcao, "main") == 0 || strcmp(funcao, "input") == 0 || strcmp(funcao, "output") == 0)
		return funcao;
	
	string nome;
	
	nome = (string) malloc((strlen(funcao) + 1) * sizeof(char));
	// coloca um underscore no final
	sprintf(nome, "%s_", funcao);
	
	int len = strlen(nome);
	
	
	
	string resultado;	
	
	resultado = (string) malloc(len * sizeof(char));
	
	memset(resultado, 0, len);
	
	
	
	int contCapital = 0;
	
	int k, j;
	
	for(k = 0, j = 0; k < len; k++, j++){
		
		resultado[j] = nome[k];
		
		// procura por uma letra maiúscula
		if(nome[k] >= 65 && nome[k] <= 90){
			contCapital++;
			j++;
			// acrescenta um underscore após ela
			resultado = (string) realloc(resultado, (len + contCapital + 1) * sizeof(char));
			resultado[j] = '_';
		}
		
	}
	
	resultado[len + contCapital] = '\0';
	
	return resultado;

}


/**
  * A partir do nome da variável, traduz para um nome que seja válido em pascal
  * e trate do case insensitive e que não pode ser igual ao nome de uma função
  */
string traduzNomeDaVariavel(string variavel){
	
	string nome;
	
	nome = (string) malloc((strlen(variavel) + 1) * sizeof(char));
	// no um underscore no início
	sprintf(nome, "_%s", variavel);
	
	int len = strlen(nome);
	
	
	
	string resultado;	
	
	resultado = (string) malloc(len * sizeof(char));
	
	memset(resultado, 0, len);
	
	
	
	int contCapital = 0;
	
	int k, j;
	
	for(k = 0, j = 0; k < len; k++, j++){
		
		// procura por uma letra maiúscula
		if(nome[k] >= 65 && nome[k] <= 90){
			contCapital++;
			// acrescenta um underscore antes dela
			resultado = (string) realloc(resultado, (len + contCapital) * sizeof(char));
			resultado[j] = '_';
			j++;
		}
		
		resultado[j] = nome[k];
		
	}
	
	resultado[len + contCapital] = '\0';
	
	return resultado;
	
}










/**
  * Inicializa os objetos
  */
void inicializaEstruturaDaGeracao(){
	variaveisGlobais = NULL;  
	funcoes = NULL;
}


void destroiVariaveis(Pvariaveis variaveis){
	
	while(variaveis != NULL){
		Pvariaveis v = variaveis;
		
		variaveis = variaveis->proximaVariavel;	

		free(v);
		
	}
}


/**
  * Tira todas as estruturas da memória
  */
void destroiGeracaoDeCodigo(){
	
	if(nomeDoPrograma != NULL)
		free(nomeDoPrograma);
		
	
	// variáveis globais
	destroiVariaveis(variaveisGlobais);
	
	// funções
	while(funcoes != NULL){
		Pfuncoes f = funcoes;
		
		destroiVariaveis(funcoes->argumentos);
		
		destroiVariaveis(funcoes->variaveis);
		
		while(funcoes->statements != NULL){
			Pstatements s = funcoes->statements;
			
			funcoes->statements = funcoes->statements->proximoStatement;
			
			free(s);
		}
		
		funcoes = funcoes->proximaFuncao;
		
		free(f);
		
	}
	
}






/** 
  * Gera o arquivo com o código em pascal 
  */
void geraCodigo(string nomeDoArquivo){
	
	nomeDoPrograma = (string) malloc((strlen(nomeDoArquivo) + 1) * sizeof(char));
	
	sprintf(nomeDoPrograma, "%s\0", nomeDoArquivo);
	
	
	
	// pega o nome do arquivo + extensão
	string nome;

	nome = (string) malloc((strlen(nomeDoArquivo) + 5) * sizeof(char));
	
	sprintf(nome, "%s.pas\0", nomeDoArquivo);


	// Cria o arquivo
	arqsaida = fopen(nome, "w");

	if(arqsaida == NULL){
		printf("\nFalha ao escrever o arquivo de saida.\n");
		destroiGeracaoDeCodigo();
		return;
	}

	escreveArquivo();

	// fecha o arquivo
	fclose(arqsaida);
	
	
	// remover tudo das estruturas da memória
	destroiGeracaoDeCodigo();
	
}


/**
  * Escreve o arquivo de saída
  */
void escreveArquivo(){

	print("program ");
	print(nomeDoPrograma);
	print(" ;\n\n");
	print("uses crt;\n\n");
	
	escreveVariaveisGlobais();
	
	escreveFuncoes();

	printf("\nArquivo  '%s.pas'  com o codigo gerado foi criado com sucesso.\n\n", nomeDoPrograma);
	
}





/**
  * Escreve as variáveis no arquivo
  */
void escreveVariaveis(Pvariaveis variavel){
	
	if(variavel == NULL)
		return;
	
	Pvariaveis v = variavel;
	
	print("var\n");
	
	while(v != NULL){
	
		print("    "); // identado em 4 espaços
		
		print(v->identificador);
		
		if(v->tipo == GFtiposimples)
			print(" : ");
		else{
			print(" : array[1..");
			
			string numero;
			numero = (string) malloc(getTotalCasasDecimais(v->num) * sizeof(char));
			sprintf(numero, "%d", v->num);
			
			print(numero);
			print("] of ");
		}
	
		
		print(traduzTipo(v->tipoesp));
		
		v = v->proximaVariavel;
		
		print(";\n");
		
	}
	
}




/**
  * Escreve no arquivo as variáveis globais
  */
void escreveVariaveisGlobais(){
	
	escreveVariaveis(variaveisGlobais);
	
	print("\n\n");
}




/**
  * Escreve os argumentos da função corrente
  */
void escreveArgumentos(Pvariaveis argumentos){
	
	if(argumentos == NULL)
		return;
	
	Pvariaveis a = argumentos;
	
	while(a != NULL){
		
		if(a->tipo == GFtiposimples){
			print(a->identificador);
			print(" : ");
		}else{
		    // todas as listas são passadas por referência
			print("var ");
			print(a->identificador);
			print(" : array of ");
		}
		
		print(traduzTipo(a->tipoesp));
			
		a = a->proximaVariavel;
			
		if(a != NULL)
			print("; ");
		
	}
	
}



/**
  * Escreve no arquivo os statements 
  */
void escreveStatements(Pstatements statements){
	
	if(statements == NULL)
		return;
	
	Pstatements s = statements;
	
	for(s = statements; s != NULL; s = s->proximoStatement){

		print(s->statement);
		
	}
	
}



/**
  * Escreve no arquivo as funções
  */
void escreveFuncoes(){

	if(funcoes == NULL)
		return;
	
	Pfuncoes f = NULL;
	
	for(f = funcoes; f != NULL; f = f->proximaFuncao){
		
		// function or procedure
		if(strcmp(f->identificador, "main") != 0){
		
			if(f->tipo == Tvoid)
				print("procedure ");
			else
				print("function ");
			
			print(f->identificador);
			
			if(f->argumentos != NULL){
				print("(");
				escreveArgumentos(f->argumentos);
				print(")");
			}
			
			if(f->tipo != Tvoid){
				print(" : ");
				print(traduzTipo(f->tipo));
			}
			
			print(";\n");
			
			escreveVariaveis(f->variaveis);
			
		}
		
		print("begin\n");
		
		// statements . . .
		escreveStatements(f->statements);
		
		if(strcmp(f->identificador, "main") == 0)
			print("\nend.");
		else
			print("\nend;\n\n\n");
	}

}


/*
int main(int argc, char* argv[]){

	// testando estrutura

	inicializaEstruturaDaGeracao();
	
	Ptipos tipoInt = getTipo(10, Tint);
	
	addVariavelGlobal(pascal_variavel_simples("global", Tstring));
    addVariavelGlobal(pascal_variavel_simples("a", Tint));
	addVariavelGlobal(pascal_variavel_simples("b", Tint));
    addVariavelGlobal(pascal_variavel_lista("p", getTipo(10, Tint)->identificador));
	addVariavelGlobal(pascal_variavel_lista("w", getTipo(10, Tint)->identificador));
	addVariavelGlobal(pascal_variavel_simples("j", Tint));

	// função  somaTodosElementosDosVetores
	addFuncao(pascal_funcao("somaTodosElementosDosVetores", Tint));
	
	addParametroNaFuncaoCorrente(pascal_variavel_lista("m", getTipo(10, Tint)->identificador));
	addParametroNaFuncaoCorrente(pascal_variavel_lista("n", getTipo(10, Tint)->identificador));
	
	addVariavelNaFuncaoCorrente(pascal_variavel_lista("r", getTipo(10, Tint)->identificador));
	addVariavelNaFuncaoCorrente(pascal_variavel_simples("i", Tint));
	addVariavelNaFuncaoCorrente(pascal_variavel_simples("resultado", Tint));
	
	// statements
	
	
	// função  subtracaoEmModulo
	addFuncao(pascal_funcao("subtracaoEmModulo", Tint));
	
	addParametroNaFuncaoCorrente(pascal_variavel_simples("a", Tint));
	addParametroNaFuncaoCorrente(pascal_variavel_simples("b", Tint));
	
	addStatementNaFuncaoCorrente(pascal_statement("    if("));
	addStatementNaFuncaoCorrente(pascal_statement("a"));
	addStatementNaFuncaoCorrente(pascal_statement(">"));
	addStatementNaFuncaoCorrente(pascal_statement("b"));
	addStatementNaFuncaoCorrente(pascal_statement(") then begin\n    "));
	addStatementNaFuncaoCorrente(pascal_statement("subtracaoEmModulo := "));
	addStatementNaFuncaoCorrente(pascal_statement("a"));
	addStatementNaFuncaoCorrente(pascal_statement(" - "));
	addStatementNaFuncaoCorrente(pascal_statement("b"));
	addStatementNaFuncaoCorrente(pascal_statement(";\n    exit;\n    "));
	addStatementNaFuncaoCorrente(pascal_statement("end;\n    "));
	addStatementNaFuncaoCorrente(pascal_statement("subtracaoEmModulo := "));
	addStatementNaFuncaoCorrente(pascal_statement("b"));
	addStatementNaFuncaoCorrente(pascal_statement(" - "));
	addStatementNaFuncaoCorrente(pascal_statement("a"));
	addStatementNaFuncaoCorrente(pascal_statement(";\n    exit;\n   "));
	
	
	// função  conversorADTresBits
	addFuncao(pascal_funcao("conversorADTresBits", Tint));
	
	addParametroNaFuncaoCorrente(pascal_variavel_simples("n", Tint));
	
	// statements

	
	// função  main
	addFuncao(pascal_funcao("main", Tvoid));

	// statements
	
	
	geraCodigo("testando");
	
}
*/
