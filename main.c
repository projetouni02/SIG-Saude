#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#include "banco.h"
#include "login.h"
#include "usuarios.h"
#include "pacientes.h"
#include "medicos.h"
#include "consultas.h"
#include "receitas.h"

int menuAdmin(sqlite3 *db);
int menuRecepcao(sqlite3 *db);
void menuMedico(sqlite3 *db, int idMedico);

int main(void) {
    sqlite3 *db;
    if (abrirBanco(&db) != 0) {
        printf("Nao foi possivel abrir o banco.\n");
        return 1;
    }
    criarTabelas(db);

    printf("Se for a primeira vez, usuario admin criado: admin / admin\n");

    while (1) {
        int opcao = -1;
        printf("\n==== SIG-Saude - Menu inicial ====\n");
        printf("1 - Login\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 0) break;

        if (opcao == 1) {
            char tipo[32];
            int idUsuario = 0;
            if (fazerLogin(db, tipo, sizeof(tipo), &idUsuario)) {
                if (strcmp(tipo, "admin") == 0) {
                    menuAdmin(db);
                } else if (strcmp(tipo, "recepcao") == 0) {
                    menuRecepcao(db);
                } else if (strcmp(tipo, "medico") == 0) {
                    menuMedico(db, idUsuario);
                } else {
                    printf("Tipo de usuario desconhecido: %s\n", tipo);
                }
            }
        } else {
            printf("Opcao invalida.\n");
        }
    }

    sqlite3_close(db);
    printf("Programa encerrado.\n");
    return 0;
}

/* menus simples */

int menuAdmin(sqlite3 *db) {
    int op;
    do {
        printf("\n--- MENU ADMIN ---\n");
        printf("1 - Cadastrar usuario\n");
        printf("2 - Listar usuarios\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        switch(op) {
            case 1: cadastrarUsuario(db); break;
            case 2: listarUsuarios(db); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while(op != 0);
    return 0;
}

int menuRecepcao(sqlite3 *db) {
    int op;
    do {
        printf("\n--- MENU RECEPCAO ---\n");
        printf("1 - Cadastrar paciente\n");
        printf("2 - Cadastrar medico\n");
        printf("3 - Agendar consulta\n");
        printf("4 - Listar pacientes\n");
        printf("0 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        switch(op) {
            case 1: cadastrarPaciente(db); break;
            case 2: cadastrarMedico(db); break;
            case 3: agendarConsulta(db); break;
            case 4: listarPacientes(db); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while(op != 0);
    return 0;
}

void menuMedico(sqlite3 *db, int idMedico) {
    int op;
    do {
        printf("\n--- MENU MEDICO ---\n");
        printf("1 - Consultas do dia (listar)\n");
        printf("2 - Todas as consultas (do medico)\n");
        printf("3 - Gerar receita\n");
        printf("0 - Logout\n");
        printf("Opcao: ");
        scanf("%d", &op);
        switch(op) {
            case 1: listarConsultasDia(db); break;
            case 2: listarConsultasMedico(db, idMedico); break;
            case 3: gerarReceitaArquivo(); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while(op != 0);
}
