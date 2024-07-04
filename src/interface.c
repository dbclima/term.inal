#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "config.h"

#include "interface.h"

int capturar_dificuldade(){
    int num_tentativas = -1;
    while(num_tentativas < 3 || num_tentativas > 20){
        printf("Digite o numero de tentativas (entre 3 e 20): ");
        scanf("%d", &num_tentativas);
        
        if(num_tentativas < 3 || num_tentativas > 20){
            printf("Tentativa invalida!\n");
        }

        // Verifica por caracteres apos o numero 
        while (getchar() != '\n'){
            continue;
        }
    }
    return num_tentativas;
}

void printar_warning(char *p_buffer_warning) {
    printf("\n%s%s%s\n", BG_NONE_FG_VERMELHO, p_buffer_warning, BG_NONE_FG_NONE);
    p_buffer_warning[0] = '\0';
}


int receber_input_usuario(char *tentativa, char* p_buffer_warning) {
    int erro = 0;
    printf("Digite uma tentativa de palavra: ");
    fscanf(stdin, "%[^\n]", tentativa);
    getchar();

    // Detecção de erro de palavra repetida
    if(0 == 1){
        strcat(p_buffer_warning, "Erro: Palavra tentada anteriormente.\n");
        erro++;
    }
    
    // Detecção de erro de tamanho
    if(strlen(tentativa) != 5){
        strcat(p_buffer_warning, "Erro: A palavra deve conter cinco caracteres.\n");
        erro++;
    }

    // Detecção de erro de caractere inváldio
    for(int i = 0; i < strlen(tentativa); i++){
        if(!((tentativa[i] >= 'a' && tentativa[i] <= 'z') || (tentativa[i] >= 'A' && tentativa[i] <= 'Z'))){
            strcat(p_buffer_warning, "Erro: A palavra deve conter apenas letras.\n");
            erro++;
            break;
        }
    }

    return erro;
}

void rotina_vitoria() {
    system("clear");
    printf("\n\n\n%sVitoria!\n\n\n\n", OFFSET_PALAVRAS);
}

void rotina_derrota() {
    system("clear");
    printf("\n\n\n%sDerrota!\n\n\n\n", OFFSET_PALAVRAS);
}

Bool jogar_novamente() {
    Bool retorno;
    printf("Deseja jogar novamente? [s/n]: ");

    switch(getchar()) {
        case 's':
        case 'S':
            retorno = TRUE;
            break;
        case 'n':
        case 'N':
        default:
            retorno = FALSE;
            break;
    }
    getchar();

    return retorno;
}