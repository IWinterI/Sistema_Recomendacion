#pragma once

#include "estructuras.h"
#include <string>

// --- Declaraciones de Funciones de Utilidades ---

std::string generarID();
std::string aMinusculas(const std::string &texto);
std::string leertexto();
void clearScreen();
void pausarConsola();
void opcioninvalida(int min, int max);
void printCentered(const std::string &text, int width = 50);
void encabezado(const std::string &titulo);
void seccion(const std::string &titulo);

// Funciones de listas
void insertarLista(ListaString& lista, const std::string& valor);
bool existeEnLista(ListaString lista, const std::string& valor);
void insertarEnLista(ListaProducto& lista, const Producto& valor);
int longitudLista(ListaProducto lista);
Producto& obtenerElementoEn(ListaProducto lista, int indice);
void barajarLista(ListaProducto& lista);
void barajarLista(ListaString& lista);

// Funciones de Set
bool buscarEnSet(SetInt set, int valor);
void insertarEnSet(SetInt& set, int valor);

// Funciones de Mapa
void incrementarEnMapa(MapaStringInt& mapa, const std::string& clave);
void incrementarEnMapa(MapaIntInt& mapa, int clave);
bool mapaEstaVacio(MapaStringInt mapa);
bool mapaEstaVacio(MapaIntInt mapa);
