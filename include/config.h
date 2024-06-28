#pragma once

// Macros para adicionar cor ao fundo
#define BG_AMARELO_FG_BRANCO            "\033[1;37;43m"
#define BG_VERDE_FG_BRANCO              "\033[1;37;42m"
#define BG_NONE_FG_BRANCO               "\033[1;37m"
#define BG_NONE_FG_NONE                 "\033[0m"
#define BG_NONE_FG_VERMELHO             "\033[1;31m"

#define LETRAS_POR_PALAVRAS             5           // Quantidade de letras por palavra
#define MAXIMO_LETRAS_POR_PALAVRA       100         // Maximo de 100 letras por palavra
#define CARACTERES_POR_LETRA            3           // Toda letra possui 3 caracteres (cor, valor, cor)
#define MAXIMO_TAMANHO_LETRA            11 + 1 + 11

#define TECLAS_PRIMEIRA_FILEIRA         "qwertyuiop"
#define TECLAS_SEGUNDA_FILEIRA          "asdfghjkl"
#define TECLAS_TERCEIRA_FILEIRA         "zxcvbnm"    // Letras teclado em ordem



#define DEFAULT_CARACTERE   BG_NONE("_")

#define OFFSET_TECLADO      "                            "
#define OFFSET_PALAVRAS     OFFSET_TECLADO "       "