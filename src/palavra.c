#include <stdlib.h>
#include <string.h>

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
    // Implementacao Diogo
}

//////////////////////////// Palavras ////////////////////////////

inline void inicializar_palavra(Palavra *p_palavra) {
    p_palavra->p_primeira_letra = NULL;
}

void deletar_palavra(Palavra *p_palavra) {
    Letra *auxiliar;

    // Iterando ate a ultima letra
    while (p_palavra->p_primeira_letra != NULL) {
        auxiliar = p_palavra->p_primeira_letra;
        p_palavra->p_primeira_letra = auxiliar->p_proxima;
        free(auxiliar);
    }
}

static Status adicionar_letra_em_palavra(Palavra *p_palavra, Letra letra) {
    Status status = OK;
    
    Letra *verificador;
    verificador = p_palavra->p_primeira_letra;
    int contador = 0;
    
    // Encontramos a ultima letra da lista
    while (verificador != NULL) {
        if (contador++ == MAXIMO_LETRAS_POR_PALAVRA) {
            status = ERRO_OVERFLOW_PALAVRA;
            return status;
        }
        verificador = verificador->p_proxima;
    }

    // Alocamos espaco para a nova letra
    verificador = (Letra*) malloc(sizeof(Letra));
    if (verificador == NULL) {
        status = ERRO_ALOCACAO_MEMORIA;
        return status;
    }

    // Inicializamos a letra com valores default
    inicializar_letra(verificador);

    // preenchemos a letra interna com os valores da letra passada por parametro
    trocar_conteudo_letra(verificador, letra.conteudo);

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
    // Implementacao Diogo
}
