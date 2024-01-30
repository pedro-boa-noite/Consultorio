#include "tDocumento.h"
#include <stdlib.h>

struct tDocumento{
    void *dado;
    func_ptr_imprimeNaTela imprimeNaTela;
    func_ptr_imprimeEmArquivo imprimeEmArquivo;
    func_ptr_desaloca desaloca;
};

/**
 * Função que recebe um dado genérico (representando um tipo de documento) e suas funções de callback.
 * A função cria um Documento e retorna um ponteiro para ele.
 */
tDocumento *criaDocumento(void *dado, func_ptr_imprimeNaTela imprimeNaTela, func_ptr_imprimeEmArquivo ImprimeEmArquivo, func_ptr_desaloca desaloca){
    tDocumento* documento = (tDocumento*) calloc (1, sizeof(tDocumento));

    documento->dado = dado;
    documento->imprimeNaTela = imprimeNaTela;
    documento->imprimeEmArquivo = ImprimeEmArquivo;
    documento->desaloca = desaloca;

    return documento;
}

/**
 * Função que recebe um Documento e o desaloca. O dado genérico também deve ser desalocado
 * dentro dessa função.
 */
void desalocaDocumento(tDocumento *doc){
    if(doc != NULL){
        if(doc->dado != NULL) doc->desaloca(doc->dado);
        free(doc);
    }
}

/**
 * Função que recebe um Documento genérico e o imprime na tela.
 */
void imprimeNaTelaDocumento(tDocumento *doc){
    doc->imprimeNaTela(doc->dado);
}

/**
 * Função que recebe um Documento genérico e o imprime em um arquivo.
 * O path representa o caminho até o diretório onde o arquivo será criado ou editado.
 */
void imprimeEmArquivoDocumento(tDocumento *doc, char *path){
    doc->imprimeEmArquivo(doc->dado, path);
}