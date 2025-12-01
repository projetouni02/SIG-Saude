#ifndef USUARIOS_H
#define USUARIOS_H

#include "sqlite3.h"

void cadastrarUsuario(sqlite3 *db);
void listarUsuarios(sqlite3 *db);

#endif
