#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <iomanip>

//**Estructuras**

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
                  << "\nPrecio: $" << std::fixed << std::setprecision(2) << precio << "$"
                  << "\nCalidad: " << std::string(calidad, '*')
                  << " (" << calidad << "/5)\n\n";
    }

};

//**Funciones principales de los productos**

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

// 2. Búsqueda por rango de precios
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

// 3. Búsqueda por marca (insensible a mayúsculas)
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

// 4. Búsqueda por descripción (insensible a mayúsculas y subcadenas)
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

int main() {
    // Generar catálogo de productos
    std::vector<Producto> catalogo = generarCatalogo();

    std::cout << "===== CATALOGO ELECTRONICO COMPLETO (50 productos) =====\n";
    for (const auto& producto : catalogo) {
        producto.mostrar();
    }

    // Ejemplo de búsquedas
    std::cout << "\n\n===== PRODUCTOS APPLE (Busqueda por marca) =====\n";
    auto resultadosApple = buscarPorMarca(catalogo, "apple");
    for (const auto& p : resultadosApple) {
        p.mostrar();
    }

    std::cout << "\n\n===== SMARTPHONES GAMA ALTA (> $800) =====\n";
    auto smartphonesAltaGama = buscarPorCategoria(resultadosApple, "Smartphones");
    smartphonesAltaGama = buscarPorRangoPrecios(smartphonesAltaGama, 800.0, 2000.0);
    for (const auto& p : smartphonesAltaGama) {
        p.mostrar();
    }

    std::cout << "\n\n===== PRODUCTOS CON 'PRO' EN DESCRIPCIoN =====\n";
    auto resultadosPro = buscarPorDescripcion(catalogo, "pro");
    for (const auto& p : resultadosPro) {
        p.mostrar();
    }

    return 0;
}
