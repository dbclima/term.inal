#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "config.h"

#include "interface.h"

void rotina_vitoria() {
    system("clear");
    printf("\n\n\n%sVitoria!\n\n\n\n", OFFSET_PALAVRAS);
}

void rotina_derrota() {
    system("clear");
    printf("\n\n\n%sDerrota!\n\n\n\n", OFFSET_PALAVRAS);
}

Bool jogar_novamente() {
    Bool retorno;
    printf("Deseja jogar novamente? [s/n]: ");

    switch(getchar()) {
        case 's':
        case 'S':
            retorno = TRUE;
            break;
        case 'n':
        case 'N':
        default:
            retorno = FALSE;
            break;
    }

    return retorno;
}

void printar_warning(char *p_buffer_warning) {
    printf("\n%s%s%s\n", BG_NONE_FG_VERMELHO, p_buffer_warning, BG_NONE_FG_NONE);
}