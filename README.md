lfc-2013.2
==========

Repositório para inclusão dos trabalhos referente à disciplina de Linguagens Formais e Compiladores da UFS (2013/2)



------------------------------------------------------------------------------------------------------------------------

COMPILAR E GERAR O EXECUTÁVEL DO COMPILADOR PARA C-




Há duas maneiras de fazer:



1) Executar o shell script  'makecompiler.sh'

        ./makecompiler.sh




2) Compilar manualmente


        bison -v -d -o sintatico.c sintatico.y
        
        
        flex -v -t lex.l > lex.c
        
        
        gcc sintatico.c lex.c -o compilador

------------------------------------------------------------------------------------------------------------------------

USO DO COMPILADOR PARA C-




Para usar o compilador, crie um arquivo fonte de extensão .c, e coloque-o como entrada do compilador.


Por exemplo:



Arquivo 'teste.c'


      void main(void){
        int a;
        a = 10;
        output(a);
      }





No shell:

      ./compilador <teste.c


------------------------------------------------------------------------------------------------------------------------

POSSÍVEIS SAÍDAS NA TELA
                        
1) Se o programa fonte, usado como entrada, não contiver erros, uma mensagem será exibida informando que um um arquivo 
novo foi criado. Este arquivo contém a tradução do código C- (informado na entrada) em Pascal.


2) O anúncio de algum erro. O erro pode ser léxico, sintático ou semântico. Observações:
  - O primeiro erro encontrado é anunciado e o processo de análise é encerrado
  - Nenhuma destas mensagens informa qual linha do arquivo ocorreu o erro
  - Não é informado qual o tipo de erro sintático que ocorreu
  - A causa do erro léxico ou semântico é explícita
  
  
