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

// Crear un nuevo nodo
Nodoarbol *crearNodo(Usuario valor)
{
    Nodoarbol *nuevo = new Nodoarbol;
    nuevo->dato = valor;
    nuevo->izquierda = nullptr;
    nuevo->derecha = nullptr;

    return nuevo;
}

// Insertar un nuevo nodo
Nodoarbol *insertar(Nodoarbol *&raiz, Usuario &usuario)
{
    // caso base
    if (raiz == nullptr)
    {
        raiz = crearNodo(usuario);
        return raiz;
    }

    // caso recursivo
    if (usuario.usuario < raiz->dato.usuario)
    {
        raiz->izquierda = insertar(raiz->izquierda, usuario);
    }
    else if (usuario.usuario > raiz->dato.usuario)
    {
        raiz->derecha = insertar(raiz->derecha, usuario);
    }

    return raiz; // Esto es para ignorar a usuarios duplicados
}

// Buscar un nodo
Nodoarbol *buscar(Nodoarbol *raiz, const std::string &usuario)
{
    // caso base
    if (raiz == nullptr || raiz->dato.usuario == usuario)
    {
        return raiz;
    }

    // caso recursivo
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

// Recorrer arbol
void inorden(Nodoarbol *raiz)
{
    if (raiz != nullptr)
    {
        inorden(raiz->izquierda);
        std::cout << "Id: " << raiz->dato.id << std::endl;
        std::cout << "Usuario: " << raiz->dato.usuario << std::endl;
        inorden(raiz->derecha);
    }
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

// imprimir un usuario registrado
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
    std::cout << "Usuairo: " << usuario.usuario << std::endl;

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "ID: " << usuario.id << std::endl;

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Password: " << usuario.password << std::endl;
    std::cout << std::string(50, '-') << std::endl;
}


//**Funciones de utilidades**

// Limpiar consola
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pausar programa
void pausarConsola()
{
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); // Espera a que se presione Enter
}

// Mensaje de error para opciones invalidas del menu
void opcioninvalida(int min, int max)
{
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Opcion invalida." << std::endl;
    std::cout << "Por favor ingrese un numero entre (" << min << "-" << max << ")" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

// Imprimir el encabezado de una opcion
void encabezado(const std::string &titulo)
{
    std::cout << std::string(50, '=') << std::endl;
    printCentered(titulo);
    std::cout << std::string(50, '=') << std::endl;
}

// Leer texto por consola, con espacio y autoajustado
std::string leertexto()
{
    std::string entrada;

    // Limpiar posibles saltos de línea previos
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore();
    }

    // Leer la línea completa
    std::getline(std::cin, entrada);

    // Eliminar espacios en blanco al inicio/final
    size_t inicio = entrada.find_first_not_of(" ");
    size_t fin = entrada.find_last_not_of(" ");

    if (inicio == std::string::npos)
    { // Si es cadena vacía
        return "";
    }

    return entrada.substr(inicio, fin - inicio + 1);
}

// Función para generar el catálogo de productos electrónicos
std::vector<Producto> generarCatalogo() {
    return {
        // Smartphones (10 productos)
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

        // Laptops (10 productos)
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

        // Audio (10 productos)
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

        // Smartwatches (5 productos)
        {"Apple Watch Ultra 2", 4001, "Apple", 799.00, 5, "Wearables"},
        {"Galaxy Watch6 Classic", 4002, "Samsung", 429.99, 4, "Wearables"},
        {"Pixel Watch 2", 4003, "Google", 349.99, 4, "Wearables"},
        {"Garmin Forerunner 965", 4004, "Garmin", 599.99, 5, "Wearables"},
        {"Amazfit GTR 4", 4005, "Amazfit", 199.99, 4, "Wearables"},

        // Monitores (5 productos)
        {"Pro Display XDR", 5001, "Apple", 4999.00, 5, "Monitores"},
        {"Odyssey Neo G9", 5002, "Samsung", 1799.99, 5, "Monitores"},
        {"UltraGear 45GR95QE", 5003, "LG", 1699.99, 4, "Monitores"},
        {"Alienware 34 QD-OLED", 5004, "Dell", 1199.99, 5, "Monitores"},
        {"ProArt PA329CV", 5005, "ASUS", 999.00, 4, "Monitores"},

        // Gaming (5 productos)
        {"PlayStation 5", 6001, "Sony", 499.99, 5, "Gaming"},
        {"Xbox Series X", 6002, "Microsoft", 499.99, 5, "Gaming"},
        {"Nintendo Switch OLED", 6003, "Nintendo", 349.99, 4, "Gaming"},
        {"DualSense Edge", 6004, "Sony", 199.99, 4, "Gaming"},
        {"Xbox Elite Controller", 6005, "Microsoft", 179.99, 4, "Gaming"},

        // Fotografia (5 productos)
        {"Alpha 7 IV", 7001, "Sony", 2499.99, 5, "Fotografia"},
        {"EOS R6 Mark II", 7002, "Canon", 2499.00, 5, "Fotografia"},
        {"Z9", 7003, "Nikon", 5499.95, 5, "Fotografia"},
        {"GoPro Hero12 Black", 7004, "GoPro", 449.99, 4, "Fotografia"},
        {"DJI Mavic 3 Pro", 7005, "DJI", 2199.00, 5, "Fotografia"}
    };
}

// Función auxiliar para convertir a minúsculas (búsquedas insensibles a mayúsculas)
std::string aMinusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return resultado;
}

// 1. Búsqueda por categoría (insensible a mayúsculas)
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

//**Funciones para listas enlazadas**

// Insertar un elemento al final de la lista
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

// Verificar si un valor existe en la lista
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

//**Funciones para el sistema de recomendación**

// Obtener categorías únicas del catálogo
std::vector<std::string> obtenerCategoriasUnicas() {
    std::set<std::string> categoriasSet;
    for (const auto& producto : catalogoGlobal) {
        categoriasSet.insert(producto.categoria);
    }
    return std::vector<std::string>(categoriasSet.begin(), categoriasSet.end());
}

// Mostrar productos por categoría (solo nombres)
void mostrarProductosPorCategoria(const std::string& categoria) {
    std::vector<Producto> productos = buscarPorCategoria(catalogoGlobal, categoria);
    std::cout << "\n=== " << categoria << " ===\n";
    for (const auto& producto : productos) {
        std::cout << "ID: " << producto.id << " - " << producto.descripcion << "\n";
    }
    std::cout << "------------------------\n";
}

// Mostrar detalles de un producto y agregar al historial
void verDetallesProducto(int idProducto, Usuario* usuario) {
    for (const auto& producto : catalogoGlobal) {
        if (producto.id == idProducto) {
            clearScreen();
            producto.mostrar();

            // Registrar en el historial si no existe
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

// Obtener la categoría más frecuente en el historial
std::string obtenerCategoriaFrecuente(Usuario* usuario) {
    // Contar categorías en el historial
    std::vector<std::pair<std::string, int>> conteo;

    Nodolista* actual = usuario->historial;
    while (actual != nullptr) {
        int id = std::stoi(actual->dato);
        for (const auto& producto : catalogoGlobal) {
            if (producto.id == id) {
                bool encontrado = false;
                for (auto& par : conteo) {
                    if (par.first == producto.categoria) {
                        par.second++;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    conteo.push_back({producto.categoria, 1});
                }
                break;
            }
        }
        actual = actual->siguiente;
    }

    // Encontrar la categoría con mayor conteo
    if (conteo.empty()) {
        return "";
    }

    std::string categoriaFrecuente = conteo[0].first;
    int maxConteo = conteo[0].second;

    for (const auto& par : conteo) {
        if (par.second > maxConteo) {
            maxConteo = par.second;
            categoriaFrecuente = par.first;
        }
    }

    return categoriaFrecuente;
}

// Generar productos recomendados
std::vector<Producto> generarRecomendaciones(Usuario* usuario) {
    std::vector<Producto> recomendados;
    std::string categoriaFrecuente = obtenerCategoriaFrecuente(usuario);

    if (categoriaFrecuente.empty()) {
        return recomendados;
    }

    // Obtener productos de la categoría frecuente
    std::vector<Producto> productosCategoria = buscarPorCategoria(catalogoGlobal, categoriaFrecuente);

    // Filtrar productos no vistos
    for (const auto& producto : productosCategoria) {
        std::string idStr = std::to_string(producto.id);
        if (!existeEnLista(usuario->historial, idStr)) {
            recomendados.push_back(producto);
        }
    }

    return recomendados;
}

//**Menú de usuario**

void mostrarMenuUsuario(Usuario* usuario) {
    int opcion;
    bool salir = false;
    std::vector<std::string> categorias = obtenerCategoriasUnicas();

    while (!salir) {
        clearScreen();
        encabezado("Bienvenido, " + usuario->nombre);
        std::cout << "1. Ver catalogo de productos\n";
        std::cout << "2. Ver recomendaciones\n";
        std::cout << "3. Cerrar sesion\n";
        std::cout << "------------------------\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar buffer

        switch (opcion) {
            case 1: {
                // Mostrar productos por categoría
                clearScreen();
                encabezado("Catalogo de Productos");
                for (const auto& categoria : categorias) {
                    mostrarProductosPorCategoria(categoria);
                }

                // Permitir selección de producto
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
                // Mostrar recomendaciones
                clearScreen();
                encabezado("Recomendaciones para ti");

                std::vector<Producto> recomendaciones = generarRecomendaciones(usuario);
                if (recomendaciones.empty()) {
                    std::cout << "No hay recomendaciones disponibles. Vea algunos productos primero.\n";
                } else {
                    std::cout << "Basado en tus intereses:\n";
                    for (const auto& producto : recomendaciones) {
                        std::cout << "ID: " << producto.id << " - " << producto.descripcion << "\n";
                    }

                    // Permitir selección de producto recomendado
                    std::cout << "\nIngrese el ID del producto para ver detalles (0 para volver): ";
                    int idProducto;
                    std::cin >> idProducto;
                    std::cin.ignore();

                    if (idProducto != 0) {
                        verDetallesProducto(idProducto, usuario);
                    }
                }
                pausarConsola();
                break;
            }
            case 3:
                salir = true;
                clearScreen();
                encabezado("Sesion finalizada");
                pausarConsola();
                break;
            default:
                opcioninvalida(1, 3);
                pausarConsola();
                break;
        }
    }
}

/* Comandos */

// Comando para registrar un usuario
void ComandoRegistrarUsuario()
{
    clearScreen();
    encabezado("Registro de usuario");
    std::cout << std::string(50, '=') << std::endl;

    Usuario nuevo;
    bool cancelado = false;

    // Función para validar campos vacíos
    auto validarCampo = [](const std::string &valor, const std::string &campo) -> bool
    {
        if (valor.empty())
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "ERROR: El " << campo << " no puede estar vacio" << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            return false;
        }
        return true;
    };

    // Validar nombre
    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Nombre: " << std::endl;
        nuevo.nombre = leertexto();
    } while (!validarCampo(nuevo.nombre, "nombre"));
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Nombre registrado: " << nuevo.nombre << std::endl;

    // Validar apellido
    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Apellido: " << std::endl;
        nuevo.apellido = leertexto();
    } while (!validarCampo(nuevo.apellido, "apellido"));
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Apellido registrado: " << nuevo.apellido << std::endl;

    // Validar usuario
    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Usuario: " << std::endl;
        std::string input = leertexto();

        // Validar vacío
        if (!validarCampo(input, "usuario"))
            continue;

        // Validar espacios
        if (input.find(' ') != std::string::npos)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "ERROR: El usuario no puede contener espacios" << std::endl;
            continue;
        }

        // Verificar unicidad
        Nodoarbol *coincidencia = buscar(Usuarios, input);
        if (coincidencia != nullptr)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "Usuario '" << input << "' ya registrado." << std::endl;
            std::cout << std::string(50, '=') << std::endl;

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Desea intentar con otro usuario? (s/n): ";
            std::string continuar = leertexto();
            std::cout << std::string(50, '-') << std::endl;

            if (continuar == "n" || continuar == "N")
            {
                std::cout << std::string(50, '=') << std::endl;
                printCentered("Registro de usuario cancelado");
                std::cout << std::string(50, '=') << std::endl;
                cancelado = true;
                break;
            }
            continue;
        }

        nuevo.usuario = input;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Usuario registrado: " << nuevo.usuario << std::endl;
        break;
    } while (true);

    if (cancelado)
    {
        pausarConsola();
        return;
    }

    // Validar contraseña
    do
    {
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Password (minimo 6 caracteres): " << std::endl;
        nuevo.password = leertexto();

        // Validar longitud mínima
        if (nuevo.password.length() < 6)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "ERROR: La password debe tener minimo 6 caracteres" << std::endl;
            continue;
        }
        break;
    } while (true);

    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Password registrada: " << nuevo.password << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    // Generar id
    nuevo.id = generarID();

    // Inicializar estructuras
    nuevo.historial = nullptr;
    nuevo.preferencias = nullptr;

    // Guardar usuario
    insertar(Usuarios, nuevo);

    // Mostrar resultado
    clearScreen();
    std::cout << std::string(50, '=') << std::endl;
    printCentered("REGISTRO EXITOSO!");
    std::cout << std::string(50, '=') << std::endl;
    imprimirUsuario(nuevo);
    std::cout << std::string(50, '=') << std::endl;
    pausarConsola();
}

// Comando para ingresar con un usuario
Usuario* ComandoIngresarUsuario()
{
    do
    {
        clearScreen();
        encabezado("Ingresar a la plataforma.");
        std::cout << std::string(50, '=') << std::endl;

        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Ingrese el usuario: " << std::endl;
        std::string usuario = leertexto();
        std::cout << std::string(50, '-') << std::endl;

        Nodoarbol *ingreso = buscar(Usuarios, usuario);

        if (ingreso == nullptr)
        {
            std::cout << std::string(50, '=') << std::endl;
            std::cout << "El usuario '" << usuario << "' no existe." << std::endl;
            std::cout << std::string(50, '=') << std::endl;

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Desea probar con otro usuario? (s/n): ";
            std::string opcion = leertexto();

            if (opcion == "n" || opcion == "N")
            {
                clearScreen();
                std::cout << std::string(50, '=') << std::endl;
                printCentered("Saliendo del login");
                std::cout << std::string(50, '=') << std::endl;
                pausarConsola();
                return nullptr;
            }
            continue;
        }

        int intentos = 0;
        const int MAX_INTENTOS = 3;

        while (intentos < MAX_INTENTOS)
        {
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Ingrese la password: " << std::endl;
            std::string password = leertexto();
            std::cout << std::string(50, '-') << std::endl;

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
                std::cout << std::string(50, '=') << std::endl;
                std::cout << "Password incorrecta. Intento " << intentos << "/" << MAX_INTENTOS << std::endl;
                std::cout << std::string(50, '=') << std::endl;

                if (intentos < MAX_INTENTOS)
                {
                    std::cout << std::string(50, '-') << std::endl;
                    std::cout << "Desea intentar de nuevo? (s/n): ";
                    std::string reintentar = leertexto();

                    if (reintentar == "n" || reintentar == "N")
                    {
                        clearScreen();
                        std::cout << std::string(50, '=') << std::endl;
                        printCentered("Saliendo del login");
                        std::cout << std::string(50, '=') << std::endl;
                        pausarConsola();
                        return nullptr;
                    }
                }
            }
        }

        // Si se superan los intentos máximos
        std::cout << std::string(50, '=') << std::endl;
        printCentered("Ha superado el maximo de intentos");
        std::cout << std::string(50, '=') << std::endl;
        pausarConsola();
        return nullptr;

    } while (true);
}

/* Menus */

void procesarMainmenu(int opcion)
{
    switch (opcion)
    {
    case 1:
        clearScreen();
        ComandoRegistrarUsuario();
        break;

    case 2:
    	clearScreen();
    	Usuario* usuario = ComandoIngresarUsuario();
        if (usuario != nullptr) {
            mostrarMenuUsuario(usuario);
        }
        break;
    }
}

void Mainmenu()
{
    int opcion;

    do
    {
        clearScreen();
        encabezado("Bienvenid@ a Quantum Store.");
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "1.-Registrar un nuevo usuario." << std::endl;
        std::cout << "2.-Ingresar con un usuario existente." << std::endl;
        std::cout << "3.-Salir." << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();
        std::cout << std::string(50, '-') << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        if (opcion == 3)
        {
            break;
        }
        else
        {
            procesarMainmenu(opcion);
        }

    } while (true);
}


int main() {
    // Generar catálogo global
    catalogoGlobal = generarCatalogo();

    Mainmenu();

    std::cout << std::string(50, '=') << std::endl;
    printCentered("Gracias por visitar.");
    std::cout << std::string(50, '=') << std::endl;

    return 0;
}
