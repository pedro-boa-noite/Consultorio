#include "tReceita.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct tReceita{
    char *nomePaciente;
    eTipoUso tipoUso;
    char *nomeMedicamento;
    char *tipoMedicamento;
    char *instrucoes;
    int qntd;
    char *nomeMedico;
    char *CRM;
    char *dataStr;
    // tPaciente* paciente;
    // tMedico* medico;
};

/**
 * Função que recebe todas as informações pertinentes a uma receita e retorna
 * um ponteiro com a receita criada.
 *
 */
tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr){

    tReceita* receita = (tReceita*) calloc (1, sizeof(tReceita));

    receita->tipoUso = tipoUso;
    receita->qntd = qntd;

    receita->nomePaciente = malloc((strlen(nomePaciente)+1)*sizeof(char));
    receita->nomeMedicamento = malloc((strlen(nomeMedicamento)+1)*sizeof(char));
    receita->tipoMedicamento = malloc((strlen(tipoMedicamento)+1)*sizeof(char));
    receita->instrucoes = malloc((strlen(instrucoes)+1)*sizeof(char));
    receita->nomeMedico = malloc((strlen(nomeMedico)+1)*sizeof(char));
    receita->CRM = malloc((strlen(CRM)+1)*sizeof(char));
    receita->dataStr = malloc((strlen(dataStr)+1)*sizeof(char));

    // receita->paciente = paciente;
    // receita->medico = medico;

    strcpy(receita->nomePaciente, nomePaciente);
    strcpy(receita->nomeMedicamento, nomeMedicamento);
    strcpy(receita->tipoMedicamento, tipoMedicamento);
    strcpy(receita->instrucoes, instrucoes);
    strcpy(receita->nomeMedico, nomeMedico);
    strcpy(receita->CRM, CRM);
    strcpy(receita->dataStr, dataStr);

    // if(medico == NULL) printf("Receita: %s %s %d %s %s %s (%s) %s\n", obtemNomePaciente(paciente), receita->nomeMedicamento, receita->qntd, receita->tipoMedicamento, receita->instrucoes, "", "", receita->dataStr);
    // else printf("Receita: %s %s %d %s %s %s (%s) %s\n", obtemNomePaciente(paciente), receita->nomeMedicamento, receita->qntd, receita->tipoMedicamento, receita->instrucoes, obtemNomeMedico(medico), obtemCrmMedico(medico), receita->dataStr);

    return receita;
}

/**
 * Função que recebe o ponteiro genérico (que deve conter uma receita) e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaReceita(void *dado){
    tReceita* dadoTipado = (tReceita *) dado;

    if(dadoTipado != NULL){
        if(dadoTipado->nomePaciente != NULL) free(dadoTipado->nomePaciente);
        if(dadoTipado->nomeMedicamento != NULL) free(dadoTipado->nomeMedicamento);
        if(dadoTipado->tipoMedicamento != NULL) free(dadoTipado->tipoMedicamento);
        if(dadoTipado->instrucoes != NULL) free(dadoTipado->instrucoes);
        if(dadoTipado->nomeMedico != NULL) free(dadoTipado->nomeMedico);
        if(dadoTipado->CRM != NULL) free(dadoTipado->CRM);
        if(dadoTipado->dataStr != NULL) free(dadoTipado->dataStr);
        free(dado);
    }
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma receita) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaReceita(void *dado){
    tReceita* dadoTipado = (tReceita *) dado;
    
    char tipoUso[15];
    if(dadoTipado->tipoUso == 0){
        strcpy(tipoUso, "USO ORAL");
    } else if(dadoTipado->tipoUso == 1){
        strcpy(tipoUso, "USO TOPICO");
    }

    // if(dadoTipado->medico == NULL) printf("RECEITUARIO\nNOME: %s\n\n%s\n\n%s\n%d %s\n\n%s\n\n%s (%s)\n%s\n\n", obtemNomePaciente(dadoTipado->paciente), tipoUso, dadoTipado->nomeMedicamento, dadoTipado->qntd, dadoTipado->tipoMedicamento, dadoTipado->instrucoes, "", "", dadoTipado->dataStr);
    // else printf("RECEITUARIO\nNOME: %s\n\n%s\n\n%s\n%d %s\n\n%s\n\n%s (%s)\n%s\n\n", obtemNomePaciente(dadoTipado->paciente), tipoUso, dadoTipado->nomeMedicamento, dadoTipado->qntd, dadoTipado->tipoMedicamento, dadoTipado->instrucoes, obtemNomeMedico(dadoTipado->medico), obtemCrmMedico(dadoTipado->medico), dadoTipado->dataStr);
    printf("RECEITUARIO\nNOME: %s\n\n%s\n\n%s\n%d %s\n\n%s\n\n%s (%s)\n%s\n\n", dadoTipado->nomePaciente, tipoUso, dadoTipado->nomeMedicamento, dadoTipado->qntd, dadoTipado->tipoMedicamento, dadoTipado->instrucoes, dadoTipado->nomeMedico, dadoTipado->CRM, dadoTipado->dataStr);
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma receita) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void imprimeEmArquivoReceita(void *dado, char *path){
    tReceita* dadoTipado = (tReceita *) dado;
    char caminhoArquivo[1001];
    sprintf(caminhoArquivo, "%s/receita.txt", path);

    FILE *receita = fopen(caminhoArquivo, "a");

    if(receita == NULL) {
        perror("Erro ao abrir o arquivo de receita");
        return;
    }

    char tipoUso[15];
    if(dadoTipado->tipoUso == 0){
        strcpy(tipoUso, "USO ORAL");
    } else if(dadoTipado->tipoUso == 1){
        strcpy(tipoUso, "USO TOPICO");
    }

    // if(dadoTipado->medico == NULL) fprintf(receita, "RECEITUARIO\nNOME: %s\n\n%s\n\n%s\n%d %s\n\n%s\n\n%s (%s)\n%s\n\n", obtemNomePaciente(dadoTipado->paciente), tipoUso, dadoTipado->nomeMedicamento, dadoTipado->qntd, dadoTipado->tipoMedicamento, dadoTipado->instrucoes, "", "", dadoTipado->dataStr);
    // else fprintf(receita, "RECEITUARIO\nNOME: %s\n\n%s\n\n%s\n%d %s\n\n%s\n\n%s (%s)\n%s\n\n", obtemNomePaciente(dadoTipado->paciente), tipoUso, dadoTipado->nomeMedicamento, dadoTipado->qntd, dadoTipado->tipoMedicamento, dadoTipado->instrucoes, obtemNomeMedico(dadoTipado->medico), obtemCrmMedico(dadoTipado->medico), dadoTipado->dataStr);
    fprintf(receita, "RECEITUARIO\nNOME: %s\n\n%s\n\n%s\n%d %s\n\n%s\n\n%s (%s)\n%s\n\n", dadoTipado->nomePaciente, tipoUso, dadoTipado->nomeMedicamento, dadoTipado->qntd, dadoTipado->tipoMedicamento, dadoTipado->instrucoes, dadoTipado->nomeMedico, dadoTipado->CRM, dadoTipado->dataStr);

    fclose(receita);
}
