#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "types.h"
#include "palavra.h"

//////////////////////////// Letras ////////////////////////////////

void inicializar_letra(Letra *p_letra) {
    p_letra->cor = NONE;
    p_letra->conteudo = '_';
    p_letra->p_proxima = NULL;
}

void trocar_conteudo_letra(Letra *p_letra, const char buffer) {
    p_letra->conteudo = buffer;
}

void trocar_cor_letra(Letra *p_letra, const Cor cor) {
    p_letra->cor = cor;
}

void converter_letra_string(Letra *p_letra, char *p_buffer, Bool espaco_entre_letras) {
    char modificador_cor_entrada[MAXIMO_TAMANHO_LETRA + 1], modificador_cor_saida[MAXIMO_TAMANHO_LETRA + 1];
    strcpy(modificador_cor_saida, BG_NONE_FG_NONE);
    
    switch(p_letra->cor) {
        case NONE:
            strcpy(modificador_cor_entrada, BG_NONE_FG_BRANCO);
            break;
        
        case AMARELO:
            strcpy(modificador_cor_entrada, BG_AMARELO_FG_BRANCO);
            break;
        
        case VERDE:
            strcpy(modificador_cor_entrada, BG_VERDE_FG_BRANCO);
            break;
        case VERMELHO:
            strcpy(modificador_cor_entrada, BG_VERMELHO_FG_BRANCO);
            break;
    }

    sprintf(p_buffer, "%s%c%s", modificador_cor_entrada, p_letra->conteudo, modificador_cor_saida);
    if (espaco_entre_letras) strncat(p_buffer, " ", 2);
}

//////////////////////////// Palavras ////////////////////////////

void inicializar_palavra(Palavra *p_palavra) {
    p_palavra->p_primeira_letra = NULL;
}

void deletar_palavra(Palavra *p_palavra) {
    Letra *letra_auxiliar;

    // Iterando ate a ultima letra
    while (p_palavra->p_primeira_letra != NULL) {
        letra_auxiliar = p_palavra->p_primeira_letra;
        p_palavra->p_primeira_letra = letra_auxiliar->p_proxima;
        free(letra_auxiliar);
    }

    p_palavra->p_primeira_letra = NULL;
}

Status adicionar_letra_em_palavra(Palavra *p_palavra, Letra letra) {
    Status status = OK;
    
    if (get_tamanho_palavra(p_palavra) > MAXIMO_LETRAS_POR_PALAVRA) {
        status = ERRO_OVERFLOW_PALAVRA;
        return status;
    }

    Letra *letra_auxiliar = (Letra*) malloc(sizeof(Letra));
    if (letra_auxiliar == NULL) {
        status = ERRO_ALOCACAO_MEMORIA;
        return status;
    }
    inicializar_letra(letra_auxiliar);

    trocar_conteudo_letra(letra_auxiliar, letra.conteudo);
    letra_auxiliar->p_proxima = p_palavra->p_primeira_letra;
    p_palavra->p_primeira_letra = letra_auxiliar;

    return status; 
}

Status preencher_palavra(Palavra *p_palavra, char *p_buffer) {
    Status status = OK;
    Letra letra_auxiliar;

    if (strlen(p_buffer) > MAXIMO_LETRAS_POR_PALAVRA + 1) {
        status = ERRO_OVERFLOW_PALAVRA;
        return status;
    }

    inicializar_letra(&letra_auxiliar);

    // Primeiro limpamos o conteudo prévio em palavra
    deletar_palavra(p_palavra);

    for (int i = strlen(p_buffer) - 1; i >= 0; i--) {
        trocar_conteudo_letra(&letra_auxiliar, p_buffer[i]);
        status = adicionar_letra_em_palavra(p_palavra, letra_auxiliar);

        if (status != OK) {
            return status;
        }
    }

    return status;
}

int get_tamanho_palavra(Palavra *p_palavra) {
    int contador = 0;
    Letra *letra_auxiliar;

    letra_auxiliar = p_palavra->p_primeira_letra;

    while (letra_auxiliar != NULL) {
        contador++;
        letra_auxiliar = letra_auxiliar->p_proxima;
    }

    return contador;
}

void converter_palavra_string(Palavra *p_palavra, char *p_buffer, Bool espaco_entre_letras) {
    char string_auxiliar[MAXIMO_TAMANHO_LETRA + 1 + 1] = "";
    Letra *letra_auxiliar;

    letra_auxiliar = p_palavra->p_primeira_letra;

    while (letra_auxiliar != NULL) {
        converter_letra_string(letra_auxiliar, string_auxiliar, espaco_entre_letras);
        strcat(p_buffer, string_auxiliar);
        letra_auxiliar = letra_auxiliar->p_proxima;
    }
}

Status trocar_cor_letra_em_palavra_idx(Palavra *p_palavra, Cor cor, int indice) {
    Status status = OK;
    Letra *p_letra_auxiliar;

    if (indice >= get_tamanho_palavra(p_palavra)) {
        status = ERRO_INDICE_FORA_DE_ALCANCE;
        return status;
    }

    p_letra_auxiliar = p_palavra->p_primeira_letra;

    for (int i = 0; i < indice; i++) {
        p_letra_auxiliar = p_letra_auxiliar->p_proxima;
    }

    trocar_cor_letra(p_letra_auxiliar, cor);
    return status;
}

void trocar_cor_letra_em_teclado_char(Palavra *p_palavra, Cor cor, char c){


    Letra *p_letra_auxiliar;


    for (int j = 0; j < 3;j++){
        p_letra_auxiliar = p_palavra[j].p_primeira_letra;
        for (int i = 0; i < get_tamanho_palavra(&p_palavra[j]); i++)
        {
            if ((p_letra_auxiliar->conteudo == c) && (p_letra_auxiliar->cor != VERDE))
            {
                trocar_cor_letra(p_letra_auxiliar, cor);
                return;
            }

            p_letra_auxiliar = p_letra_auxiliar->p_proxima;
        }
    }

        
}

Status printar_palavra(Palavra *p_palavra, char *p_buffer_offset, Bool espaco_entre_letras) {
    Status status = OK;
    char *string_palavra = (char*) malloc(sizeof(char) * (get_tamanho_palavra(p_palavra) * (MAXIMO_TAMANHO_LETRA + 1) + 1));
    if (string_palavra == NULL) {
        status = ERRO_ALOCACAO_MEMORIA;
        return status;
    }
    // Se certificando que string_palavra eh uma string vazia
    string_palavra[0] = '\0';

    converter_palavra_string(p_palavra, string_palavra, espaco_entre_letras);
    printf("%s%s\n", p_buffer_offset, string_palavra);
    free(string_palavra);
    return status;
}

Status printar_teclado(Palavra *p_teclado, char* p_buffer_offset) {
    Status status = OK;
    for (int i = 0; i < 3; i++) {
        switch(i) {
            case 1:
                printf(" ");
                break;
            case 2:
                printf("   ");
                break;
            default:
                break;
        }
        status = printar_palavra(&p_teclado[i], p_buffer_offset, TRUE);
        if (status != OK) return status;
    }

    return status;
}

Status iniciar_teclado(Palavra *p_teclado){

    if(p_teclado == NULL){
        return ERRO_ALOCACAO_MEMORIA;
    } 

    char *stringPrimeiraFileira = TECLAS_PRIMEIRA_FILEIRA;
    char *stringSegundaFileira = TECLAS_SEGUNDA_FILEIRA;
    char *stringTerceiraFileira = TECLAS_TERCEIRA_FILEIRA;
    Palavra primeiraFileira, segundaFileira, terceiraFileira;

    inicializar_palavra(&primeiraFileira);
    inicializar_palavra(&segundaFileira);
    inicializar_palavra(&terceiraFileira);

    preencher_palavra(&primeiraFileira, stringPrimeiraFileira);
    preencher_palavra(&segundaFileira, stringSegundaFileira);
    preencher_palavra(&terceiraFileira, stringTerceiraFileira);

    Letra *letraAuxiliar1;
    letraAuxiliar1 = primeiraFileira.p_primeira_letra;
    for (int i = 0; i < get_tamanho_palavra(&primeiraFileira); i++)
    {
        letraAuxiliar1->cor = NONE;
        letraAuxiliar1 = letraAuxiliar1->p_proxima;
    }

    Letra *letraAuxiliar2;
    letraAuxiliar2 = primeiraFileira.p_primeira_letra;
    for (int i = 0; i < get_tamanho_palavra(&segundaFileira);i++){
        letraAuxiliar2->cor = NONE;
        letraAuxiliar2 = letraAuxiliar2->p_proxima;
    }

    Letra *letraAuxiliar3;
    letraAuxiliar3 = primeiraFileira.p_primeira_letra;
    for (int i = 0; i < get_tamanho_palavra(&terceiraFileira);i++){
        letraAuxiliar3->cor = NONE;
        letraAuxiliar3 = letraAuxiliar3->p_proxima;
    }

    p_teclado[0] = primeiraFileira;
    p_teclado[1] = segundaFileira;
    p_teclado[2] = terceiraFileira;

    return OK;
};

Bool processar_nova_palavra(Palavra *p_teclado, char* palavra_chave, char *palavraTentativa, Palavra *p_palavras, int tentativaAtual){

    Palavra palavraTentativaOriginal;
    Palavra palavra_fim;
    int contador = 0;

    inicializar_palavra(&palavra_fim); //esse q faltou
    inicializar_palavra(&palavraTentativaOriginal);
    preencher_palavra(&palavraTentativaOriginal, palavraTentativa);
    preencher_palavra(&palavra_fim, palavraTentativa);

    char palavraChaveAtual[6];

    strcpy(palavraChaveAtual, palavra_chave);

    Letra *letraAuxiliarVerde;
    letraAuxiliarVerde = palavraTentativaOriginal.p_primeira_letra;


    for (int i = 0; i < get_tamanho_palavra(&palavraTentativaOriginal);i++){
        if(palavraChaveAtual[i] == letraAuxiliarVerde->conteudo){
            trocar_cor_letra_em_palavra_idx(&palavra_fim, VERDE, i);
            trocar_conteudo_letra(letraAuxiliarVerde, '_');
            trocar_cor_letra_em_teclado_char(p_teclado, VERDE, palavraChaveAtual[i]);
            palavraChaveAtual[i] = '-';
            contador++;
        }
        else
        {
            trocar_cor_letra_em_teclado_char(p_teclado, VERMELHO, palavraTentativa[i]);
        }
            letraAuxiliarVerde = letraAuxiliarVerde->p_proxima;
    }

    printar_palavra(&palavraTentativaOriginal, "", FALSE);

    Letra *letraAuxiliarAmarelo;
    letraAuxiliarAmarelo = palavraTentativaOriginal.p_primeira_letra;

    for (int i = 0; i < get_tamanho_palavra(&palavraTentativaOriginal);i++){
            letraAuxiliarAmarelo = palavraTentativaOriginal.p_primeira_letra;
        for (int j = 0; j < get_tamanho_palavra(&palavraTentativaOriginal);j++){
            if (palavraChaveAtual[i] == letraAuxiliarAmarelo->conteudo)
            {
                trocar_cor_letra_em_palavra_idx(&palavra_fim, AMARELO, j);
                trocar_conteudo_letra(letraAuxiliarAmarelo, '_');
                trocar_cor_letra_em_teclado_char(p_teclado, AMARELO, palavraChaveAtual[i]);
                break;
            }
            letraAuxiliarAmarelo = letraAuxiliarAmarelo->p_proxima;
        }
    }
    printar_palavra(&palavraTentativaOriginal, "", FALSE);



    p_palavras[tentativaAtual] = palavra_fim;


    if(contador == 5){
        return TRUE;
    }

    return FALSE;
}

void deletar_palavras(Palavra *p_palavras, int numero_palavras){

    for (int i = 0; i < numero_palavras;i++){
        deletar_palavra(p_palavras + i);
    }
}

void deletar_teclado(Palavra *p_teclado){
    for (int i = 0; i < 3;i++){
        deletar_palavra(p_teclado + i);
    }
};
