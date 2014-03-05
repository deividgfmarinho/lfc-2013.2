
bison -v -d -o sintatico.c sintatico.y


flex -v -t lex.l > lex.c


gcc sintatico.c lex.c -o compilador
