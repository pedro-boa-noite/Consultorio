#include "tRelatorio.h"

struct tRelatorio{
    int pacientesAtendidos;
    int idadeMedia;
    int pacientesFemininos;
    int pacientesMasculinos;
    int pacientesOutros;
    int tamanhoLesoesConsultas;
    int numTotalLesoes;
    int cirugiasTotais;
    int crioterapiasTotais;
};

tRelatorio *criaRelatorio(int pacientesAtendidos, int idadeMedia, int pacientesFemininos, int pacientesMasculinos, int pacientesOutros, int tamanhoLesoesConsultas, int numTotalLesoes, int cirugiasTotais, int crioterapiasTotais){
    tRelatorio* relatorio = calloc(1, sizeof(tRelatorio));

    relatorio->pacientesAtendidos = pacientesAtendidos;
    relatorio->idadeMedia = idadeMedia;
    relatorio->pacientesFemininos = pacientesFemininos;
    relatorio->pacientesMasculinos = pacientesMasculinos;
    relatorio->pacientesOutros = pacientesOutros;
    relatorio->tamanhoLesoesConsultas = tamanhoLesoesConsultas;
    relatorio->numTotalLesoes = numTotalLesoes;
    relatorio->cirugiasTotais = cirugiasTotais;
    relatorio->crioterapiasTotais = crioterapiasTotais;

    return relatorio;
}

void desalocaRelatorio(void *dado){
    tRelatorio* dadoTipado = (tRelatorio *) dado;

    if(dadoTipado != NULL) free(dadoTipado);
}

void imprimeNaTelaRelatorio(void *dado){
    tRelatorio* dadoTipado = (tRelatorio *) dado;

    if(dadoTipado != NULL){
        printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: ");
        printf("%d\n", dadoTipado->pacientesAtendidos);
        printf("IDADE MEDIA: ");
        printf("%d\n", dadoTipado->idadeMedia);
        printf("DISTRIBUICAO POR GENERO:\n");
        printf("- FEMININO: ");
        printf("%d\n", dadoTipado->pacientesFemininos);
        printf("- MASCULINO: ");
        printf("%d\n", dadoTipado->pacientesMasculinos);
        printf("- OUTROS: ");
        printf("%d\n", dadoTipado->pacientesOutros);
        printf("TAMANHO MEDIO DAS LESOES: ");
        printf("%d\n", dadoTipado->tamanhoLesoesConsultas);
        printf("NUMERO TOTAL DE LESOES: ");
        printf("%d\n", dadoTipado->numTotalLesoes);
        printf("NUMERO TOTAL DE CIRURGIAS: ");
        printf("%d\n", dadoTipado->cirugiasTotais);
        printf("NUMERO TOTAL DE CRIOTERAPIA: ");
        printf("%d\n", dadoTipado->crioterapiasTotais);
    }
}

void imprimeEmArquivoRelatorio(void *dado, char *path){
    tRelatorio* dadoTipado = (tRelatorio *) dado;
    char caminhoArquivo[1001];
    sprintf(caminhoArquivo, "%s/relatorio_geral.txt", path);

    FILE *relatorio = fopen(caminhoArquivo, "a");

    if(relatorio == NULL) {
        perror("Erro ao abrir o arquivo de relatorio");
        return;
    }

    fprintf(relatorio, "NUMERO TOTAL DE PACIENTES ATENDIDOS: ");
    fprintf(relatorio, "%d\n", dadoTipado->pacientesAtendidos);
    fprintf(relatorio, "IDADE MEDIA: ");
    fprintf(relatorio, "%d\n", dadoTipado->idadeMedia);
    fprintf(relatorio, "DISTRIBUICAO POR GENERO:\n");
    fprintf(relatorio, "- FEMININO: ");
    fprintf(relatorio, "%d\n", dadoTipado->pacientesFemininos);
    fprintf(relatorio, "- MASCULINO: ");
    fprintf(relatorio, "%d\n", dadoTipado->pacientesMasculinos);
    fprintf(relatorio, "- OUTROS: ");
    fprintf(relatorio, "%d\n", dadoTipado->pacientesOutros);
    fprintf(relatorio, "TAMANHO MEDIO DAS LESOES: ");
    fprintf(relatorio, "%d\n", dadoTipado->tamanhoLesoesConsultas);
    fprintf(relatorio, "NUMERO TOTAL DE LESOES: ");
    fprintf(relatorio, "%d\n", dadoTipado->numTotalLesoes);
    fprintf(relatorio, "NUMERO TOTAL DE CIRURGIAS: ");
    fprintf(relatorio, "%d\n", dadoTipado->cirugiasTotais);
    fprintf(relatorio, "NUMERO TOTAL DE CRIOTERAPIA: ");
    fprintf(relatorio, "%d\n", dadoTipado->crioterapiasTotais);

    fclose(relatorio);
}