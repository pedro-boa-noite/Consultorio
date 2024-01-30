#include "tLista.h"

struct tLista{
    tPaciente** pacientes;
    int qtdPacientes;
};

tLista *criaLista(){
    tLista* lista = calloc(1, sizeof(tLista));

    if(lista == NULL){
        perror("Erro ao alocar lista");
        exit(1);
    }

    lista->pacientes = NULL;

    return lista;
}

void insereLista(tLista* lista, tPaciente* paciente){
    
    (lista->qtdPacientes)++;

    lista->pacientes = realloc(lista->pacientes, sizeof(tPaciente*)*lista->qtdPacientes);
    lista->pacientes[(lista->qtdPacientes) - 1] = paciente;
}

void desalocaLista(void *dado){
    tLista* dadoTipado = (tLista *) dado;

    if(dadoTipado != NULL){
        free(dadoTipado->pacientes);
        free(dadoTipado);
    }
}

void imprimeNaTelaLista(void *dado){
    tLista* dadoTipado = (tLista *) dado;

    if(dadoTipado != NULL){
        for(int i=0; i<dadoTipado->qtdPacientes; i++){
            printf("%d - %s (%s)\n\n", i+1, obtemNomePaciente(dadoTipado->pacientes[i]), obtemCpfPaciente(dadoTipado->pacientes[i]));
        }
    }    
}

void imprimeEmArquivoLista(void *dado, char *path){
    tLista* dadoTipado = (tLista *) dado;
    char caminhoArquivo[1001];
    sprintf(caminhoArquivo, "%s/lista_busca.txt", path);

    FILE *lista = fopen(caminhoArquivo, "a");

    if(lista == NULL) {
        perror("Erro ao abrir o arquivo de lista");
        return;
    }

    for(int i=0; i<dadoTipado->qtdPacientes; i++){
        fprintf(lista, "%d - %s (%s)\n\n", i+1, obtemNomePaciente(dadoTipado->pacientes[i]), obtemCpfPaciente(dadoTipado->pacientes[i]));
    }

    fclose(lista);
}

int listaNula(tLista *lista){
    if(lista->pacientes == NULL) return 1;
    return 0;
}