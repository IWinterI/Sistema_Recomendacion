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
#include <chrono>
#include <thread>

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
    Nodolista *carrito;
    Nodolista *listaDeseos;
};

struct Nodoarbol
{
    Usuario dato;
    Nodoarbol *izquierda;
    Nodoarbol *derecha;
};

struct Producto
{
    std::string descripcion;
    int id;
    std::string marca;
    double precio;
    int calidad;
    std::string categoria;

    Producto(std::string desc = "", int id = 0, std::string marca = "",
             double precio = 0.0, int calidad = 1, std::string categoria = "")
        : descripcion(desc), id(id), marca(marca), precio(precio), categoria(categoria)
    {
        if (calidad < 1)
            this->calidad = 1;
        else if (calidad > 5)
            this->calidad = 5;
        else
            this->calidad = calidad;
    }

    void mostrar() const
    {
        std::cout << "ID: " << id
                  << "\nProducto: " << descripcion
                  << "\nCategoria: " << categoria
                  << "\nMarca: " << marca
                  << "\nPrecio: $" << std::fixed << std::setprecision(2) << precio
                  << "\nCalidad: " << std::string(calidad, '*')
                  << " (" << calidad << "/5)\n\n";
    }
};

struct Recomendaciones
{
    std::vector<Producto> porCategoria;
    std::vector<Producto> porMarca;
    std::vector<Producto> porCalidad;
};

Nodoarbol *Usuarios = nullptr;

std::vector<Producto> catalogoGlobal;

const std::string CARACTERES_VALIDOS =
    "1234567890"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

void printCentered(const std::string &text, int width = 50)
{
    int padding = (width - static_cast<int>(text.length())) / 2;
    if (padding > 0)
        std::cout << std::string(padding, ' ');
    std::cout << text << std::endl;
}

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

void seccion(const std::string &titulo)
{
    std::cout << std::string(50, '-') << std::endl;
    printCentered(titulo);
    std::cout << std::string(50, '-') << std::endl;
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

std::vector<Producto> generarCatalogo()
{
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
        {"DJI Mavic 3 Pro", 7005, "DJI", 2199.00, 5, "Fotografia"}};
}

std::string aMinusculas(const std::string &texto)
{
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    return resultado;
}

void insertarLista(Nodolista *&lista, const std::string &valor)
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

bool existeEnLista(Nodolista *lista, const std::string &valor)
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

std::vector<Producto> buscarPorCategoria(const std::vector<Producto> &productos, const std::string &categoriaBuscada)
{
    std::vector<Producto> resultados;
    std::string categoriaLower = aMinusculas(categoriaBuscada);

    for (const auto &prod : productos)
    {
        if (aMinusculas(prod.categoria) == categoriaLower)
        {
            resultados.push_back(prod);
        }
    }
    return resultados;
}

std::vector<Producto> buscarPorRangoPrecios(const std::vector<Producto> &productos, double precioMin, double precioMax)
{
    std::vector<Producto> resultados;
    for (const auto &prod : productos)
    {
        if (prod.precio >= precioMin && prod.precio <= precioMax)
        {
            resultados.push_back(prod);
        }
    }
    return resultados;
}

std::vector<Producto> buscarPorMarca(const std::vector<Producto> &productos, const std::string &marcaBuscada)
{
    std::vector<Producto> resultados;
    std::string marcaLower = aMinusculas(marcaBuscada);

    for (const auto &prod : productos)
    {
        if (aMinusculas(prod.marca) == marcaLower)
        {
            resultados.push_back(prod);
        }
    }
    return resultados;
}

std::vector<Producto> buscarPorDescripcion(const std::vector<Producto> &productos, const std::string &textoBuscado)
{
    std::vector<Producto> resultados;
    std::string textoLower = aMinusculas(textoBuscado);

    for (const auto &prod : productos)
    {
        std::string descLower = aMinusculas(prod.descripcion);
        if (descLower.find(textoLower) != std::string::npos)
        {
            resultados.push_back(prod);
        }
    }
    return resultados;
}

std::vector<std::string> obtenerCategoriasUnicas()
{
    std::set<std::string> categoriasSet;
    for (const auto &producto : catalogoGlobal)
    {
        categoriasSet.insert(producto.categoria);
    }
    return std::vector<std::string>(categoriasSet.begin(), categoriasSet.end());
}

std::vector<std::string> obtenerMarcasUnicas()
{
    std::set<std::string> marcasSet;
    for (const auto &producto : catalogoGlobal)
    {
        marcasSet.insert(producto.marca);
    }
    return std::vector<std::string>(marcasSet.begin(), marcasSet.end());
}

void mostrarProductosPorCategoria(const std::string &categoria)
{
    std::vector<Producto> productos = buscarPorCategoria(catalogoGlobal, categoria);
    std::cout << "\n=== " << categoria << " ===\n";
    for (const auto &producto : productos)
    {
        std::cout << "ID: " << producto.id << " - " << producto.descripcion << "\n";
    }
    std::cout << "------------------------\n";
}

void verDetallesProducto(int idProducto, Usuario *usuario)
{
    for (const auto &producto : catalogoGlobal)
    {
        if (producto.id == idProducto)
        {
            clearScreen();
            encabezado("Detalles del Producto");
            producto.mostrar();

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
                std::cout << "\nProducto agregado al carrito\n";
                pausarConsola();
            }
            else if (opcion == 2)
            {
                insertarLista(usuario->listaDeseos, idStr);
                std::cout << "\nProducto agregado a lista de deseos\n";
                pausarConsola();
            }

            return;
        }
    }
    std::cout << "Producto no encontrado.\n";
    pausarConsola();
}

struct EstadisticasUsuario
{
    std::string categoriaFrecuente;
    std::string marcaFrecuente;
    int calidadFrecuente;
};

EstadisticasUsuario obtenerEstadisticasUsuario(Usuario *usuario)
{
    EstadisticasUsuario stats;
    std::map<std::string, int> conteoCategorias;
    std::map<std::string, int> conteoMarcas;
    std::map<int, int> conteoCalidades;

    Nodolista *actual = usuario->historial;
    while (actual != nullptr)
    {
        int id = std::stoi(actual->dato);
        for (const auto &producto : catalogoGlobal)
        {
            if (producto.id == id)
            {
                conteoCategorias[producto.categoria]++;
                conteoMarcas[producto.marca]++;
                conteoCalidades[producto.calidad]++;
                break;
            }
        }
        actual = actual->siguiente;
    }

    if (!conteoCategorias.empty())
    {
        stats.categoriaFrecuente = std::max_element(
                                       conteoCategorias.begin(), conteoCategorias.end(),
                                       [](const auto &a, const auto &b)
                                       { return a.second < b.second; })
                                       ->first;
    }

    if (!conteoMarcas.empty())
    {
        stats.marcaFrecuente = std::max_element(
                                   conteoMarcas.begin(), conteoMarcas.end(),
                                   [](const auto &a, const auto &b)
                                   { return a.second < b.second; })
                                   ->first;
    }

    if (!conteoCalidades.empty())
    {
        stats.calidadFrecuente = std::max_element(
                                     conteoCalidades.begin(), conteoCalidades.end(),
                                     [](const auto &a, const auto &b)
                                     { return a.second < b.second; })
                                     ->first;
    }

    return stats;
}

Recomendaciones generarRecomendaciones(Usuario *usuario)
{
    Recomendaciones rec;
    std::set<int> productosExcluidos;

    // Recopilar IDs de productos en historial, carrito y lista de deseos
    auto agregarIDs = [&](Nodolista *lista)
    {
        Nodolista *actual = lista;
        while (actual != nullptr)
        {
            try
            {
                int id = std::stoi(actual->dato);
                productosExcluidos.insert(id);
            }
            catch (...)
            {
                // Ignorar errores de conversión
            }
            actual = actual->siguiente;
        }
    };

    agregarIDs(usuario->historial);
    agregarIDs(usuario->carrito);
    agregarIDs(usuario->listaDeseos);

    // Recomendaciones basadas en categorías preferidas
    if (usuario->preferencias != nullptr)
    {
        std::vector<Producto> candidatos;
        Nodolista *pref = usuario->preferencias;
        while (pref != nullptr)
        {
            for (const auto &prod : catalogoGlobal)
            {
                // Solo agregar productos de categorías preferidas no excluidos
                if (prod.categoria == pref->dato &&
                    productosExcluidos.find(prod.id) == productosExcluidos.end())
                {
                    candidatos.push_back(prod);
                }
            }
            pref = pref->siguiente;
        }

        // Eliminar duplicados
        std::sort(candidatos.begin(), candidatos.end(),
                  [](const Producto &a, const Producto &b)
                  { return a.id < b.id; });
        auto last = std::unique(candidatos.begin(), candidatos.end(),
                                [](const Producto &a, const Producto &b)
                                { return a.id == b.id; });
        candidatos.erase(last, candidatos.end());

        // Ordenar por calidad (mayor primero) y precio (menor primero)
        std::sort(candidatos.begin(), candidatos.end(),
                  [](const Producto &a, const Producto &b)
                  {
                      if (a.calidad != b.calidad)
                          return a.calidad > b.calidad;
                      return a.precio < b.precio;
                  });

        // Asignar TODOS los productos sin límite
        rec.porCategoria = candidatos;
    }

    // Recomendaciones basadas en historial (si existe)
    EstadisticasUsuario stats = obtenerEstadisticasUsuario(usuario);

    // Recomendaciones por marca
    if (!stats.marcaFrecuente.empty())
    {
        std::vector<Producto> candidatos;
        for (const auto &prod : catalogoGlobal)
        {
            if (prod.marca == stats.marcaFrecuente &&
                productosExcluidos.find(prod.id) == productosExcluidos.end())
            {
                candidatos.push_back(prod);
            }
        }

        // Ordenar y asignar TODOS los productos
        std::sort(candidatos.begin(), candidatos.end(),
                  [](const Producto &a, const Producto &b)
                  {
                      if (a.calidad != b.calidad)
                          return a.calidad > b.calidad;
                      return a.precio < b.precio;
                  });

        rec.porMarca = candidatos;
    }

    // Recomendaciones por calidad
    if (stats.calidadFrecuente > 0)
    {
        std::vector<Producto> candidatos;
        for (const auto &prod : catalogoGlobal)
        {
            if (prod.calidad == stats.calidadFrecuente &&
                productosExcluidos.find(prod.id) == productosExcluidos.end())
            {
                candidatos.push_back(prod);
            }
        }

        // Ordenar y asignar TODOS los productos
        std::sort(candidatos.begin(), candidatos.end(),
                  [](const Producto &a, const Producto &b)
                  { return a.precio < b.precio; });

        rec.porCalidad = candidatos;
    }

    return rec;
}

void seleccionarPreferencias(Usuario *usuario)
{
    clearScreen();
    encabezado("Seleccion de Preferencias");

    std::vector<std::string> categorias = obtenerCategoriasUnicas();
    std::string entrada;

    while (true)
    {
        int i = 1;

        for (auto var : categorias)
        {
            std::cout << i << ".-" << var << std::endl;
            i++;
        }

        seccion("Instrucciones");
        std::cout << "Ingrese los numeros de las categorias que le interesan (ej: 1 3 5): ";
        std::getline(std::cin, entrada);

        std::istringstream iss(entrada);
        int num;
        bool invalido = false;

        usuario->preferencias = nullptr;

        while (iss >> num)
        {
            if (num >= 1 && static_cast<size_t>(num) <= categorias.size())
            {
                std::string categoriaSeleccionada = categorias[num - 1];
                if (!existeEnLista(usuario->preferencias, categoriaSeleccionada))
                {
                    insertarLista(usuario->preferencias, categoriaSeleccionada);
                }
            }
            else
            {
                invalido = true;
            }
        }

        if (!invalido && usuario->preferencias != nullptr)
        {
            seccion("Preferencias Guardadas");
            Nodolista *temp = usuario->preferencias;
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
    Nodolista *actual = usuario->carrito;
    while (actual != nullptr)
    {
        int id = std::stoi(actual->dato);
        for (const auto &producto : catalogoGlobal)
        {
            if (producto.id == id)
            {
                seccion(producto.descripcion);
                std::cout << "ID: " << producto.id << "\n";
                std::cout << "Precio: $" << std::fixed << std::setprecision(2) << producto.precio << "\n";
                total += producto.precio;
                break;
            }
        }
        actual = actual->siguiente;
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
        std::cout << "Gracias por su compra\n";
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

    Nodolista *actual = usuario->listaDeseos;
    while (actual != nullptr)
    {
        int id = std::stoi(actual->dato);
        for (const auto &producto : catalogoGlobal)
        {
            if (producto.id == id)
            {
                seccion(producto.descripcion);
                std::cout << "ID: " << producto.id << "\n";
                std::cout << "Precio: $" << std::fixed << std::setprecision(2) << producto.precio << "\n";
                break;
            }
        }
        actual = actual->siguiente;
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

    Nodolista *actual = usuario->historial;
    while (actual != nullptr)
    {
        int id = std::stoi(actual->dato);
        for (const auto &producto : catalogoGlobal)
        {
            if (producto.id == id)
            {
                seccion(producto.descripcion);
                std::cout << "ID: " << producto.id << "\n";
                std::cout << "Categoria: " << producto.categoria << "\n";
                std::cout << "Marca: " << producto.marca << "\n";
                std::cout << "Precio: $" << std::fixed << std::setprecision(2) << producto.precio << "\n";
                break;
            }
        }
        actual = actual->siguiente;
    }

    pausarConsola();
}

void mostrarMenuUsuario(Usuario *usuario)
{
    int opcion;
    bool salir = false;
    std::vector<std::string> categorias = obtenerCategoriasUnicas();
    std::vector<std::string> marcas = obtenerMarcasUnicas();

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
            for (const auto &categoria : categorias)
            {
                mostrarProductosPorCategoria(categoria);
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

            if (rec.porCategoria.empty() && rec.porMarca.empty() && rec.porCalidad.empty())
            {
                seccion("Sin Recomendaciones");
                std::cout << "No hay recomendaciones disponibles. Vea algunos productos primero.\n";
            }
            else
            {
                if (!rec.porCategoria.empty())
                {
                    seccion("Recomendados por categoria");
                    for (const auto &prod : rec.porCategoria)
                    {
                        std::cout << "ID: " << prod.id << " - " << prod.descripcion;
                        std::cout << " (Categoria: " << prod.categoria << ")\n";
                    }
                }

                if (!rec.porMarca.empty())
                {
                    seccion("Recomendados por marca");
                    for (const auto &prod : rec.porMarca)
                    {
                        std::cout << "ID: " << prod.id << " - " << prod.descripcion;
                        std::cout << " (Marca: " << prod.marca << ")\n";
                    }
                }

                if (!rec.porCalidad.empty())
                {
                    seccion("Recomendados por calidad similar");
                    for (const auto &prod : rec.porCalidad)
                    {
                        std::cout << "ID: " << prod.id << " - " << prod.descripcion;
                        std::cout << " (Calidad: " << std::string(prod.calidad, '*') << ")\n";
                    }
                }
            }

            if (!rec.porCategoria.empty() || !rec.porMarca.empty() || !rec.porCalidad.empty())
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

                std::vector<Producto> resultados;

                switch (opcionBusqueda)
                {
                case 1:
                {
                    seccion("Categorias Disponibles");
                    for (const auto &cat : categorias)
                    {
                        std::cout << "- " << cat << "\n";
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
                    for (const auto &marca : marcas)
                    {
                        std::cout << "- " << marca << "\n";
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
                    std::cout << "Ingrese palabra clave (ej: PlayStation, laptop, Galaxy): ";
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

                    if (resultados.empty())
                    {
                        seccion("Sin Resultados");
                        std::cout << "No se encuentra ninguna coincidencia.\n";
                    }
                    else
                    {
                        seccion("Productos Encontrados");
                        for (const auto &prod : resultados)
                        {
                            std::cout << "ID: " << prod.id << " - " << prod.descripcion << "\n";
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

    // Primero seleccionar preferencias
    seleccionarPreferencias(&nuevo);

    // Luego insertar en el árbol con las preferencias ya asignadas
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

int main()
{
    catalogoGlobal = generarCatalogo();
    Mainmenu();
    encabezado("Gracias por visitar Quantum Store");
    return 0;
}
