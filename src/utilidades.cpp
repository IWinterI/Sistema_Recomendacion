#include "utilidades.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <cctype>
#include <limits>

const std::string CARACTERES_VALIDOS =
    "1234567890"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

std::string generarID()
{
    std::random_device rd;
    std::mt19937 generador(rd());
    std::uniform_int_distribution<int> distribucion(0, CARACTERES_VALIDOS.size() - 1);

    std::string id;
    for (int i = 0; i < 10; i++)
    {
        id += CARACTERES_VALIDOS[distribucion(generador)];
    }
    return id;
}

std::string aMinusculas(const std::string &texto)
{
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return resultado;
}

std::string leertexto()
{
    std::string entrada;
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore();
    }
    std::getline(std::cin, entrada);
    size_t inicio = entrada.find_first_not_of(" ");
    size_t fin = entrada.find_last_not_of(" ");
    if (inicio == std::string::npos)
    {
        return "";
    }
    return entrada.substr(inicio, fin - inicio + 1);
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausarConsola()
{
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void opcioninvalida(int min, int max)
{
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Opcion invalida." << std::endl;
    std::cout << "Por favor ingrese un numero entre (" << min << "-" << max << ")" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void printCentered(const std::string &text, int width)
{
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding > 0)
        std::cout << std::string(padding, ' ');
    std::cout << text << std::endl;
}

void encabezado(const std::string &titulo)
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(titulo);
    std::cout << std::string(50, '=') << std::endl;
}

void seccion(const std::string &titulo)
{
    std::cout << std::string(50, '-') << std::endl;
    printCentered(titulo);
    std::cout << std::string(50, '-') << std::endl;
}

void insertarLista(ListaString& lista, const std::string& valor)
{
    Nodolista *nuevo = new Nodolista;
    nuevo->dato = valor;
    nuevo->siguiente = nullptr;

    if (lista == nullptr)
    {
        lista = nuevo;
    }
    else
    {
        Nodolista *actual = lista;
        while (actual->siguiente != nullptr)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

bool existeEnLista(ListaString lista, const std::string& valor)
{
    Nodolista *actual = lista;
    while (actual != nullptr)
    {
        if (actual->dato == valor)
        {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

void insertarEnLista(ListaProducto& lista, const Producto& valor) {
    NodoProducto* nuevo = new NodoProducto();
    nuevo->dato = valor;
    nuevo->siguiente = nullptr;
    if (lista == nullptr) {
        lista = nuevo;
    } else {
        NodoProducto* actual = lista;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

int longitudLista(ListaProducto lista) {
    int count = 0;
    NodoProducto* actual = lista;
    while (actual != nullptr) {
        count++;
        actual = actual->siguiente;
    }
    return count;
}

Producto& obtenerElementoEn(ListaProducto lista, int indice) {
    NodoProducto* actual = lista;
    for (int i = 0; i < indice; ++i) {
        actual = actual->siguiente;
    }
    return actual->dato;
}

void barajarLista(ListaProducto& lista) {
    int n = longitudLista(lista);
    if (n > 1) {
        std::random_device rd;
        std::mt19937 gen(rd());
        for (int i = n - 1; i > 0; --i) {
            std::uniform_int_distribution<int> dist(0, i);
            int j = dist(gen);
            Producto temp = obtenerElementoEn(lista, i);
            obtenerElementoEn(lista, i) = obtenerElementoEn(lista, j);
            obtenerElementoEn(lista, j) = temp;
        }
    }
}

void barajarLista(ListaString& lista) {
    // Implementación similar si es necesaria, por ahora vacía
}

bool buscarEnSet(SetInt set, int valor) {
    NodoSetInt* actual = set;
    while (actual != nullptr) {
        if (actual->dato == valor) return true;
        actual = actual->siguiente;
    }
    return false;
}

void insertarEnSet(SetInt& set, int valor) {
    if (!buscarEnSet(set, valor)) {
        NodoSetInt* nuevo = new NodoSetInt{valor, nullptr};
        if (set == nullptr) {
            set = nuevo;
        } else {
            NodoSetInt* actual = set;
            while (actual->siguiente != nullptr) {
                actual->siguiente = nuevo;
            }
        }
    }
}

void incrementarEnMapa(MapaStringInt& mapa, const std::string& clave) {
    NodoMapaStringInt* actual = mapa;
    while (actual != nullptr) {
        if (actual->clave == clave) {
            actual->valor++;
            return;
        }
        actual = actual->siguiente;
    }
    NodoMapaStringInt* nuevo = new NodoMapaStringInt{clave, 1, mapa};
    mapa = nuevo;
}

void incrementarEnMapa(MapaIntInt& mapa, int clave) {
    NodoMapaIntInt* actual = mapa;
    while (actual != nullptr) {
        if (actual->clave == clave) {
            actual->valor++;
            return;
        }
        actual = actual->siguiente;
    }
    NodoMapaIntInt* nuevo = new NodoMapaIntInt{clave, 1, mapa};
    mapa = nuevo;
}

bool mapaEstaVacio(MapaStringInt mapa) {
    return mapa == nullptr;
}

bool mapaEstaVacio(MapaIntInt mapa) {
    return mapa == nullptr;
}
