#include "interfaz.h"
#include "usuario.h"
#include "catalogo.h"
#include "recomendacion.h"
#include "utilidades.h"
#include <iostream>
#include <sstream>

void mostrarProductosPorCategoria(const std::string &categoria)
{
    ListaProducto productos = buscarPorCategoria(catalogoGlobal, categoria);
    std::cout << "\n=== " << categoria << " ===\n";
    NodoProducto* actual = productos;
    while (actual != nullptr)
    {
        std::cout << "ID: " << actual->dato.id << " - " << actual->dato.descripcion << "\n";
        actual = actual->siguiente;
    }
    std::cout << "------------------------\n";
}

void verDetallesProducto(int idProducto, Usuario *usuario)
{
    NodoProducto* actual = catalogoGlobal;
    while (actual != nullptr)
    {
        if (actual->dato.id == idProducto)
        {
            clearScreen();
            encabezado("Detalles del Producto");
            actual->dato.mostrar();

            std::string idStr = std::to_string(idProducto);
            if (!existeEnLista(usuario->historial, idStr))
            {
                insertarLista(usuario->historial, idStr);
            }

            seccion("Opciones Adicionales");
            std::cout << "1. Agregar al carrito\n";
            std::cout << "2. Agregar a lista de deseos\n";
            std::cout << "3. Volver\n";
            std::cout << "Seleccione una opcion: ";

            int opcion;
            std::cin >> opcion;
            std::cin.ignore();

            if (opcion == 1)
            {
                insertarLista(usuario->carrito, idStr);
                std::cout << "\nProducto agregado al carrito!\n";
                pausarConsola();
            }
            else if (opcion == 2)
            {
                insertarLista(usuario->listaDeseos, idStr);
                std::cout << "\nProducto agregado a lista de deseos!\n";
                pausarConsola();
            }

            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "Producto no encontrado.\n";
    pausarConsola();
}

void verCarrito(Usuario *usuario)
{
    clearScreen();
    encabezado("Carrito de Compras");

    if (usuario->carrito == nullptr)
    {
        seccion("Carrito Vacio");
        std::cout << "No hay productos en el carrito.\n";
        pausarConsola();
        return;
    }

    double total = 0.0;
    Nodolista *actualCarrito = usuario->carrito;
    while (actualCarrito != nullptr)
    {
        int id = std::stoi(actualCarrito->dato);
        NodoProducto* actualProd = catalogoGlobal;
        while(actualProd != nullptr)
        {
            if (actualProd->dato.id == id)
            {
                seccion(actualProd->dato.descripcion);
                std::cout << "ID: " << actualProd->dato.id << "\n";
                std::cout << "Precio: $" << std::fixed << std::setprecision(2) << actualProd->dato.precio << "\n";
                total += actualProd->dato.precio;
                break;
            }
            actualProd = actualProd->siguiente;
        }
        actualCarrito = actualCarrito->siguiente;
    }

    seccion("Total");
    std::cout << "Total a pagar: $" << std::fixed << std::setprecision(2) << total << "\n";

    seccion("Opciones");
    std::cout << "1. Realizar compra\n";
    std::cout << "2. Vaciar carrito\n";
    std::cout << "3. Volver\n";
    std::cout << "Seleccione una opcion: ";

    int opcion;
    std::cin >> opcion;
    std::cin.ignore();

    if (opcion == 1)
    {
        while (usuario->carrito != nullptr)
        {
            Nodolista *temp = usuario->carrito;
            usuario->carrito = usuario->carrito->siguiente;
            delete temp;
        }
        seccion("Compra Realizada");
        std::cout << "¡Gracias por su compra!\n";
        pausarConsola();
    }
    else if (opcion == 2)
    {
        while (usuario->carrito != nullptr)
        {
            Nodolista *temp = usuario->carrito;
            usuario->carrito = usuario->carrito->siguiente;
            delete temp;
        }
        seccion("Carrito Vaciado");
        std::cout << "El carrito ha sido vaciado.\n";
        pausarConsola();
    }
}

void verListaDeseos(Usuario *usuario)
{
    clearScreen();
    encabezado("Lista de Deseos");

    if (usuario->listaDeseos == nullptr)
    {
        seccion("Lista Vacia");
        std::cout << "No hay productos en la lista de deseos.\n";
        pausarConsola();
        return;
    }

    Nodolista *actualDeseos = usuario->listaDeseos;
    while (actualDeseos != nullptr)
    {
        int id = std::stoi(actualDeseos->dato);
        NodoProducto* actualProd = catalogoGlobal;
        while(actualProd != nullptr)
        {
            if (actualProd->dato.id == id)
            {
                seccion(actualProd->dato.descripcion);
                std::cout << "ID: " << actualProd->dato.id << "\n";
                std::cout << "Precio: $" << std::fixed << std::setprecision(2) << actualProd->dato.precio << "\n";
                break;
            }
            actualProd = actualProd->siguiente;
        }
        actualDeseos = actualDeseos->siguiente;
    }

    seccion("Opciones");
    std::cout << "1. Vaciar lista de deseos\n";
    std::cout << "2. Volver\n";
    std::cout << "Seleccione una opcion: ";

    int opcion;
    std::cin >> opcion;
    std::cin.ignore();

    if (opcion == 1)
    {
        while (usuario->listaDeseos != nullptr)
        {
            Nodolista *temp = usuario->listaDeseos;
            usuario->listaDeseos = usuario->listaDeseos->siguiente;
            delete temp;
        }
        seccion("Lista Vaciada");
        std::cout << "La lista de deseos ha sido vaciada.\n";
        pausarConsola();
    }
}

void verHistorial(Usuario *usuario)
{
    clearScreen();
    encabezado("Historial de Productos Visualizados");

    if (usuario->historial == nullptr)
    {
        seccion("Historial Vacio");
        std::cout << "No ha visto ningun producto aun.\n";
        pausarConsola();
        return;
    }

    Nodolista *actualHistorial = usuario->historial;
    while (actualHistorial != nullptr)
    {
        int id = std::stoi(actualHistorial->dato);
        NodoProducto* actualProd = catalogoGlobal;
        while(actualProd != nullptr)
        {
            if (actualProd->dato.id == id)
            {
                seccion(actualProd->dato.descripcion);
                std::cout << "ID: " << actualProd->dato.id << "\n";
                std::cout << "Categoria: " << actualProd->dato.categoria << "\n";
                std::cout << "Marca: " << actualProd->dato.marca << "\n";
                std::cout << "Precio: $" << std::fixed << std::setprecision(2) << actualProd->dato.precio << "\n";
                break;
            }
            actualProd = actualProd->siguiente;
        }
        actualHistorial = actualHistorial->siguiente;
    }

    pausarConsola();
}

void mostrarMenuUsuario(Usuario *usuario)
{
    int opcion;
    bool salir = false;
    ListaString categorias = obtenerCategoriasUnicas();
    ListaString marcas = obtenerMarcasUnicas();

    while (!salir)
    {
        clearScreen();
        encabezado("Bienvenido, " + usuario->nombre);

        seccion("Menu Principal");
        std::cout << "1. Ver catalogo de productos\n";
        std::cout << "2. Ver productos recomendados\n";
        std::cout << "3. Realizar busqueda\n";
        std::cout << "4. Carrito de Compras\n";
        std::cout << "5. Lista de Deseos\n";
        std::cout << "6. Ver historial de productos\n";
        std::cout << "7. Cerrar sesion\n";
        seccion("Seleccion");
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion)
        {
        case 1:
        {
            clearScreen();
            encabezado("Catalogo de Productos");
            Nodolista* actualCat = categorias;
            while (actualCat != nullptr)
            {
                mostrarProductosPorCategoria(actualCat->dato);
                actualCat = actualCat->siguiente;
            }

            seccion("Detalles de Producto");
            std::cout << "Ingrese el ID del producto para ver detalles (0 para volver): ";
            int idProducto;
            std::cin >> idProducto;
            std::cin.ignore();

            if (idProducto != 0)
            {
                verDetallesProducto(idProducto, usuario);
            }
            break;
        }
        case 2:
        {
            clearScreen();
            encabezado("Productos Recomendados");

            Recomendaciones rec = generarRecomendaciones(usuario);

            if (rec.porMarcasPreferidas == nullptr &&
                rec.porOtrasMarcasFrecuentes == nullptr &&
                rec.porCategoriaPreferida == nullptr &&
                rec.porCategoriaFrecuente == nullptr &&
                rec.porCalidad == nullptr)
            {
                seccion("Sin Recomendaciones");
                std::cout << "No hay recomendaciones disponibles. Vea algunos productos primero.\n";
            }
            else
            {
                if (rec.porMarcasPreferidas != nullptr)
                {
                    seccion("Recomendados por tus marcas preferidas");
                    NodoProducto* actualProd = rec.porMarcasPreferidas;
                    while(actualProd != nullptr) {
                        std::cout << "ID: " << actualProd->dato.id << " - " << actualProd->dato.descripcion;
                        std::cout << " (Marca: " << actualProd->dato.marca << ")\n";
                        actualProd = actualProd->siguiente;
                    }
                }

                if (rec.porOtrasMarcasFrecuentes != nullptr)
                {
                    seccion("Recomendados por otras marcas frecuentes");
                    NodoProducto* actualProd = rec.porOtrasMarcasFrecuentes;
                    while(actualProd != nullptr) {
                        std::cout << "ID: " << actualProd->dato.id << " - " << actualProd->dato.descripcion;
                        std::cout << " (Marca: " << actualProd->dato.marca << ")\n";
                        actualProd = actualProd->siguiente;
                    }
                }

                if (rec.porCategoriaPreferida != nullptr)
                {
                    seccion("Recomendados por tus categorias preferidas");
                    NodoProducto* actualProd = rec.porCategoriaPreferida;
                    while(actualProd != nullptr) {
                        std::cout << "ID: " << actualProd->dato.id << " - " << actualProd->dato.descripcion;
                        std::cout << " (Categoria: " << actualProd->dato.categoria << ")\n";
                        actualProd = actualProd->siguiente;
                    }
                }

                if (rec.porCategoriaFrecuente != nullptr)
                {
                    seccion("Recomendados por tus categorias mas visualizadas");
                    NodoProducto* actualProd = rec.porCategoriaFrecuente;
                    while(actualProd != nullptr) {
                        std::cout << "ID: " << actualProd->dato.id << " - " << actualProd->dato.descripcion;
                        std::cout << " (Categoria: " << actualProd->dato.categoria << ")\n";
                        actualProd = actualProd->siguiente;
                    }
                }

                if (rec.porCalidad != nullptr)
                {
                    seccion("Recomendados por calidad similar");
                    NodoProducto* actualProd = rec.porCalidad;
                    while(actualProd != nullptr) {
                        std::cout << "ID: " << actualProd->dato.id << " - " << actualProd->dato.descripcion;
                        std::cout << " (Calidad: " << std::string(actualProd->dato.calidad, '*') << ")\n";
                        actualProd = actualProd->siguiente;
                    }
                }
            }

            if (rec.porMarcasPreferidas != nullptr ||
                rec.porOtrasMarcasFrecuentes != nullptr ||
                rec.porCategoriaPreferida != nullptr ||
                rec.porCategoriaFrecuente != nullptr ||
                rec.porCalidad != nullptr)
            {
                seccion("Detalles de Producto");
                std::cout << "Ingrese el ID del producto para ver detalles (0 para volver): ";
                int idProducto;
                std::cin >> idProducto;
                std::cin.ignore();

                if (idProducto != 0)
                {
                    verDetallesProducto(idProducto, usuario);
                }
            }
            else
            {
                pausarConsola();
            }
            break;
        }
        case 3:
        {
            int opcionBusqueda;
            bool volver = false;

            while (!volver)
            {
                clearScreen();
                encabezado("Buscar Productos");
                seccion("Opciones de Busqueda");
                std::cout << "1. Buscar por categoria\n";
                std::cout << "2. Buscar por rango de precios\n";
                std::cout << "3. Buscar por marca\n";
                std::cout << "4. Buscar por descripcion\n";
                std::cout << "5. Volver\n";
                seccion("Seleccion");
                std::cout << "Seleccione una opcion: ";
                std::cin >> opcionBusqueda;
                std::cin.ignore();

                ListaProducto resultados = nullptr;

                switch (opcionBusqueda)
                {
                case 1:
                {
                    seccion("Categorias Disponibles");
                    Nodolista* actualCat = categorias;
                    while(actualCat != nullptr) {
                        std::cout << "- " << actualCat->dato << "\n";
                        actualCat = actualCat->siguiente;
                    }
                    seccion("Busqueda");
                    std::cout << "Ingrese categoria: ";
                    std::string categoria;
                    std::getline(std::cin, categoria);
                    resultados = buscarPorCategoria(catalogoGlobal, categoria);
                    break;
                }
                case 2:
                {
                    seccion("Rango de Precios");
                    double min, max;
                    std::cout << "Ingrese precio minimo: ";
                    std::cin >> min;
                    std::cout << "Ingrese precio maximo: ";
                    std::cin >> max;
                    std::cin.ignore();
                    resultados = buscarPorRangoPrecios(catalogoGlobal, min, max);
                    break;
                }
                case 3:
                {
                    seccion("Marcas Disponibles");
                    Nodolista* actualMarca = marcas;
                    while(actualMarca != nullptr) {
                        std::cout << "- " << actualMarca->dato << "\n";
                        actualMarca = actualMarca->siguiente;
                    }
                    seccion("Busqueda");
                    std::cout << "Ingrese marca: ";
                    std::string marca;
                    std::getline(std::cin, marca);
                    resultados = buscarPorMarca(catalogoGlobal, marca);
                    break;
                }
                case 4:
                {
                    seccion("Busqueda por Descripcion");
                    std::cout << "Ingrese palabra clave (ej: telefono, laptop, auriculares): ";
                    std::string clave;
                    std::getline(std::cin, clave);
                    resultados = buscarPorDescripcion(catalogoGlobal, clave);
                    break;
                }
                case 5:
                    volver = true;
                    break;
                default:
                    opcioninvalida(1, 5);
                    pausarConsola();
                    continue;
                }

                if (opcionBusqueda >= 1 && opcionBusqueda <= 4)
                {
                    clearScreen();
                    encabezado("Resultados de la busqueda");

                    if (resultados == nullptr)
                    {
                        seccion("Sin Resultados");
                        std::cout << "No se encuentra ninguna coincidencia.\n";
                    }
                    else
                    {
                        seccion("Productos Encontrados");
                        NodoProducto* actualProd = resultados;
                        while(actualProd != nullptr) {
                            std::cout << "ID: " << actualProd->dato.id << " - " << actualProd->dato.descripcion << "\n";
                            actualProd = actualProd->siguiente;
                        }
                    }

                    seccion("Detalles de Producto");
                    std::cout << "\nIngrese el ID del producto para ver detalles (0 para volver): ";
                    int idProducto;
                    std::cin >> idProducto;
                    std::cin.ignore();

                    if (idProducto != 0)
                    {
                        verDetallesProducto(idProducto, usuario);
                    }
                }
            }
            break;
        }
        case 4:
            verCarrito(usuario);
            break;
        case 5:
            verListaDeseos(usuario);
            break;
        case 6:
            verHistorial(usuario);
            break;
        case 7:
            salir = true;
            clearScreen();
            encabezado("Sesion finalizada");
            pausarConsola();
            break;
        default:
            opcioninvalida(1, 7);
            pausarConsola();
            break;
        }
    }
}

void Mainmenu()
{
    int opcion;

    do
    {
        clearScreen();
        encabezado("Bienvenid@ a Quantum Store.");

        seccion("Menu Principal");
        std::cout << "1. Registrar un nuevo usuario\n";
        std::cout << "2. Ingresar con un usuario existente\n";
        std::cout << "3. Salir\n";
        seccion("Seleccion");
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion)
        {
        case 1:
            ComandoRegistrarUsuario();
            break;
        case 2:
        {
            Usuario *usuario = ComandoIngresarUsuario();
            if (usuario != nullptr)
            {
                mostrarMenuUsuario(usuario);
            }
            break;
        }
        case 3:
            return;
        default:
            opcioninvalida(1, 3);
            pausarConsola();
            break;
        }
    } while (true);
}
