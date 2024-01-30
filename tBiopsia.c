#include "tBiopsia.h"

struct tBiopsia{
    char* nomePaciente;
    char* CPF;
    tLesao** lesoes;
    int qtdLesoes;
    char* nomeMedico;
    char* CRM;
    char* dataStr;
};

/**
 * Função que recebe todas as informações pertinentes a uma biopsia e retorna
 * um ponteiro com a biopsia criada.
 *
 */
tBiopsia *criaBiopsia(char *nomePaciente, char *CPF, tLesao** lesoes, int qtdLesoes, char *nomeMedico, char *CRM, char *dataStr){
    tBiopsia* biopsia = (tBiopsia*) calloc (1, sizeof(tBiopsia));

    biopsia->qtdLesoes = qtdLesoes;

    biopsia->nomePaciente = malloc((strlen(nomePaciente)+1)*sizeof(char));
    biopsia->CPF = malloc((strlen(CPF)+1)*sizeof(char));
    biopsia->nomeMedico = malloc((strlen(nomeMedico)+1)*sizeof(char));
    biopsia->CRM = malloc((strlen(CRM)+1)*sizeof(char));
    biopsia->dataStr = malloc((strlen(dataStr)+1)*sizeof(char));

    //biopsia->lesoes = malloc(qtdLesoes * sizeof(tLesao*));
    // for(int i=0; i<qtdLesoes; i++){
    //     biopsia->lesoes[i] = lesoes[i];
    // }

    biopsia->lesoes = lesoes;

    strcpy(biopsia->nomePaciente, nomePaciente);
    strcpy(biopsia->CPF, CPF);
    strcpy(biopsia->nomeMedico, nomeMedico);
    strcpy(biopsia->CRM, CRM);
    strcpy(biopsia->dataStr, dataStr);

    return biopsia;
}

/**
 * Função que recebe o ponteiro genérico (que deve conter uma biopsia) e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaBiopsia(void *dado){
    tBiopsia* dadoTipado = (tBiopsia *) dado;

    if(dadoTipado != NULL){
        if(dadoTipado->nomePaciente != NULL) free(dadoTipado->nomePaciente);
        if(dadoTipado->CPF != NULL) free(dadoTipado->CPF);
        // for(int i=0; i<dadoTipado->qtdLesoes; i++){
        //     desalocaLesao(dadoTipado->lesoes[i]);
        // }
        //free(dadoTipado->lesoes);
        if(dadoTipado->nomeMedico != NULL) free(dadoTipado->nomeMedico);
        if(dadoTipado->CRM != NULL) free(dadoTipado->CRM);
        if(dadoTipado->dataStr != NULL) free(dadoTipado->dataStr);
        free(dado);
    }
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma biopsia) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaBiopsia(void *dado){
    tBiopsia* dadoTipado = (tBiopsia *) dado;

    printf("PACIENTE: %s\nCPF: %s\n\nSOLICITACAO DE BIOPSIA PARA AS LESOES:\n", dadoTipado->nomePaciente, dadoTipado->CPF);
    for(int i=0; i<dadoTipado->qtdLesoes; i++){
        if(obtemCirurgiaLesao(dadoTipado->lesoes[i]) == 1) printf("L%d - %s - %s - %dMM\n", i, obtemDiagnosticoLesao(dadoTipado->lesoes[i]), obtemRegiaoLesao(dadoTipado->lesoes[i]), obtemTamanhoLesao(dadoTipado->lesoes[i]));
    }
    printf("\n%s (%s)\n%s\n\n", dadoTipado->nomeMedico, dadoTipado->CRM, dadoTipado->dataStr);
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma biopsia) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void imprimeEmArquivoBiopsia(void *dado, char *path){
    tBiopsia* dadoTipado = (tBiopsia *) dado;
    char caminhoArquivo[1001];
    sprintf(caminhoArquivo, "%s/biopsia.txt", path);

    FILE *biopsia = fopen(caminhoArquivo, "a");

    if(biopsia == NULL) {
        perror("Erro ao abrir o arquivo de biopsia");
        return;
    }

    int dia, mes, ano;
    sscanf(dadoTipado->dataStr, "%d/%d/%d", &dia, &mes, &ano);
    char data[11];
    sprintf(data, "%d/%d/%d", dia, mes, ano);

    fprintf(biopsia, "PACIENTE: %s\nCPF: %s\n\nSOLICITACAO DE BIOPSIA PARA AS LESOES:\n", dadoTipado->nomePaciente, dadoTipado->CPF);
    for(int i=0; i<dadoTipado->qtdLesoes; i++){
        if(obtemCirurgiaLesao(dadoTipado->lesoes[i]) == 1) fprintf(biopsia, "L%d - %s - %s - %dMM\n", i+1, obtemDiagnosticoLesao(dadoTipado->lesoes[i]), obtemRegiaoLesao(dadoTipado->lesoes[i]), obtemTamanhoLesao(dadoTipado->lesoes[i]));
    }
    fprintf(biopsia, "\n%s (%s)\n%s\n\n", dadoTipado->nomeMedico, dadoTipado->CRM, data);

    fclose(biopsia);
}