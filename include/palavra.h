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
void inicializar_letra(Letra *p_letra);
    // p_letra = ponteiro para letra que deve ser inicializada

// Funcao permite trocar o conteudo da letra para o conteudo do buffer
void trocar_conteudo_letra(Letra *p_letra, const char buffer);
    // p_letra = ponteiro para a letra que deve ser preenchida
    // buffer = buffer que armazena o novo conteudo

// Funcao que permite trocar a cor da letra
void trocar_cor_letra(Letra *p_letra, const Cor cor);
    // p_letra = ponteiro para a letra que deve ser colorida
    // cor = cor que deve ser aplicada na letra

// Funcao que converte a letra para uma string colorida
void converter_letra_string(Letra *p_letra, char *p_buffer, Bool espaco_entre_letras);
    // p_letra = ponteiro para a letra que deve ser convertida em string
    // p_buffer = string que armazenara a converao 


//////////////////////////////// Palavras ////////////////////////////////

// Funcao que inicializa as structs Palavra com valores default
void inicializar_palavra(Palavra *p_palavra);
    // p_palavra = ponteiro para palavra que deve ser inicializada

// Funcao que libera o espaco alocado dinamicamente de cada letra  
void deletar_palavra(Palavra *p_palavra);
    // p_palavra = ponteiro para Palavra que deve ser deletada

// Funcao que adiciona uma letra no fim da palavra
Status adicionar_letra_em_palavra(Palavra *p_palavra, Letra letra);
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
void converter_palavra_string(Palavra *p_palavra, char *p_buffer, Bool espaco_entre_letras);
    // p_palavra = ponteiro para a palavra alvo
    // p_buffer = string que armazenara a conversao

// Funcao que permite trocar a cor de uma letra na palavra na posicao indice
Status trocar_cor_letra_em_palavra_idx(Palavra *p_palavra, Cor cor, int indice);
    // p_palavra = ponteiro para a palavra que deve ser modificada
    // cor = cor que deve ser aplicada a palavra
    // indice = indice da letra que dele ser modificada

// Funcao que printa no stdout o conteudo de palavra
Status printar_palavra(Palavra *p_palavra, char *p_buffer_offset, Bool espaco_entre_letras);
    // p_palavra = ponteiro para a palavra que deve ser impressa
    // p_buffer_offset = ponteiro para o buffer de offset (formatacao)
    // espaco_entre_letras = Bool que diz se tem ou nao espaco entre letras

// Funcao que printa o teclado formatado no stdout
Status printar_teclado(Palavra *p_teclado, char* p_buffer_offset);
    // p_teclado = ponteiro para o teclado
    // p_buffer_offset = ponteiro para o buffer de offset (formatacao)

Status iniciar_teclado(Palavra *p_teclado);

Bool processar_nova_palavra(Palavra *p_teclado, char *palavra_chave, char *palavraTentativa, Palavra *p_palavras, int tentativaAtual);