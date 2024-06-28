#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "types.h"
#include "sorteio.h"

Status sortear_palavra(char* palavra_chave){
    int tam, pos;
    FILE* f;

    tam = fseek(f, 0, SEEK_END);
    tam = tam/(sizeof(char)*6);

    pos = rand()%tam;
    pos = pos*(sizeof(char)*6);

    fseek(f, pos, SEEK_SET);
    fscanf(f, "%s", palavra_chave)
}