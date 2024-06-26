#pragma once

#include "types.h"
#include "config.h"

typedef struct aux {
    Cor cor;
    char a_conteudo[CARACTERES_POR_LETRA + 1];
    struct aux *p_proxima;
} Letra;

typedef struct {
    Letra *p_primeira_letra;
} Palavra;

//////////////////////////////// Letras ////////////////////////////////

// Funcao que inicializa as structs Letra com valores default
static void inicializar_letra(Letra *p_letra);
    // p_letra = ponteiro para letra que deve ser inicializada

// Funcao que preenche o valor da letra com o conteudo do buffer
static Status preencher_letra(Letra *p_letra, char *p_buffer);
    // p_letra = ponteiro para a letra que deve ser preenchida
    // p_buffer = pontiero para o buffer que armazena o novo conteudo
    // retorno = {OK, ERRO_TAMANHO_BUFFER}


//////////////////////////////// Palavras ////////////////////////////////

// Funcao que inicializa as structs Palavra com valores default
void inicializar_palavra(Palavra *p_palavra);
    // p_palavra = ponteiro para palavra que deve ser inicializada

// Funcao que libera o espaco alocado dinamicamente de cada letra  
void deletar_palavra(Palavra *p_palavra);
    // p_palavra = ponteiro para Palavra que deve ser deletada

// Funcao que adiciona uma letra no fim da palavra
static Status adicionar_letra_em_palavra(Palavra *p_palavra, Letra letra);
    // p_palavra = ponteiro para palavra alvo
    // letra = string que armazena o conteudo para preencher
    // retorno = {OK, ERRO_OVERFLOW_PALAVRA, ERRO_ALOCACAO_MEMORIA, ERRO_TAMANHO_BUFFER}

// Funcao que preenche a palavra com uma letras para cada caractere em buffer
Status preencher_palavra(Palavra *p_palavra, char* p_buffer);
    // p_palavra = ponteiro para a palavra que deve ser preenchida
    // p_buffer = string que deve ser convertida em palavra
    // retorno = {OK, ERRO_OVERFLOW_PALAVRA, ERRO_ALOCACAO_MEMORIA, ERRO_TAMANHO_BUFFER}




