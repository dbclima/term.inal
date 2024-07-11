# Programação de Computadores II

## Descrição
O projeto `term.inal` foi é um projeto por estudantes da **UFRJ** da disciplina Programação de Computadores II 24.1

O projeto foi inspirado no jogo [term.ooo](https://term.ooo/) adaptado ao terminal.

## Alunos
- Antônio Pedro Corrêa Rodrigues
    - DRE: 123675045
- Diogo Bernardo Corrêa Lima
    - DRE: 123706511
- João Victor Fittipaldi Binda Magno
    - DRE: 123711443
- Sylvio Jorge Pastene Helt
    - DRE: 123675265

## Regras do Jogo
O jogador deve adivinhar uma palavra de cinco letras sorteada aleatoreamente dentre uma série de palavras em um banco. Antes do jogo começar, é possível adicionar novas palavras ao banco por meio da flag -add quando o programa é executado.

O usuário deve escolher um número de tentativas entre 3 e 20, que estabelecerá a dificuldade do jogo. Em cada tentativa, caso uma letra esteja presente na palavra correta e na posição correta, sua cor muda para verde. Caso a letra esteja na palavra correta, mas numa posição incorreta, sua cor muda para amarelo. Caso não esteja presente na palavra, sua cor muda para vermelho no teclado com as letras já testadas.

O jogo acaba quando o usuário chega ao número máximo de tentativas e não acerta, perdendo o jogo ou quando o usuário acerta. Após isso, é possível jogar novamente.


## Pseudo Código:
O código pode sem compreendido através das seguintes simplificações:

### main
~~~c
// Struct que armazena os atributos de letra (caractere e cor)
// Alem de apontar pra proxima letra
typedef struct aux {
    ...
} Letra;

// Struct que apenas aponta para a primeira letra
typedef struct {
    ...
} Palavra;

int main(argumentos_do_programa) {

    // Tratamento dos parametros passados por linha de comando para o jogo
    tratar_argumentos();

    // Captura da dificuldade do jogo
    capturar_dificuldade();

    // Inicializacao da struct que armazenara o teclado
    iniciar_teclado();

    // Loop onde o jogo ocorre
    while (continuar) {
        // Sorteio da palavra chave de um arquivo que contem o banco de palavras
        sortear_palavra_chave_do_arquivo();
        
        // Funcao que recebera a palavra chave e inicia o jogo com base na mesma
        // Alem disso, verifica se o usuario quer jogar novamente  
        continuar = loop_jogo();
    }

    // Rotina executada ao finalizarmos o jogo
    rotina_fim_de_jogo();

    return 0;
}
~~~

### loop jogo
~~~c
loop_jogo() {
    while(tentativa_atual < numero_tentativas) {
        // Limpamos a tela do conteudo atual
        limpar_tela();

        // Printamos as palavras atuais do jogo
        printar_palavras();

        // Printamos o teclado
        printar_teclado();

        // Printamos qualquer aviso resultante da ultima jogada
        printar_warning();

        // Recebemos e tratamos o input do usuario
        receber_input_usuario();
        
        // Caso o jogo acabe em vitoria
        if (jogo_ganho) {
            // Exibimos a rotina de vitoria
            rotina_vitoria();

            // Perguntamos quanto a jogar novamente
            return jogar_novamente();
        }
    }
    
    // Caso o while encerre, printamos a rotina de derrota
    rotina_derrota();

    // Perguntamos quanto a jogar novamente
    return jogar_novamente();
}
~~~
