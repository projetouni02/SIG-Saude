#ifndef CONSULTAS_H
#define CONSULTAS_H

#include "sqlite3.h"

void agendarConsulta(sqlite3 *db);
void listarConsultasMedico(sqlite3 *db, int idMedico);
void listarConsultasDia(sqlite3 *db);

#endif
