#pragma once

typedef enum {
    NONE,
    AMARELO,
    VERDE
} Cor;

typedef enum {
    FALSE,
    TRUE
} Bool;

typedef enum {
    OK,
    ERRO_ALOCACAO_MEMORIA,
    ERRO_ABERTURA_ARQUIVO,
    ERRO_OVERFLOW_PALAVRA,
    ERRO_TAMANHO_BUFFER,
    ERRO_TECLAS_TECLADO,
    ERRO_INDICE_FORA_DE_ALCANCE,
} Status;

typedef enum {
    NO_WARNINGS = 1,
    PALAVRA_REPETIDA = 2,
    NUMERO_LETRAS_INVALIDO = 3,
    CARACTERE_INVALIDO = 5,
} Warning;