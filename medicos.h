    #ifndef MEDICOS_H
#define MEDICOS_H

#include "sqlite3.h"

void cadastrarMedico(sqlite3 *db);
void listarMedicos(sqlite3 *db);

#endif
