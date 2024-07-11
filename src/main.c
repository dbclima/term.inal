#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "types.h"
#include "palavra.h"
#include "interface.h"
#include "sorteio.h"

Bool loop_jogo(Palavra *p_palavras, int numero_tentativas, char *palavra_chave, Palavra *p_teclado);

int main(int argc, char **argv) {
    
    // Tratar argumentos do programa
    Status status = OK;
    if(argc > 1){
        if(argc <= 2){
            printf("Falta palavras para serem inseridas no arquivo depois da flag");
            return ERRO_CHAMADA_INVALIDA;
        }
        if(strcmp(argv[1], "--add")){
            printf("Flag para adicionar palavras nao foi detectada. Utilize dessa maneira: \n%s --add <palavra que deseja adicionar>", argv[0]);
            return ERRO_CHAMADA_INVALIDA;
        }
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
                    default:
                        printf("\n");
                }
            }
        }
        return status;
    }
    
    // Cria variáveis que armazenam tentativas anteriores e teclado
    Bool continuar_jogo = TRUE;
    int numero_tentativas = capturar_dificuldade(); // Pessoa 3
    Palavra *p_palavras = (Palavra *)malloc(sizeof(Palavra) * numero_tentativas);
    Palavra *p_teclado = (Palavra *)malloc(sizeof(Palavra) * 3);

    char palavra_chave[6];

    iniciar_teclado(p_teclado);

    // Execução do programa a cada rodada
    while (continuar_jogo) {
        sortear_palavra(palavra_chave); 
        continuar_jogo = loop_jogo(p_palavras, numero_tentativas, palavra_chave, p_teclado);
    }

    // Libera a memória alocada durante a execução
    deletar_palavras(p_palavras, numero_tentativas);
    deletar_teclado(p_teclado);
    free(p_palavras);
    free(p_teclado);

    return 0;
}

Bool loop_jogo(Palavra *p_palavras, int numero_tentativas, char *palavra_chave, Palavra *p_teclado) {
    int tentativa_atual = 0;
    char buffer_warning[200] = "";
    char tentativa[200] = "";
    int qtde_erros = 0;
    int flag_endgame = 0;

    deletar_teclado(p_teclado);
    iniciar_teclado(p_teclado);

    while(tentativa_atual < numero_tentativas) {
        system("clear");
        strcpy(tentativa, "");

        // Exibe em tela tentativas anteriores
        for (int i = 0; i < ((flag_endgame == 1 || flag_endgame == -1) ? tentativa_atual + 1 : tentativa_atual) ; i++) {
            printar_palavra(&p_palavras[i], OFFSET_PALAVRAS, FALSE);
        }
        for (int i = tentativa_atual; i < ((flag_endgame == 1 || flag_endgame == -1) ? numero_tentativas - 1 : numero_tentativas); i++) {
            printf("%s_____\n", OFFSET_PALAVRAS);
        }

        // Exibe teclado e warnings anteriores
        printf("\n");
        printar_teclado(p_teclado, OFFSET_TECLADO);
        printar_warning(buffer_warning);

        for (int i = qtde_erros; i < 2; i++) {
            printf("\n");
        }        

        // Rotina caso jogo chegue ao fim
        if (flag_endgame) {
            if (flag_endgame == -1) rotina_derrota(palavra_chave);
            else rotina_vitoria();
            return jogar_novamente();
        }

        // Não incrementa número de tentativas caso haja erros
        if((qtde_erros = receber_input_usuario(tentativa, buffer_warning, p_palavras, tentativa_atual)) != 0){
            continue;
        }

        // Verifica condição de vitória
        if (processar_nova_palavra(p_teclado, palavra_chave,tentativa, p_palavras,tentativa_atual)) {
            flag_endgame = 1;
            continue;
        }
        
        tentativa_atual++;
        
        // Verifica condição de derrota  
        if (tentativa_atual == numero_tentativas) {
            flag_endgame = -1;
            tentativa_atual--;
        }
    
    }
    return FALSE;
}
