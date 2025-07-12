#include "../include/catalogo.h"
#include "../include/utilidades.h"

ListaProducto catalogoGlobal = nullptr;

void inicializarCatalogo()
{
    catalogoGlobal = nullptr; // Limpiar por si se llama más de una vez
    insertarEnLista(catalogoGlobal, {"iPhone 15 Pro", 1001, "Apple", 999.99, 5, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"Galaxy S24 Ultra", 1002, "Samsung", 1199.99, 5, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"Pixel 8 Pro", 1003, "Google", 899.00, 4, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"Xperia 1 V", 1004, "Sony", 1299.99, 4, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"OnePlus 12", 1005, "OnePlus", 799.99, 4, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"Redmi Note 13 Pro", 1006, "Xiaomi", 349.99, 3, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"ROG Phone 7", 1007, "ASUS", 999.00, 4, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"Moto Edge 40", 1008, "Motorola", 599.99, 3, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"Nord N30", 1009, "OnePlus", 299.99, 3, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"Galaxy A54", 1010, "Samsung", 449.99, 4, "Smartphones"});
    insertarEnLista(catalogoGlobal, {"MacBook Pro 16\" M2", 2001, "Apple", 2499.00, 5, "Laptops"});
    insertarEnLista(catalogoGlobal, {"XPS 15 OLED", 2002, "Dell", 2199.99, 5, "Laptops"});
    insertarEnLista(catalogoGlobal, {"ThinkPad X1 Carbon", 2003, "Lenovo", 1899.00, 4, "Laptops"});
    insertarEnLista(catalogoGlobal, {"ROG Zephyrus G14", 2004, "ASUS", 1499.99, 4, "Laptops"});
    insertarEnLista(catalogoGlobal, {"Spectre x360", 2005, "HP", 1399.99, 4, "Laptops"});
    insertarEnLista(catalogoGlobal, {"Surface Laptop 5", 2006, "Microsoft", 1299.00, 4, "Laptops"});
    insertarEnLista(catalogoGlobal, {"IdeaPad Slim 5", 2007, "Lenovo", 799.99, 3, "Laptops"});
    insertarEnLista(catalogoGlobal, {"Swift 3", 2008, "Acer", 699.00, 3, "Laptops"});
    insertarEnLista(catalogoGlobal, {"Galaxy Book3 Ultra", 2009, "Samsung", 2299.99, 5, "Laptops"});
    insertarEnLista(catalogoGlobal, {"Chromebook 314", 2010, "Acer", 349.99, 3, "Laptops"});
    insertarEnLista(catalogoGlobal, {"WH-1000XM5", 3001, "Sony", 399.99, 5, "Audio"});
    insertarEnLista(catalogoGlobal, {"QuietComfort Ultra", 3002, "Bose", 429.00, 5, "Audio"});
    insertarEnLista(catalogoGlobal, {"AirPods Pro 2", 3003, "Apple", 249.00, 5, "Audio"});
    insertarEnLista(catalogoGlobal, {"Galaxy Buds2 Pro", 3004, "Samsung", 229.99, 4, "Audio"});
    insertarEnLista(catalogoGlobal, {"Soundcore Liberty 4", 3005, "Anker", 129.99, 4, "Audio"});
    insertarEnLista(catalogoGlobal, {"HD 660S2", 3006, "Sennheiser", 499.95, 5, "Audio"});
    insertarEnLista(catalogoGlobal, {"HomePod mini", 3007, "Apple", 99.99, 4, "Audio"});
    insertarEnLista(catalogoGlobal, {"Sonos Era 300", 3008, "Sonos", 449.00, 5, "Audio"});
    insertarEnLista(catalogoGlobal, {"JBL Flip 6", 3009, "JBL", 129.95, 4, "Audio"});
    insertarEnLista(catalogoGlobal, {"HyperX Cloud III", 3010, "HP", 99.99, 4, "Audio"});
    insertarEnLista(catalogoGlobal, {"Apple Watch Ultra 2", 4001, "Apple", 799.00, 5, "Wearables"});
    insertarEnLista(catalogoGlobal, {"Galaxy Watch6 Classic", 4002, "Samsung", 429.99, 4, "Wearables"});
    insertarEnLista(catalogoGlobal, {"Pixel Watch 2", 4003, "Google", 349.99, 4, "Wearables"});
    insertarEnLista(catalogoGlobal, {"Garmin Forerunner 965", 4004, "Garmin", 599.99, 5, "Wearables"});
    insertarEnLista(catalogoGlobal, {"Amazfit GTR 4", 4005, "Amazfit", 199.99, 4, "Wearables"});
    insertarEnLista(catalogoGlobal, {"Pro Display XDR", 5001, "Apple", 4999.00, 5, "Monitores"});
    insertarEnLista(catalogoGlobal, {"Odyssey Neo G9", 5002, "Samsung", 1799.99, 5, "Monitores"});
    insertarEnLista(catalogoGlobal, {"UltraGear 45GR95QE", 5003, "LG", 1699.99, 4, "Monitores"});
    insertarEnLista(catalogoGlobal, {"Alienware 34 QD-OLED", 5004, "Dell", 1199.99, 5, "Monitores"});
    insertarEnLista(catalogoGlobal, {"ProArt PA329CV", 5005, "ASUS", 999.00, 4, "Monitores"});
    insertarEnLista(catalogoGlobal, {"PlayStation 5", 6001, "Sony", 499.99, 5, "Gaming"});
    insertarEnLista(catalogoGlobal, {"Xbox Series X", 6002, "Microsoft", 499.99, 5, "Gaming"});
    insertarEnLista(catalogoGlobal, {"Nintendo Switch OLED", 6003, "Nintendo", 349.99, 4, "Gaming"});
    insertarEnLista(catalogoGlobal, {"DualSense Edge", 6004, "Sony", 199.99, 4, "Gaming"});
    insertarEnLista(catalogoGlobal, {"Xbox Elite Controller", 6005, "Microsoft", 179.99, 4, "Gaming"});
    insertarEnLista(catalogoGlobal, {"Alpha 7 IV", 7001, "Sony", 2499.99, 5, "Fotografia"});
    insertarEnLista(catalogoGlobal, {"EOS R6 Mark II", 7002, "Canon", 2499.00, 5, "Fotografia"});
    insertarEnLista(catalogoGlobal, {"Z9", 7003, "Nikon", 5499.95, 5, "Fotografia"});
    insertarEnLista(catalogoGlobal, {"GoPro Hero12 Black", 7004, "GoPro", 449.99, 4, "Fotografia"});
    insertarEnLista(catalogoGlobal, {"DJI Mavic 3 Pro", 7005, "DJI", 2199.00, 5, "Fotografia"});
}

ListaProducto buscarPorCategoria(ListaProducto productos, const std::string &categoriaBuscada)
{
    ListaProducto resultados = nullptr;
    std::string categoriaLower = aMinusculas(categoriaBuscada);

    NodoProducto* actual = productos;
    while (actual != nullptr)
    {
        if (aMinusculas(actual->dato.categoria) == categoriaLower)
        {
            insertarEnLista(resultados, actual->dato);
        }
        actual = actual->siguiente;
    }
    return resultados;
}

ListaProducto buscarPorRangoPrecios(ListaProducto productos, double precioMin, double precioMax)
{
    ListaProducto resultados = nullptr;
    NodoProducto* actual = productos;
    while (actual != nullptr)
    {
        if (actual->dato.precio >= precioMin && actual->dato.precio <= precioMax)
        {
            insertarEnLista(resultados, actual->dato);
        }
        actual = actual->siguiente;
    }
    return resultados;
}

ListaProducto buscarPorMarca(ListaProducto productos, const std::string &marcaBuscada)
{
    ListaProducto resultados = nullptr;
    std::string marcaLower = aMinusculas(marcaBuscada);

    NodoProducto* actual = productos;
    while (actual != nullptr)
    {
        if (aMinusculas(actual->dato.marca) == marcaLower)
        {
            insertarEnLista(resultados, actual->dato);
        }
        actual = actual->siguiente;
    }
    return resultados;
}

ListaProducto buscarPorDescripcion(ListaProducto productos, const std::string &textoBuscado)
{
    ListaProducto resultados = nullptr;
    std::string textoLower = aMinusculas(textoBuscado);

    NodoProducto* actual = productos;
    while (actual != nullptr)
    {
        std::string descLower = aMinusculas(actual->dato.descripcion);
        if (descLower.find(textoLower) != std::string::npos)
        {
            insertarEnLista(resultados, actual->dato);
        }
        actual = actual->siguiente;
    }
    return resultados;
}

ListaString obtenerCategoriasUnicas()
{
    ListaString categorias = nullptr;
    NodoProducto* actual = catalogoGlobal;
    while (actual != nullptr)
    {
        if (!existeEnLista(categorias, actual->dato.categoria))
        {
            insertarLista(categorias, actual->dato.categoria);
        }
        actual = actual->siguiente;
    }
    return categorias;
}

ListaString obtenerMarcasUnicas()
{
    ListaString marcas = nullptr;
    NodoProducto* actual = catalogoGlobal;
    while (actual != nullptr)
    {
        if (!existeEnLista(marcas, actual->dato.marca))
        {
            insertarLista(marcas, actual->dato.marca);
        }
        actual = actual->siguiente;
    }
    return marcas;
}
