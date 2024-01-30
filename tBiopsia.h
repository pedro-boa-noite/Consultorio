#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLesao.h"

typedef struct tBiopsia tBiopsia;

/**
 * Função que recebe todas as informações pertinentes a uma biopsia e retorna
 * um ponteiro com a biopsia criada.
 *
 */
tBiopsia *criaBiopsia(char *nomePaciente, char* CPF, tLesao** lesoes, int qtdLesoes, char *nomeMedico, char *CRM, char *dataStr);

/**
 * Função que recebe o ponteiro genérico (que deve conter uma biopsia) e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaBiopsia(void *dado);

/**
 * Função que recebe um ponteiro genérico (que deve conter uma biopsia) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaBiopsia(void *dado);

/**
 * Função que recebe um ponteiro genérico (que deve conter uma biopsia) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void imprimeEmArquivoBiopsia(void *dado, char *path);

#endif