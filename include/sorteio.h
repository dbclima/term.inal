#pragma once

#include "config.h"
#include "types.h"

//Função que sorteia a palavra para ser a resposta do jogo.
Status sortear_palavra(char* palavra_chave);
    //palavra_chave = string que armazena a palavra sorteada.

//Função que insere a palavra no arquivo palavras.txt, e o ordena, se a palavra não existir.
Status inserirpalavra(char* palavra);
    //palavra = string que irá ser inserida no arquivo.