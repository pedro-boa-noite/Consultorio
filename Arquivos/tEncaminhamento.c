#include "tEncaminhamento.h"

struct tEncaminhamento{
    char *nomePaciente;
    char *CPF;
    char *especialidade;
    char *motivoEncaminhamento;
    char *nomeMedico;
    char *CRM;
    char *dataStr;
};

/**
 * Função que recebe todas as informações pertinentes a um encaminhamento e retorna
 * um ponteiro com o encaminhamento criado.
 *
 */
tEncaminhamento *criaEncaminhamento(char *nomePaciente, char* CPF, char *especialidade, char *motivoEncaminhamento, char *nomeMedico, char *CRM, char *dataStr){
    tEncaminhamento* encaminhamento = (tEncaminhamento*) calloc (1, sizeof(tEncaminhamento));

    encaminhamento->nomePaciente = malloc((strlen(nomePaciente)+1)*sizeof(char));
    encaminhamento->CPF = malloc((strlen(CPF)+1)*sizeof(char));
    encaminhamento->especialidade = malloc((strlen(especialidade)+1)*sizeof(char));
    encaminhamento->motivoEncaminhamento = malloc((strlen(motivoEncaminhamento)+1)*sizeof(char));
    encaminhamento->nomeMedico = malloc((strlen(nomeMedico)+1)*sizeof(char));
    encaminhamento->CRM = malloc((strlen(CRM)+1)*sizeof(char));
    encaminhamento->dataStr = malloc((strlen(dataStr)+1)*sizeof(char));

    strcpy(encaminhamento->nomePaciente, nomePaciente);
    strcpy(encaminhamento->CPF, CPF);
    strcpy(encaminhamento->especialidade, especialidade);
    strcpy(encaminhamento->motivoEncaminhamento, motivoEncaminhamento);
    strcpy(encaminhamento->nomeMedico, nomeMedico);
    strcpy(encaminhamento->CRM, CRM);
    strcpy(encaminhamento->dataStr, dataStr);

    return encaminhamento;
}

/**
 * Função que recebe o ponteiro genérico (que deve conter um encaminhamento) e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaEncaminhamento(void *dado){
    tEncaminhamento* dadoTipado = (tEncaminhamento *) dado;

    if(dadoTipado != NULL){
        if(dadoTipado->nomePaciente != NULL) free(dadoTipado->nomePaciente);
        if(dadoTipado->CPF != NULL) free(dadoTipado->CPF);
        if(dadoTipado->especialidade != NULL) free(dadoTipado->especialidade);
        if(dadoTipado->motivoEncaminhamento != NULL) free(dadoTipado->motivoEncaminhamento);
        if(dadoTipado->nomeMedico != NULL) free(dadoTipado->nomeMedico);
        if(dadoTipado->CRM != NULL) free(dadoTipado->CRM);
        if(dadoTipado->dataStr != NULL) free(dadoTipado->dataStr);
        free(dado);
    }
}

/**
 * Função que recebe um ponteiro genérico (que deve conter um encaminhamento) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaEncaminhamento(void *dado){
    tEncaminhamento* dadoTipado = (tEncaminhamento *) dado;

    printf("PACIENTE: %s\nCPF: %s\n\nESPECIALIDADE ENCAMINHADA: %s\n\nMOTIVO: %s\n\n%s (%s)\n%s\n\n", 
    dadoTipado->nomePaciente, dadoTipado->CPF, dadoTipado->especialidade, dadoTipado->motivoEncaminhamento, 
    dadoTipado->nomeMedico, dadoTipado->CRM, dadoTipado->dataStr);
}

/**
 * Função que recebe um ponteiro genérico (que deve conter um encaminhamento) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void imprimeEmArquivoEncaminhamento(void *dado, char *path){
    tEncaminhamento* dadoTipado = (tEncaminhamento *) dado;
    char caminhoArquivo[1001];
    sprintf(caminhoArquivo, "%s/encaminhamento.txt", path);

    FILE *encaminhamento = fopen(caminhoArquivo, "a");

    if(encaminhamento == NULL) {
        perror("Erro ao abrir o arquivo de encaminhamento");
        return;
    }

    int dia, mes, ano;
    sscanf(dadoTipado->dataStr, "%d/%d/%d", &dia, &mes, &ano);
    char data[11];
    sprintf(data, "%d/%d/%d", dia, mes, ano);

    fprintf(encaminhamento, "PACIENTE: %s\nCPF: %s\n\nESPECIALIDADE ENCAMINHADA: %s\nMOTIVO: %s\n\n%s (%s)\n%s\n\n", 
    dadoTipado->nomePaciente, dadoTipado->CPF, dadoTipado->especialidade, dadoTipado->motivoEncaminhamento, 
    dadoTipado->nomeMedico, dadoTipado->CRM, data);

    fclose(encaminhamento);
}
