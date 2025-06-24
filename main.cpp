#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <set>
#include <memory>
#include <limits>
#include <random>
#include <sstream>
#include <map>
#include <cmath>

//**Estructuras**

//Estructuras de usuario
struct Nodolista
{
    std::string dato;
    Nodolista *siguiente;
};

struct Usuario
{
    std::string nombre;
    std::string apellido;
    std::string id;
    std::string usuario;
    std::string password;
    Nodolista *preferencias;
    Nodolista *historial;
};

struct Nodoarbol
{
    Usuario dato;
    Nodoarbol *izquierda;
    Nodoarbol *derecha;
};

//Estructura de productos
struct Producto {
    std::string descripcion;
    int id;
    std::string marca;
    double precio;
    int calidad;
    std::string categoria;

    // Constructor con validación de calidad
    Producto(std::string desc = "", int id = 0, std::string marca = "",
             double precio = 0.0, int calidad = 1, std::string categoria = "")
        : descripcion(desc), id(id), marca(marca), precio(precio), categoria(categoria)
    {
        // Validar y ajustar la calidad
        if (calidad < 1) this->calidad = 1;
        else if (calidad > 5) this->calidad = 5;
        else this->calidad = calidad;
    }

    // Función para mostrar información del producto
    void mostrar() const {
        std::cout << "ID: " << id
                  << "\nProducto: " << descripcion
                  << "\nCategoria: " << categoria
                  << "\nMarca: " << marca
                  << "\nPrecio: $" << std::fixed << std::setprecision(2) << precio
                  << "\nCalidad: " << std::string(calidad, '*')
                  << " (" << calidad << "/5)\n\n";
    }
};

/* Declaraciones globales */

// Registros de usuarios
Nodoarbol *Usuarios = nullptr;

// Catálogo global de productos
std::vector<Producto> catalogoGlobal;

// Caracteres para ids
const std::string CARACTERES_VALIDOS =
    "1234567890"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "!#$%&/()=?Âˇ',.-;:_";

//**Funciones principales de la gestion de usuarios**

// Imprimir centrado
void printCentered(const std::string &text, int width = 50)
{
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding > 0)
        std::cout << std::string(padding, ' ');
    std::cout << text << std::endl;
}

// Funciones para arbol de busqueda
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

// Generar id de los usuarios
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

//**Funciones de utilidades**
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

void encabezado(const std::string &titulo)
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(titulo);
    std::cout << std::string(50, '=') << std::endl;
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

//**Funciones para productos**
std::vector<Producto> generarCatalogo() {
    return {
        {"iPhone 15 Pro", 1001, "Apple", 999.99, 5, "Smartphones"},
        {"Galaxy S24 Ultra", 1002, "Samsung", 1199.99, 5, "Smartphones"},
        {"Pixel 8 Pro", 1003, "Google", 899.00, 4, "Smartphones"},
        {"Xperia 1 V", 1004, "Sony", 1299.99, 4, "Smartphones"},
        {"OnePlus 12", 1005, "OnePlus", 799.99, 4, "Smartphones"},
        {"Redmi Note 13 Pro", 1006, "Xiaomi", 349.99, 3, "Smartphones"},
        {"ROG Phone 7", 1007, "ASUS", 999.00, 4, "Smartphones"},
        {"Moto Edge 40", 1008, "Motorola", 599.99, 3, "Smartphones"},
        {"Nord N30", 1009, "OnePlus", 299.99, 3, "Smartphones"},
        {"Galaxy A54", 1010, "Samsung", 449.99, 4, "Smartphones"},
        {"MacBook Pro 16\" M2", 2001, "Apple", 2499.00, 5, "Laptops"},
        {"XPS 15 OLED", 2002, "Dell", 2199.99, 5, "Laptops"},
        {"ThinkPad X1 Carbon", 2003, "Lenovo", 1899.00, 4, "Laptops"},
        {"ROG Zephyrus G14", 2004, "ASUS", 1499.99, 4, "Laptops"},
        {"Spectre x360", 2005, "HP", 1399.99, 4, "Laptops"},
        {"Surface Laptop 5", 2006, "Microsoft", 1299.00, 4, "Laptops"},
        {"IdeaPad Slim 5", 2007, "Lenovo", 799.99, 3, "Laptops"},
        {"Swift 3", 2008, "Acer", 699.00, 3, "Laptops"},
        {"Galaxy Book3 Ultra", 2009, "Samsung", 2299.99, 5, "Laptops"},
        {"Chromebook 314", 2010, "Acer", 349.99, 3, "Laptops"},
        {"WH-1000XM5", 3001, "Sony", 399.99, 5, "Audio"},
        {"QuietComfort Ultra", 3002, "Bose", 429.00, 5, "Audio"},
        {"AirPods Pro 2", 3003, "Apple", 249.00, 5, "Audio"},
        {"Galaxy Buds2 Pro", 3004, "Samsung", 229.99, 4, "Audio"},
        {"Soundcore Liberty 4", 3005, "Anker", 129.99, 4, "Audio"},
        {"HD 660S2", 3006, "Sennheiser", 499.95, 5, "Audio"},
        {"HomePod mini", 3007, "Apple", 99.99, 4, "Audio"},
        {"Sonos Era 300", 3008, "Sonos", 449.00, 5, "Audio"},
        {"JBL Flip 6", 3009, "JBL", 129.95, 4, "Audio"},
        {"HyperX Cloud III", 3010, "HP", 99.99, 4, "Audio"},
        {"Apple Watch Ultra 2", 4001, "Apple", 799.00, 5, "Wearables"},
        {"Galaxy Watch6 Classic", 4002, "Samsung", 429.99, 4, "Wearables"},
        {"Pixel Watch 2", 4003, "Google", 349.99, 4, "Wearables"},
        {"Garmin Forerunner 965", 4004, "Garmin", 599.99, 5, "Wearables"},
        {"Amazfit GTR 4", 4005, "Amazfit", 199.99, 4, "Wearables"},
        {"Pro Display XDR", 5001, "Apple", 4999.00, 5, "Monitores"},
        {"Odyssey Neo G9", 5002, "Samsung", 1799.99, 5, "Monitores"},
        {"UltraGear 45GR95QE", 5003, "LG", 1699.99, 4, "Monitores"},
        {"Alienware 34 QD-OLED", 5004, "Dell", 1199.99, 5, "Monitores"},
        {"ProArt PA329CV", 5005, "ASUS", 999.00, 4, "Monitores"},
        {"PlayStation 5", 6001, "Sony", 499.99, 5, "Gaming"},
        {"Xbox Series X", 6002, "Microsoft", 499.99, 5, "Gaming"},
        {"Nintendo Switch OLED", 6003, "Nintendo", 349.99, 4, "Gaming"},
        {"DualSense Edge", 6004, "Sony", 199.99, 4, "Gaming"},
        {"Xbox Elite Controller", 6005, "Microsoft", 179.99, 4, "Gaming"},
        {"Alpha 7 IV", 7001, "Sony", 2499.99, 5, "Fotografia"},
        {"EOS R6 Mark II", 7002, "Canon", 2499.00, 5, "Fotografia"},
        {"Z9", 7003, "Nikon", 5499.95, 5, "Fotografia"},
        {"GoPro Hero12 Black", 7004, "GoPro", 449.99, 4, "Fotografia"},
        {"DJI Mavic 3 Pro", 7005, "DJI", 2199.00, 5, "Fotografia"}
    };
}

std::string aMinusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return resultado;
}

//**Funciones para listas enlazadas**
void insertarLista(Nodolista*& lista, const std::string& valor) {
    Nodolista* nuevo = new Nodolista;
    nuevo->dato = valor;
    nuevo->siguiente = nullptr;

    if (lista == nullptr) {
        lista = nuevo;
    } else {
        Nodolista* actual = lista;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

bool existeEnLista(Nodolista* lista, const std::string& valor) {
    Nodolista* actual = lista;
    while (actual != nullptr) {
        if (actual->dato == valor) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

//**Funciones de búsqueda**
std::vector<Producto> buscarPorCategoria(const std::vector<Producto>& productos,
                                        const std::string& categoriaBuscada) {
    std::vector<Producto> resultados;
    std::string categoriaLower = aMinusculas(categoriaBuscada);

    for (const auto& prod : productos) {
        if (aMinusculas(prod.categoria) == categoriaLower) {
            resultados.push_back(prod);
        }
    }
    return resultados;
}

std::vector<Producto> buscarPorRangoPrecios(const std::vector<Producto>& productos,
                                           double precioMin, double precioMax) {
    std::vector<Producto> resultados;
    for (const auto& prod : productos) {
        if (prod.precio >= precioMin && prod.precio <= precioMax) {
            resultados.push_back(prod);
        }
    }
    return resultados;
}

std::vector<Producto> buscarPorMarca(const std::vector<Producto>& productos,
                                    const std::string& marcaBuscada) {
    std::vector<Producto> resultados;
    std::string marcaLower = aMinusculas(marcaBuscada);

    for (const auto& prod : productos) {
        if (aMinusculas(prod.marca) == marcaLower) {
            resultados.push_back(prod);
        }
    }
    return resultados;
}

std::vector<Producto> buscarPorDescripcion(const std::vector<Producto>& productos,
                                         const std::string& textoBuscado) {
    std::vector<Producto> resultados;
    std::string textoLower = aMinusculas(textoBuscado);

    for (const auto& prod : productos) {
        std::string descLower = aMinusculas(prod.descripcion);
        if (descLower.find(textoLower) != std::string::npos) {
            resultados.push_back(prod);
        }
    }
    return resultados;
}

//**Funciones para el sistema de recomendación**
std::vector<std::string> obtenerCategoriasUnicas() {
    std::set<std::string> categoriasSet;
    for (const auto& producto : catalogoGlobal) {
        categoriasSet.insert(producto.categoria);
    }
    return std::vector<std::string>(categoriasSet.begin(), categoriasSet.end());
}

std::vector<std::string> obtenerMarcasUnicas() {
    std::set<std::string> marcasSet;
    for (const auto& producto : catalogoGlobal) {
        marcasSet.insert(producto.marca);
    }
    return std::vector<std::string>(marcasSet.begin(), marcasSet.end());
}

void mostrarProductosPorCategoria(const std::string& categoria) {
    std::vector<Producto> productos = buscarPorCategoria(catalogoGlobal, categoria);
    std::cout << "\n=== " << categoria << " ===\n";
    for (const auto& producto : productos) {
        std::cout << "ID: " << producto.id << " - " << producto.descripcion << "\n";
    }
    std::cout << "------------------------\n";
}

void verDetallesProducto(int idProducto, Usuario* usuario) {
    for (const auto& producto : catalogoGlobal) {
        if (producto.id == idProducto) {
            clearScreen();
            producto.mostrar();

            std::string idStr = std::to_string(idProducto);
            if (!existeEnLista(usuario->historial, idStr)) {
                insertarLista(usuario->historial, idStr);
            }

            pausarConsola();
            return;
        }
    }
    std::cout << "Producto no encontrado.\n";
    pausarConsola();
}

// Nueva función para obtener estadísticas de usuario
struct EstadisticasUsuario {
    std::string categoriaFrecuente;
    std::string marcaFrecuente;
    int calidadFrecuente;
};

EstadisticasUsuario obtenerEstadisticasUsuario(Usuario* usuario) {
    EstadisticasUsuario stats;
    std::map<std::string, int> conteoCategorias;
    std::map<std::string, int> conteoMarcas;
    std::map<int, int> conteoCalidades;

    Nodolista* actual = usuario->historial;
    while (actual != nullptr) {
        int id = std::stoi(actual->dato);
        for (const auto& producto : catalogoGlobal) {
            if (producto.id == id) {
                conteoCategorias[producto.categoria]++;
                conteoMarcas[producto.marca]++;
                conteoCalidades[producto.calidad]++;
                break;
            }
        }
        actual = actual->siguiente;
    }

    // Obtener categoría más frecuente
    if (!conteoCategorias.empty()) {
        stats.categoriaFrecuente = std::max_element(
            conteoCategorias.begin(), conteoCategorias.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; }
        )->first;
    }

    // Obtener marca más frecuente
    if (!conteoMarcas.empty()) {
        stats.marcaFrecuente = std::max_element(
            conteoMarcas.begin(), conteoMarcas.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; }
        )->first;
    }

    // Obtener calidad más frecuente
    if (!conteoCalidades.empty()) {
        stats.calidadFrecuente = std::max_element(
            conteoCalidades.begin(), conteoCalidades.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; }
        )->first;
    }

    return stats;
}

// Función mejorada para generar recomendaciones
std::vector<Producto> generarRecomendaciones(Usuario* usuario) {
    std::vector<Producto> recomendados;
    EstadisticasUsuario stats = obtenerEstadisticasUsuario(usuario);

    // Filtrar productos no vistos
    auto filtrarNoVistos = [usuario](const std::vector<Producto>& productos) {
        std::vector<Producto> resultado;
        for (const auto& prod : productos) {
            std::string idStr = std::to_string(prod.id);
            if (!existeEnLista(usuario->historial, idStr)) {
                resultado.push_back(prod);
            }
        }
        return resultado;
    };

    // Recomendar por categoría
    if (!stats.categoriaFrecuente.empty()) {
        std::vector<Producto> productosCategoria = buscarPorCategoria(catalogoGlobal, stats.categoriaFrecuente);
        auto noVistos = filtrarNoVistos(productosCategoria);
        recomendados.insert(recomendados.end(), noVistos.begin(), noVistos.end());
    }

    // Recomendar por marca
    if (!stats.marcaFrecuente.empty()) {
        std::vector<Producto> productosMarca = buscarPorMarca(catalogoGlobal, stats.marcaFrecuente);
        auto noVistos = filtrarNoVistos(productosMarca);
        recomendados.insert(recomendados.end(), noVistos.begin(), noVistos.end());
    }

    // Recomendar por calidad
    if (stats.calidadFrecuente > 0) {
        std::vector<Producto> productosCalidad;
        for (const auto& prod : catalogoGlobal) {
            if (prod.calidad == stats.calidadFrecuente) {
                productosCalidad.push_back(prod);
            }
        }
        auto noVistos = filtrarNoVistos(productosCalidad);
        recomendados.insert(recomendados.end(), noVistos.begin(), noVistos.end());
    }

    // Eliminar duplicados
    std::set<int> idsVistos;
    std::vector<Producto> unicos;
    for (const auto& prod : recomendados) {
        if (idsVistos.find(prod.id) == idsVistos.end()) {
            idsVistos.insert(prod.id);
            unicos.push_back(prod);
        }
    }

    return unicos;
}

//**Menú de usuario mejorado**
void mostrarMenuUsuario(Usuario* usuario) {
    int opcion;
    bool salir = false;
    std::vector<std::string> categorias = obtenerCategoriasUnicas();
    std::vector<std::string> marcas = obtenerMarcasUnicas();

    while (!salir) {
        clearScreen();
        encabezado("Bienvenido, " + usuario->nombre);
        std::cout << "1. Ver catalogo de productos\n";
        std::cout << "2. Ver productos recomendados\n";
        std::cout << "3. Realizar busqueda\n";
        std::cout << "4. Cerrar sesion\n";
        std::cout << "------------------------\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1: {
                clearScreen();
                encabezado("Catalogo de Productos");
                for (const auto& categoria : categorias) {
                    mostrarProductosPorCategoria(categoria);
                }

                std::cout << "Ingrese el ID del producto para ver detalles (0 para volver): ";
                int idProducto;
                std::cin >> idProducto;
                std::cin.ignore();

                if (idProducto != 0) {
                    verDetallesProducto(idProducto, usuario);
                }
                break;
            }
            case 2: {
                clearScreen();
                encabezado("Productos Recomendados");

                EstadisticasUsuario stats = obtenerEstadisticasUsuario(usuario);
                std::vector<Producto> recomendaciones = generarRecomendaciones(usuario);

                if (recomendaciones.empty()) {
                    std::cout << "No hay recomendaciones disponibles. Vea algunos productos primero.\n";
                } else {
                    // Mostrar por categoría
                    if (!stats.categoriaFrecuente.empty()) {
                        std::cout << "\n--- Por tu categoria favorita: " << stats.categoriaFrecuente << " ---\n";
                        auto catRec = buscarPorCategoria(recomendaciones, stats.categoriaFrecuente);
                        for (const auto& prod : catRec) {
                            std::cout << "ID: " << prod.id << " - " << prod.descripcion << "\n";
                        }
                    }

                    // Mostrar por marca
                    if (!stats.marcaFrecuente.empty()) {
                        std::cout << "\n--- Por tu marca favorita: " << stats.marcaFrecuente << " ---\n";
                        auto marcaRec = buscarPorMarca(recomendaciones, stats.marcaFrecuente);
                        for (const auto& prod : marcaRec) {
                            std::cout << "ID: " << prod.id << " - " << prod.descripcion << "\n";
                        }
                    }

                    // Mostrar por calidad
                    if (stats.calidadFrecuente > 0) {
                        std::cout << "\n--- Por tu calidad favorita: " << stats.calidadFrecuente << " estrellas ---\n";
                        for (const auto& prod : recomendaciones) {
                            if (prod.calidad == stats.calidadFrecuente) {
                                std::cout << "ID: " << prod.id << " - " << prod.descripcion << "\n";
                            }
                        }
                    }
                }

                std::cout << "\nIngrese el ID del producto para ver detalles (0 para volver): ";
                int idProducto;
                std::cin >> idProducto;
                std::cin.ignore();

                if (idProducto != 0) {
                    verDetallesProducto(idProducto, usuario);
                }
                break;
            }
            case 3: {
                int opcionBusqueda;
                bool volver = false;

                while (!volver) {
                    clearScreen();
                    encabezado("Buscar Productos");
                    std::cout << "1. Buscar por categoria\n";
                    std::cout << "2. Buscar por rango de precios\n";
                    std::cout << "3. Buscar por marca\n";
                    std::cout << "4. Buscar por descripcion\n";
                    std::cout << "5. Volver\n";
                    std::cout << "------------------------\n";
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> opcionBusqueda;
                    std::cin.ignore();

                    std::vector<Producto> resultados;

                    switch (opcionBusqueda) {
                        case 1: {
                            std::cout << "Categorias disponibles:\n";
                            for (const auto& cat : categorias) {
                                std::cout << "- " << cat << "\n";
                            }
                            std::cout << "Ingrese categoria: ";
                            std::string categoria;
                            std::getline(std::cin, categoria);
                            resultados = buscarPorCategoria(catalogoGlobal, categoria);
                            break;
                        }
                        case 2: {
                            double min, max;
                            std::cout << "Ingrese precio minimo: ";
                            std::cin >> min;
                            std::cout << "Ingrese precio maximo: ";
                            std::cin >> max;
                            std::cin.ignore();
                            resultados = buscarPorRangoPrecios(catalogoGlobal, min, max);
                            break;
                        }
                        case 3: {
                            std::cout << "Marcas disponibles:\n";
                            for (const auto& marca : marcas) {
                                std::cout << "- " << marca << "\n";
                            }
                            std::cout << "Ingrese marca: ";
                            std::string marca;
                            std::getline(std::cin, marca);
                            resultados = buscarPorMarca(catalogoGlobal, marca);
                            break;
                        }
                        case 4: {
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

                    if (opcionBusqueda >= 1 && opcionBusqueda <= 4) {
                        clearScreen();
                        encabezado("Resultados de la busqueda");

                        if (resultados.empty()) {
                            std::cout << "No se encuentra ninguna coincidencia.\n";
                        } else {
                            for (const auto& prod : resultados) {
                                std::cout << "ID: " << prod.id << " - " << prod.descripcion << "\n";
                            }
                        }

                        std::cout << "\nIngrese el ID del producto para ver detalles (0 para volver): ";
                        int idProducto;
                        std::cin >> idProducto;
                        std::cin.ignore();

                        if (idProducto != 0) {
                            verDetallesProducto(idProducto, usuario);
                        }
                    }
                }
                break;
            }
            case 4:
                salir = true;
                clearScreen();
                encabezado("Sesion finalizada");
                pausarConsola();
                break;
            default:
                opcioninvalida(1, 4);
                pausarConsola();
                break;
        }
    }
}

//**Comandos de usuario**
void imprimirUsuario(Usuario &usuario) {
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
}

void ComandoRegistrarUsuario() {
    clearScreen();
    encabezado("Registro de usuario");

    Usuario nuevo;
    bool cancelado = false;

    // Validar campos
    auto validarCampo = [](const std::string &valor, const std::string &campo) -> bool {
        if (valor.empty()) {
            std::cout << "ERROR: El " << campo << " no puede estar vacio\n";
            return false;
        }
        return true;
    };

    // Nombre
    do {
        std::cout << "Nombre: ";
        nuevo.nombre = leertexto();
    } while (!validarCampo(nuevo.nombre, "nombre"));

    // Apellido
    do {
        std::cout << "Apellido: ";
        nuevo.apellido = leertexto();
    } while (!validarCampo(nuevo.apellido, "apellido"));

    // Usuario
    do {
        std::cout << "Usuario: ";
        std::string input = leertexto();

        if (!validarCampo(input, "usuario")) continue;

        if (input.find(' ') != std::string::npos) {
            std::cout << "ERROR: El usuario no puede contener espacios\n";
            continue;
        }

        Nodoarbol *coincidencia = buscar(Usuarios, input);
        if (coincidencia != nullptr) {
            std::cout << "Usuario '" << input << "' ya registrado.\n";
            std::cout << "Desea intentar con otro usuario? (s/n): ";
            std::string continuar = leertexto();

            if (continuar == "n" || continuar == "N") {
                std::cout << "Registro de usuario cancelado\n";
                cancelado = true;
                break;
            }
            continue;
        }

        nuevo.usuario = input;
        break;
    } while (true);

    if (cancelado) {
        pausarConsola();
        return;
    }

    // Contraseña
    do {
        std::cout << "Password (minimo 6 caracteres): ";
        nuevo.password = leertexto();
        if (nuevo.password.length() < 6) {
            std::cout << "ERROR: La password debe tener minimo 6 caracteres\n";
        }
    } while (nuevo.password.length() < 6);

    // Generar id
    nuevo.id = generarID();
    nuevo.historial = nullptr;
    nuevo.preferencias = nullptr;

    // Guardar usuario
    insertar(Usuarios, nuevo);

    // Mostrar resultado
    clearScreen();
    std::cout << "REGISTRO EXITOSO!\n";
    imprimirUsuario(nuevo);
    pausarConsola();
}

Usuario* ComandoIngresarUsuario() {
    do {
        clearScreen();
        encabezado("Ingresar a la plataforma.");

        std::cout << "Ingrese el usuario: ";
        std::string usuario = leertexto();
        Nodoarbol *ingreso = buscar(Usuarios, usuario);

        if (ingreso == nullptr) {
            std::cout << "El usuario '" << usuario << "' no existe.\n";
            std::cout << "Desea probar con otro usuario? (s/n): ";
            std::string opcion = leertexto();

            if (opcion == "n" || opcion == "N") {
                return nullptr;
            }
            continue;
        }

        int intentos = 0;
        const int MAX_INTENTOS = 3;

        while (intentos < MAX_INTENTOS) {
            std::cout << "Ingrese la password: ";
            std::string password = leertexto();

            if (verificarPassword(ingreso, password)) {
                clearScreen();
                encabezado("LOGIN EXITOSO");
                pausarConsola();
                return &(ingreso->dato);
            } else {
                intentos++;
                std::cout << "Password incorrecta. Intento " << intentos << "/" << MAX_INTENTOS << "\n";

                if (intentos < MAX_INTENTOS) {
                    std::cout << "Desea intentar de nuevo? (s/n): ";
                    std::string reintentar = leertexto();

                    if (reintentar == "n" || reintentar == "N") {
                        return nullptr;
                    }
                }
            }
        }

        std::cout << "Ha superado el maximo de intentos\n";
        pausarConsola();
        return nullptr;

    } while (true);
}

//**Menú principal**
void Mainmenu() {
    int opcion;

    do {
        clearScreen();
        encabezado("Bienvenid@ a Quantum Store.");
        std::cout << "1. Registrar un nuevo usuario\n";
        std::cout << "2. Ingresar con un usuario existente\n";
        std::cout << "3. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1:
                ComandoRegistrarUsuario();
                break;
            case 2: {
                Usuario* usuario = ComandoIngresarUsuario();
                if (usuario != nullptr) {
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

int main() {
    catalogoGlobal = generarCatalogo();
    Mainmenu();
    std::cout << "Gracias por visitar.\n";
    return 0;
}
