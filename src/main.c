#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "types.h"
#include "palavra.h"
#include "interface.h"

/*
 * Pessoa 1: Joo Binda - feito
 * Pessoa 2: Antonio Predo Corra
 * Pessoa 3: Sylvio
 * Pessoa 4: Diogo Corra Lima - feito
 */

int main(int argc, char **argv) {
    // Tratar argumentos do programa
    // Pessoa 1 - feito
    Status status = OK;
    if(argc > 1){
        if(!strcmp(argv[1], "--add")){
            for(int i = 2; i < argc; i++){
                status = inserirpalavra(argv[i]);
                if(status != OK){
                    switch(status){
                        case ERRO_ABERTURA_ARQUIVO:
                            printf("Erro de abertura de arquivo. \n");
                            exit(ERRO_ABERTURA_ARQUIVO);
                        case ERRO_TAMANHO_PALAVRA:
                            printf("Erro de tamanho de palavra. \n Digite palavras de somente 5 letras. \n");
                            break;
                        case ERRO_CARACTER_INVALIDO:
                            printf("Erro de caracter invalido. \n Nao digite caracteres especiais. \n");
                            break;
                        case ERRO_PALAVRA_REPETIDA:
                            printf("Erro de palavra repetida. \n");
                            break;
                    }
                }
            }
        }
    }

    Bool continuar_jogo = TRUE;
    int numero_tentativas = capturar_dificuldade();
    Palavra *p_palavras = (Palavra*) malloc(sizeof(Palavra) * numero_tentativas);
    Palavra p_teclado;

    char palavra_chave[6];

    // Pessoa 2
    if (iniciar_teclado(&p_teclado) != OK) {
        
    }

    while (continuar_jogo) {
        sortear_palavra(palavra_chave); // Pessoa 1 - feito
        continuar_jogo = loop_jogo(p_palavras, numero_tentativas, palavra_chave, &p_teclado);
    }

    rotina_fim_de_jogo();

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
        
        // Pessoa 4 - Feito
        for (int i = 0; i < tentativa_atual; i++) {
            printar_palavra(&p_palavras[i], OFFSET_PALAVRAS, FALSE);
        }

        // Pessoa 4 - Feito
        printar_teclado(teclado, OFFSET_TECLADO);
        printar_warning(buffer_warning);

        // Pessoa 3
        warning = receber_input_usuario();
        if (warning) {
                if (warning % PALAVRA_REPETIDA == 0) {
                    concatenar(buffer_warning, "Repetiu palavra\n");
                }
                if (warning % NUMERO_LETRAS_INVALIDO == 0) {
                    concatenar(buffer_warning, "foi detectada o numero de letras invalido\n");
                }
                if (warning % CARACTERE_INVALIDO == 0) {
                    concatenar(buffer_warning, "Foi detectado um caractere invalido\n");
                }
            }
        }

        // Pessoa 2
        if (processar_nova_palavra(teclado)) {
            
            // Pessoa 4 - Feito
            rotina_vitoria();
            return jogar_novamente();
        }
    
    // Pessoa 4 - Feito
    rotina_derrota();
    return jogar_novamente();
}