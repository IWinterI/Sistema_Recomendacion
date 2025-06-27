#pragma once

#include "estructuras.h"

// --- Declaraciones de Funciones de Interfaz ---

void mostrarMenuUsuario(Usuario *usuario);
void verCarrito(Usuario *usuario);
void verListaDeseos(Usuario *usuario);
void verHistorial(Usuario *usuario);
void verDetallesProducto(int idProducto, Usuario *usuario);
void mostrarProductosPorCategoria(const std::string &categoria);
void Mainmenu();
