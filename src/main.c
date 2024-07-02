#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "types.h"
#include "palavra.h"
#include "interface.h"

/*
 * Pessoa 1: Joao Binda
 * Pessoa 2: Antonio Predo
 * Pessoa 3: Sylvio
 * Pessoa 4: Diogo
 */

Bool loop_jogo(Palavra *p_palavras, int numero_tentativas, char *palavra_chave, Palavra *p_teclado);

int main(int argc, char **argv) {
    // Tratar argumentos do programa
    // Pessoa 1

    Bool continuar_jogo = TRUE;
    //int numero_tentativas = capturar_dificuldade();
    int numero_tentativas = 5;
    Palavra *p_palavras = (Palavra *)malloc(sizeof(Palavra) * numero_tentativas);
    Palavra *p_teclado = (Palavra *)malloc(sizeof(Palavra) * 3);

    char palavra_chave[6] = "teste";

    // Pessoa 2
    if (iniciar_teclado(p_teclado) != OK) {
        
    }

    while (continuar_jogo) {
        //sortear_palavra(palavra_chave); // Pessoa 1
        continuar_jogo = loop_jogo(p_palavras, numero_tentativas, palavra_chave, p_teclado);
    }

    //rotina_fim_de_jogo();

    return 0;
}

Bool loop_jogo(Palavra *p_palavras, int numero_tentativas, char *palavra_chave, Palavra *p_teclado) {
    Bool retorno = TRUE;
    int tentativa_atual = 0;
    char buffer_warning[200] = "";
    char tentativa[200] = "";

    while(tentativa_atual < numero_tentativas) {
        system("clear");
        
        // Pessoa 4 - Feito
        for (int i = 0; i < tentativa_atual; i++) {
            printar_palavra(&p_palavras[i], OFFSET_PALAVRAS, FALSE);
        }

        // Pessoa 4 - Feito
        printar_teclado(p_teclado, OFFSET_TECLADO);
        printar_warning(buffer_warning);

        // Pessoa 3
        if(receber_input_usuario(tentativa, buffer_warning) != 0){
            continue;
        }


        
        // Pessoa 2
        if (processar_nova_palavra(p_teclado, palavra_chave,tentativa, p_palavras,tentativa_atual)) {
            
            // Pessoa 4 - Feito
            rotina_vitoria();
            return jogar_novamente();
        }
    tentativa_atual++;
    
    // Pessoa 4 - Feito
    rotina_derrota();
    return jogar_novamente();
    }

    return retorno;

    };