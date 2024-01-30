

#ifndef _TLESAO_H_
#define _TLESAO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tLesao tLesao;

void registroBinarioLesoes(tLesao* l, FILE* file);

tLesao* cadastrarLesao(FILE* file, char* diagnostico, char* regiao, int tamanho, int cirurgia, int crioterapia);

void desalocaLesao(tLesao* l);

char* obtemDiagnosticoLesao(tLesao* l);

char* obtemRegiaoLesao(tLesao* l);

int obtemTamanhoLesao(tLesao* l);

int obtemCirurgiaLesao(tLesao* l);

int obtemCrioterapiaLesao(tLesao* l);

#endif