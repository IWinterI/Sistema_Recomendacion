#pragma once

#include "estructuras.h"

// --- Declaraciones de Funciones de Usuario ---

Nodoarbol* crearNodo(Usuario valor);
Nodoarbol* insertar(Nodoarbol*& raiz, Usuario& usuario);
Nodoarbol* buscar(Nodoarbol* raiz, const std::string& usuario);
bool verificarPassword(Nodoarbol* nodo, const std::string& password);
void ComandoRegistrarUsuario();
Usuario* ComandoIngresarUsuario();
void imprimirUsuario(Usuario& usuario);
void seleccionarPreferencias(Usuario* usuario);

extern Nodoarbol* Usuarios;
