#pragma once

#include "types.h"
#include "config.h"
#include "palavra.h"

// Funcao que captura e retorna o número de tentativas máximo
int capturar_dificuldade(); 

// Funcao que exibe o warning referente a ultima jogada
void printar_warning(char *p_buffer_warning);

// Funcao que recebe o input do usuario e relata eventuais erros
int receber_input_usuario(char *tentativa, char *p_buffer_warning, Palavra *p_palavras, int tentativa_atual);

// Funcao que exibe a rotina de vitoria
void rotina_vitoria();

// Funcao que exibe a rotina de derrota
void rotina_derrota(char* palavra_chave);

// Funncao que exibe e captura a rotina de jogar novamente
Bool jogar_novamente();

// Funcao que exibe o titulo do jogo
void printar_titulo_jogo();