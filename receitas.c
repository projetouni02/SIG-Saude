#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receitas.h"

void gerarReceitaArquivo() {
    int idConsulta;
    char nomeArquivo[64];
    char texto[512];
    FILE *f;

    printf("ID da consulta para a receita: ");
    scanf("%d", &idConsulta);
    getchar();

    snprintf(nomeArquivo, sizeof(nomeArquivo), "receita_%d.txt", idConsulta);

    printf("Digite a receita (uma ou mais linhas). Termine com uma linha apenas contendo END:\n");

    f = fopen(nomeArquivo, "w");
    if (!f) {
        printf("Erro ao criar arquivo.\n");
        return;
    }

    while (1) {
        if (!fgets(texto, sizeof(texto), stdin)) break;
        if (strcmp(texto, "END\n") == 0) break;
        fprintf(f, "%s", texto);
    }

    fclose(f);
    printf("Receita salva em %s\n", nomeArquivo);
}
