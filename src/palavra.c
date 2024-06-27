#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "config.h"
#include "types.h"
#include "palavra.h"

//////////////////////////// Letras ////////////////////////////////

inline void inicializar_letra(Letra *p_letra) {
    p_letra->cor = NONE;
    p_letra->conteudo = '_';
    p_letra->p_proxima = NULL;
}

inline void trocar_conteudo_letra(Letra *p_letra, const char buffer) {
    p_letra->conteudo = buffer;
}

inline void trocar_cor_letra(Letra *p_letra, const Cor cor) {
    p_letra->cor = cor;
}

static void converter_letra_string(Letra *p_letra, char *p_buffer) {
    char modificador_cor_entrada, modificador_cor_saida;
    modificador_cor_saida = BG_NONE_FG_NONE;
    
    switch(p_letra->cor) {
        case NONE:
            modificador_cor_entrada = BG_NONE_FG_BRANCO;
            break;
        
        case AMARELO:
            modificador_cor_entrada = BG_AMARELO_FG_BRANCO;
            break;
        
        case VERDE:
            modificador_cor_entrada = BG_VERDE_FG_BRANCO;
            break; 
    }

    snprintf(p_buffer, CARACTERES_POR_LETRA + 1, "%c%c%c", modificador_cor_entrada, p_letra->conteudo, modificador_cor_saida);
}

//////////////////////////// Palavras ////////////////////////////

inline void inicializar_palavra(Palavra *p_palavra) {
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
}

static Status adicionar_letra_em_palavra(Palavra *p_palavra, Letra letra) {
    Status status = OK;
    
    Letra *letra_auxiliar;
    letra_auxiliar = p_palavra->p_primeira_letra;
    int contador = 0;
    
    // Encontramos a ultima letra da lista
    while (letra_auxiliar != NULL) {
        if (contador++ == MAXIMO_LETRAS_POR_PALAVRA) {
            status = ERRO_OVERFLOW_PALAVRA;
            return status;
        }
        letra_auxiliar = letra_auxiliar->p_proxima;
    }

    // Alocamos espaco para a nova letra
    letra_auxiliar = (Letra*) malloc(sizeof(Letra));
    if (letra_auxiliar == NULL) {
        status = ERRO_ALOCACAO_MEMORIA;
        return status;
    }

    // Inicializamos a letra com valores default
    inicializar_letra(letra_auxiliar);

    // preenchemos a letra interna com os valores da letra passada por parametro
    trocar_conteudo_letra(letra_auxiliar, letra.conteudo);

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

    for (int i = 0; i < strlen(p_buffer); i++) {
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

void converter_palavra_string(Palavra *p_palavra, char *p_buffer) {
    char string_auxiliar[4];
    Letra *letra_auxiliar;

    letra_auxiliar = p_palavra->p_primeira_letra;

    while (letra_auxiliar != NULL) {
        converter_letra_string(letra_auxiliar, string_auxiliar);
        strncat(p_buffer, string_auxiliar, CARACTERES_POR_LETRA);
        letra_auxiliar = letra_auxiliar->p_proxima;
    }
}
