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

Status trocar_cor_letra_em_palavra(Palavra *p_palavra, Cor cor, int indice) {
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
