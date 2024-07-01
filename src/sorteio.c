#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "types.h"
#include "sorteio.h"

Status sortear_palavra(char* palavra_chave){
    int tam, pos;
    FILE* f;
    Status status = OK;

    f = fopen(ARQUIVO_PALAVRAS, "r");
    if(f == NULL){
        status = ERRO_ABERTURA_ARQUIVO;
        return status;
    }

    tam = fseek(f, 0, SEEK_END);
    tam = tam/(sizeof(char)*6);
    if(tam == 0){
        status = ERRO_ARQUIVO_VAZIO;
        printf("Nao existem palavras dentro do arquivo");
        return status;
    }
    pos = rand()%tam;
    pos = pos*(sizeof(char)*6);

    fseek(f, pos, SEEK_SET);
    fscanf(f, "%s", palavra_chave);

    fclose(f);

    return status;
}

Status inserirpalavra(char* palavra){
    Status status = OK;

    if(strlen(palavra) == 6){
        status = ERRO_TAMANHO_PALAVRA;
        return status;
    }
    for(int i = 0; i < 5; i++){
        if((palavra[i] < 65) || ((palavra[i] > 90) && (palavra[i] < 97)) || (palavra[i] > 123)){
            status = ERRO_CARACTER_INVALIDO;
            return status;
        }
    }

    FILE* f;
    int tam, aux;
    char compara[6];
    f = fopen(ARQUIVO_PALAVRAS, "r");
    if(f == NULL){
        status = ERRO_ABERTURA_ARQUIVO;
        return status;
    }

    tam = fseek(f, 0, SEEK_END);
    tam = tam/(sizeof(char)*6);
    rewind(f);
    if(tam == 0){
        puts("entrou aqui");
        //fwrite(palavra, sizeof(char), 5, f);
        //fwrite("\n", sizeof(char), 1, f);
        fprintf(f, "%s", palavra);
        
    }
    for(int i = 0; i < tam; i++){
        fscanf(f, "%s", compara);
        aux = strcmp(palavra, compara);
        if(aux == 0){
            status = ERRO_PALAVRA_REPETIDA;
            fclose(f);
            return status;
        }
        else if(aux > 0){
            fseek(f, -(sizeof(char)*6), SEEK_CUR);
            fwrite(palavra, sizeof(char), 5, f);
            fwrite("\n", sizeof(char), 1, f);
        }
        else continue;
    }

    fclose(f);
    return status;
}