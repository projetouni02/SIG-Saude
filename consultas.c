#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include "consultas.h"

void agendarConsulta(sqlite3 *db) {
    int idPac, idMed;
    char data[30], hora[30];
    char sql[256];
    char *err = NULL;

    printf("ID do paciente: ");
    scanf("%d", &idPac);
    printf("ID do medico: ");
    scanf("%d", &idMed);
    getchar();
    printf("Data (DD/MM/AAAA): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = 0;
    printf("Horario (HH:MM): ");
    fgets(hora, sizeof(hora), stdin);
    hora[strcspn(hora, "\n")] = 0;

    snprintf(sql, sizeof(sql),
        "INSERT INTO consultas (id_paciente, id_medico, data, hora) VALUES (%d, %d, '%s', '%s');",
        idPac, idMed, data, hora);

    if (sqlite3_exec(db, sql, NULL, NULL, &err) != SQLITE_OK) {
        printf("Erro agendar consulta: %s\n", err ? err : "desconhecido");
        if (err) sqlite3_free(err);
    } else {
        printf("Consulta agendada.\n");
    }
}

void listarConsultasMedico(sqlite3 *db, int idMedico) {
    char sql[256];
    sqlite3_stmt *stmt;
    int rc;

    snprintf(sql, sizeof(sql),
        "SELECT c.id, p.nome, c.data, c.hora FROM consultas c "
        "LEFT JOIN pacientes p ON p.id = c.id_paciente "
        "WHERE c.id_medico = %d ORDER BY c.data;", idMedico);

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) { printf("Erro SQL\n"); return; }

    printf("\nID | Paciente                | Data       | Hora\n------------------------------------------------\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%-2d | %-22s | %s | %s\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_text(stmt, 3));
    }
    sqlite3_finalize(stmt);
}

void listarConsultasDia(sqlite3 *db) {
    const char *sql =
        "SELECT c.id, p.nome, m.nome, c.data, c.hora FROM consultas c "
        "LEFT JOIN pacientes p ON p.id = c.id_paciente "
        "LEFT JOIN medicos m ON m.id = c.id_medico "
        "ORDER BY c.data;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) { printf("Erro SQL listar consultas dia\n"); return; }

    printf("\nID | Paciente                | Medico                 | Data       | Hora\n---------------------------------------------------------------------\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("%-2d | %-22s | %-21s | %s | %s\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_text(stmt, 3),
            sqlite3_column_text(stmt, 4));
    }
    sqlite3_finalize(stmt);
}
