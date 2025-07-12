#include "../include/usuario.h"
#include "../include/utilidades.h"
#include "../include/catalogo.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

Nodoarbol* Usuarios = nullptr;

Nodoarbol *crearNodo(Usuario valor)
{
    Nodoarbol *nuevo = new Nodoarbol;
    nuevo->dato = valor;
    nuevo->izquierda = nullptr;
    nuevo->derecha = nullptr;
    return nuevo;
}

Nodoarbol *insertar(Nodoarbol *&raiz, Usuario &usuario)
{
    if (raiz == nullptr)
    {
        raiz = crearNodo(usuario);
        return raiz;
    }

    if (usuario.usuario < raiz->dato.usuario)
    {
        raiz->izquierda = insertar(raiz->izquierda, usuario);
    }
    else if (usuario.usuario > raiz->dato.usuario)
    {
        raiz->derecha = insertar(raiz->derecha, usuario);
    }

    return raiz;
}

Nodoarbol *buscar(Nodoarbol *raiz, const std::string &usuario)
{
    if (raiz == nullptr || raiz->dato.usuario == usuario)
    {
        return raiz;
    }

    if (usuario < raiz->dato.usuario)
    {
        return buscar(raiz->izquierda, usuario);
    }
    else
    {
        return buscar(raiz->derecha, usuario);
    }
}

bool verificarPassword(Nodoarbol *nodo, const std::string &password)
{
    return nodo && nodo->dato.password == password;
}

void imprimirUsuario(Usuario &usuario)
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered("Felicidades, nuevo usuario registrado.");
    std::cout << std::string(50, '=') << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Nombre: " << usuario.nombre << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Apellido: " << usuario.apellido << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Usuario: " << usuario.usuario << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "ID: " << usuario.id << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Password: " << usuario.password << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void seleccionarPreferencias(Usuario *usuario)
{
    clearScreen();
    encabezado("Seleccion de Marcas Preferidas");

    ListaString marcas = obtenerMarcasUnicas();

    std::string entrada;

    while (true)
    {
        int i = 1;
        seccion("Marcas Disponibles");
        Nodolista* actual = marcas;
        while (actual != nullptr)
        {
            std::cout << i << ".- " << actual->dato << std::endl;
            i++;
            actual = actual->siguiente;
        }

        seccion("Instrucciones");
        std::cout << "Ingrese los numeros de las marcas que le interesan (ej: 1 3 5): ";
        std::getline(std::cin, entrada);

        std::istringstream iss(entrada);
        int num;
        bool invalido = false;

        usuario->preferencias = nullptr;

        while (iss >> num)
        {
            int j = 1;
            Nodolista* marcaActual = marcas;
            bool encontrado = false;
            while(marcaActual != nullptr) {
                if (j == num) {
                    if (!existeEnLista(usuario->preferencias, marcaActual->dato))
                    {
                        insertarLista(usuario->preferencias, marcaActual->dato);
                    }
                    encontrado = true;
                    break;
                }
                j++;
                marcaActual = marcaActual->siguiente;
            }
            if (!encontrado) {
                invalido = true;
            }
        }

        if (!invalido && usuario->preferencias != nullptr)
        {
            seccion("Marcas Preferidas Guardadas");
            Nodolista *temp = usuario->preferencias;
            while (temp != nullptr)
            {
                std::cout << "- " << temp->dato << "\n";
                temp = temp->siguiente;
            }
            pausarConsola();
            break; // Salir del bucle de marcas
        }
        else
        {
            seccion("Error");
            std::cout << "Entrada invalida. Intente nuevamente.\n";
            pausarConsola();
        }
    }

    // SELECCIÓN DE CATEGORÍAS
    clearScreen();
    encabezado("Seleccion de Categorias Preferidas");
    ListaString categorias = obtenerCategoriasUnicas();

    while (true)
    {
        int i = 1;
        seccion("Categorias Disponibles");
        Nodolista* actual = categorias;
        while (actual != nullptr)
        {
            std::cout << i << ".- " << actual->dato << std::endl;
            i++;
            actual = actual->siguiente;
        }

        seccion("Instrucciones");
        std::cout << "Ingrese los numeros de las categorias que le interesan (ej: 1 3 5): ";
        std::getline(std::cin, entrada);

        std::istringstream iss(entrada);
        int num;
        bool invalido = false;

        usuario->categoriasPreferidas = nullptr;

        while (iss >> num)
        {
            int j = 1;
            Nodolista* catActual = categorias;
            bool encontrado = false;
            while(catActual != nullptr) {
                if (j == num) {
                    if (!existeEnLista(usuario->categoriasPreferidas, catActual->dato))
                    {
                        insertarLista(usuario->categoriasPreferidas, catActual->dato);
                    }
                    encontrado = true;
                    break;
                }
                j++;
                catActual = catActual->siguiente;
            }
            if (!encontrado) {
                invalido = true;
            }
        }

        if (!invalido && usuario->categoriasPreferidas != nullptr)
        {
            seccion("Categorias Preferidas Guardadas");
            Nodolista *temp = usuario->categoriasPreferidas;
            while (temp != nullptr)
            {
                std::cout << "- " << temp->dato << "\n";
                temp = temp->siguiente;
            }
            pausarConsola();
            return;
        }
        else
        {
            seccion("Error");
            std::cout << "Entrada invalida. Intente nuevamente.\n";
            pausarConsola();
        }
    }
}

void ComandoRegistrarUsuario()
{
    clearScreen();
    encabezado("Registro de usuario");

    Usuario nuevo;
    bool cancelado = false;

    auto validarCampo = [](const std::string &valor, const std::string &campo) -> bool
    {
        if (valor.empty())
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "ERROR: El " << campo << " no puede estar vacio\n";
            std::cout << std::string(50, '-') << std::endl;
            return false;
        }
        return true;
    };

    std::cout << std::string(50, '=') << std::endl;

    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Nombre: " << std::endl;
        nuevo.nombre = leertexto();
        std::cout << std::string(50, '-') << std::endl;
    } while (!validarCampo(nuevo.nombre, "nombre"));

    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Nombre registrado: " << nuevo.nombre << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Apellido: " << std::endl;
        nuevo.apellido = leertexto();
        std::cout << std::string(50, '-') << std::endl;
    } while (!validarCampo(nuevo.apellido, "apellido"));

    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Apellido registrado: " << nuevo.apellido << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Usuario: " << std::endl;
        std::string input = leertexto();
        std::cout << std::string(50, '-') << std::endl;

        if (!validarCampo(input, "usuario"))
            continue;

        if (input.find(' ') != std::string::npos)
        {
            std::cout << "ERROR: El usuario no puede contener espacios\n";
            std::cout << std::string(50, '-') << std::endl;
            continue;
        }

        Nodoarbol *coincidencia = buscar(Usuarios, input);
        if (coincidencia != nullptr)
        {
            std::cout << std::string(50, '=') << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Usuario '" << input << "' ya registrado.\n";
            std::cout << "Desea intentar con otro usuario? (s/n): ";
            std::string continuar = leertexto();

            if (continuar == "n" || continuar == "N")
            {
                std::cout << "Registro de usuario cancelado\n";
                std::cout << std::string(50, '-') << std::endl;
                std::cout << std::string(50, '=') << std::endl;
                cancelado = true;
                break;
            }

            std::cout << std::string(50, '-') << std::endl;
            std::cout << std::string(50, '=') << std::endl;

            continue;
        }

        nuevo.usuario = input;
        break;

    } while (true);

    if (cancelado)
    {
        pausarConsola();
        return;
    }

    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Usuario registrado: " << nuevo.usuario << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Password (minimo 6 caracteres): ";
        nuevo.password = leertexto();
        std::cout << std::string(50, '-') << std::endl;
        if (nuevo.password.length() < 6)
        {
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "ERROR: La password debe tener minimo 6 caracteres\n";
            std::cout << std::string(50, '=') << std::endl;
        }
    } while (nuevo.password.length() < 6);

    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Password registrada: " << nuevo.password << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    nuevo.id = generarID();

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Generando ID de usuario." << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << std::string(50, '=') << std::endl;
    std::cout << "ID: " << nuevo.id << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    pausarConsola();

    nuevo.historial = nullptr;
    nuevo.carrito = nullptr;
    nuevo.listaDeseos = nullptr;
    nuevo.categoriasPreferidas = nullptr;


    seleccionarPreferencias(&nuevo);


    insertar(Usuarios, nuevo);

    clearScreen();
    imprimirUsuario(nuevo);
    pausarConsola();
}

Usuario *ComandoIngresarUsuario()
{
    do
    {
        clearScreen();
        encabezado("Ingresar a la plataforma.");

        std::cout << std::string(50, '=') << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Ingrese el usuario: ";
        std::string usuario = leertexto();
        Nodoarbol *ingreso = buscar(Usuarios, usuario);

        if (ingreso == nullptr)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            seccion("Usuario no encontrado");
            std::cout << "El usuario '" << usuario << "' no existe.\n";
            std::cout << "Desea probar con otro usuario? (s/n): ";
            std::string opcion = leertexto();
            std::cout << std::string(50, '=') << std::endl;

            if (opcion == "n" || opcion == "N")
            {
                std::cout << std::string(50, '=') << std::endl;
                return nullptr;
            }
            continue;
        }

        int intentos = 0;
        const int MAX_INTENTOS = 3;

        while (intentos < MAX_INTENTOS)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Ingrese la password: ";
            std::string password = leertexto();

            if (verificarPassword(ingreso, password))
            {
                clearScreen();
                encabezado("LOGIN EXITOSO");
                pausarConsola();
                return &(ingreso->dato);
            }
            else
            {
                intentos++;
                seccion("Password Incorrecta");
                std::cout << "Password incorrecta. Intento " << intentos << "/" << MAX_INTENTOS << "\n";

                if (intentos < MAX_INTENTOS)
                {
                    std::cout << "Desea intentar de nuevo? (s/n): ";
                    std::string reintentar = leertexto();

                    if (reintentar == "n" || reintentar == "N")
                    {
                        return nullptr;
                    }
                }
            }
        }

        seccion("Maximo de Intentos");
        std::cout << "Ha superado el maximo de intentos\n";
        pausarConsola();
        return nullptr;

    } while (true);
}
