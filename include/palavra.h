#pragma once

#include "types.h"
#include "config.h"

typedef struct aux {
    Cor cor;
    char conteudo;
    struct aux *p_proxima;
} Letra;

typedef struct {
    Letra *p_primeira_letra;
} Palavra;

//////////////////////////////// Letras ////////////////////////////////

// Funcao que inicializa as structs Letra com valores default
inline void inicializar_letra(Letra *p_letra);
    // p_letra = ponteiro para letra que deve ser inicializada

// Funcao permite trocar o conteudo da letra para o conteudo do buffer
inline void trocar_conteudo_letra(Letra *p_letra, const char buffer);
    // p_letra = ponteiro para a letra que deve ser preenchida
    // buffer = buffer que armazena o novo conteudo

// Funcao que permite trocar a cor da letra
inline void trocar_cor_letra(Letra *p_letra, const Cor cor);
    // p_letra = ponteiro para a letra que deve ser colorida
    // cor = cor que deve ser aplicada na letra

// Funcao que converte a letra para uma string colorida
static void converter_letra_string(Letra *p_letra, char *p_buffer);
    // p_letra = ponteiro para a letra que deve ser convertida em string
    // p_buffer = string que armazenara a converao 


//////////////////////////////// Palavras ////////////////////////////////

// Funcao que inicializa as structs Palavra com valores default
inline void inicializar_palavra(Palavra *p_palavra);
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

// Funcao que retorna o tamanho da palavra
int get_tamanho_palavra(Palavra *p_palavra);
    // p_palavra = ponteiro para a palavra que deve ser "medida"

// Funcao que converte a palavra inteira em uma string colorida
void converter_palavra_string(Palavra *p_palavra, char *p_buffer);
    // p_palavra = ponteiro para a palavra alvo
    // p_buffer = string que armazenara a conversao


