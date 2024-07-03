#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

    srand(time(NULL));
    fseek(f, 0, SEEK_END);
    tam = (int)ftell(f);
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

Status inserirpalavra(char* palavra) {
    Status status = OK;

    if(strlen(palavra) != 5){
        status = ERRO_TAMANHO_PALAVRA;
        return status;
    }

    for(int i = 0; i < 5; i++){
        if((palavra[i] < 65) || (palavra[i] > 90 && palavra[i] < 97) || (palavra[i] > 122)){
            status = ERRO_CARACTER_INVALIDO;
            return status;
        }
    }

    FILE* f;
    FILE* au;
    int tam, aux;
    char compara[6];
    compara[5] = '\0';

    au = fopen(ARQUIVO_AUXILIAR, "w+");
    if(au == NULL){
        status = ERRO_ABERTURA_ARQUIVO;
        return status;
    }

    f = fopen(ARQUIVO_PALAVRAS, "r+");
    if(f == NULL){
        fclose(au);
        status = ERRO_ABERTURA_ARQUIVO;
        return status;
    }

    fseek(f, 0, SEEK_END);
    tam = (int)ftell(f);
    tam = tam / (sizeof(char) * 6);
    rewind(f);
    long int posi;

    for(int i = 0; i < tam; i++){
        fread(compara, sizeof(char), 5, f);
        fgetc(f);
        aux = strcmp(palavra, compara);

        if(aux == 0){
            status = ERRO_PALAVRA_REPETIDA;
            fclose(f);
            fclose(au);
            return status;
        }
        else if(aux < 0){
            posi = ftell(f) - 6; 
            fwrite(palavra, sizeof(char), 5, au);
            fwrite("\n", sizeof(char), 1, au);
            fwrite(compara, sizeof(char), 5, au);
            fwrite("\n", sizeof(char), 1, au);

            while(fread(compara, sizeof(char), 5, f) == 5){
                fgetc(f);
                fwrite(compara, sizeof(char), 5, au);
                fwrite("\n", sizeof(char), 1, au);
            }

            rewind(au);
            fseek(f, posi, SEEK_SET);

            while(fread(compara, sizeof(char), 5, au) == 5){
                fgetc(au);
                fwrite(compara, sizeof(char), 5, f);
                fwrite("\n", sizeof(char), 1, f);
            }

            fclose(f);
            fclose(au);
            return status;
        }
    }

    fwrite(palavra, sizeof(char), 5, f);
    fwrite("\n", sizeof(char), 1, f);

    rewind(au);
    while(fread(compara, sizeof(char), 5, au) == 5){
        fgetc(au);
        fwrite(compara, sizeof(char), 5, f);
        fwrite("\n", sizeof(char), 1, f);
    }

    fclose(f);
    fclose(au);

    return status;
}