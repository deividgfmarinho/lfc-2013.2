/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ELSE = 258,
     IF = 259,
     INT = 260,
     STR = 261,
     RETURN = 262,
     VOID = 263,
     WHILE = 264,
     MAIS = 265,
     MENOS = 266,
     ASTERISCO = 267,
     BARRA = 268,
     MENOR = 269,
     MENORIGUAL = 270,
     MAIOR = 271,
     MAIORIGUAL = 272,
     IGUAL = 273,
     DIFERENTE = 274,
     ATRIBUICAO = 275,
     PONTOEVIRGULA = 276,
     VIRGULA = 277,
     ABREPARENTESIS = 278,
     FECHAPARENTESIS = 279,
     ABRECOLCHETE = 280,
     FECHACOLCHETE = 281,
     ABRECHAVES = 282,
     FECHACHAVES = 283,
     NUM = 284,
     STRSTR = 285,
     ID = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 24 "sintatico.y"

	int inteiro; 
	char* string;
	Tprograma programa;
	Tdeclaracaolista declaracaolista;
	Tdeclaracao declaracao; 
	Tvardeclaracao vardeclaracao;
	Ttipoespecificador tipoespecificador;
	Tfundeclaracao fundeclaracao;
	Tparams params;
	Tparamlista paramlista;
	Tparam param;
	Tcompostodecl compostodecl;
	Tlocaldeclaracoes localdeclaracoes;
	Tstatementlista statementlista;
	Tstatement statement;
	Texpressaodecl expressaodecl;
	Tselecaodecl selecaodecl;
	Titeracaodecl iteracaodecl;
	Tretornodecl retornodecl;
	Texpressao expressao;
	Tvar var; 
	Tsimplesexpressao simplesexpressao; 
	Trelacional relacional;
	Tsomaexpressao somaexpressao;
	Tsoma soma;
	Ttermo termo;
	Tmult mult;
	Tfator fator;
	Tativacao ativacao;
	Targs args;
	Targlista arglista;



/* Line 2068 of yacc.c  */
#line 117 "sintatico.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


