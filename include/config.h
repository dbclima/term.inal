#pragma once

// Macros para adicionar cor ao fundo automaticamente
#define BG_AMARELO(x)       "\033[1;37;43m" x "\033[0m"
#define BG_VERDE(x)         "\033[1;37;42m" x "\033[0m"
#define BG_NONE(x)          "\033[1;37m" x "\033[0m"

#define LETRAS_POR_PALAVRAS             5           // Quantidade de letras por palavra
#define CARACTERES_POR_LETRA            3           // 3 caracteres (cor, valor, cor)
#define MAXIMO_LETRAS_POR_PALAVRA       100         // Maximo de 100 letras por palavra

#define TECLADO             "qwertyuiopasdfghjklzxcvbnm"    // Letras teclado em ordem