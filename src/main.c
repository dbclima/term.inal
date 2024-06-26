#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "types.h"
#include "palavra.h"

/*
 * Pessoa 1: Joao Binda
 * Pessoa 2: Antonio Predo
 * Pessoa 3: Sylvio
 * Pessoa 4: Diogo
 */

int main(int argc, char **argv) {
    // Tratar argumentos do programa
    // Pessoa 1

    Bool continuar_jogo = TRUE;
    int numero_tentativas = capturar_dificuldade();
    Palavra *p_palavras = (Palavra*) malloc(sizeof(Palavra) * numero_tentativas);
    Letra teclado[26];

    char palavra_chave[6];

    // Pessoa 2
    if (iniciar_teclado(&teclado) != OK) {
        
    }

    while (continuar_jogo) {
        sortear_palavra(&palavra_chave); // Pessoa 1
        continuar_jogo = loop_jogo(p_palavras, numero_tentativas, palavra_chave, &teclado);
    }
    
    system("clear");
    printf("%s\n", BG_AMARELO("Teste"));
    getchar();

    return 0;
}

Bool loop_jogo(Palavra *p_palavras, int numero_tentativas, char *palavra_chave, Letra *teclado) {
    Bool retorno;
    int warning;
    int tentativa_atual = 0;
    char buffer_warning[200] = "";

    while(tentativa_atual < numero_tentativas) {
        tentativa_atual++;
        system("clear");
        
        // Pessoa 4
        for (int i = 0; i < tentativa_atual; i++) {
            printar_palavra(p_palavras[i]);
        }

        // Pessoa 4
        printar_teclado(teclado);
        printar_warning(buffer_warning);

        // Pessoa 3
        warning = receber_input_usuario();
        if (warning) {
                if (warning % PALAVRA_REPETIDA) {
                    concatenar(buffer_warning, "Repetiu palavra\n");
                }
                if (warning % NUMERO_LETRAS_INVALIDO) {
                    concatenar(buffer_warning, "foi detectada o numero de letras invalido\n");
                }
                if (warning % CARACTERE_INVALIDO) {
                    concatenar(buffer_warning, "Foi detectado um caractere invalido\n");
                }
            }
        }

        // Pessoa 2
        if (processar_nova_palavra(teclado)) {
            // Pessoa 4
            rotina_vitoria();
            return jogar_novamente();
        }
    
    // Pessoa 4
    rotina_derrota();
    return jogar_novamente();
}