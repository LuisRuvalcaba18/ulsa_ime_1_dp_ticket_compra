// Práctica: Ticket de compra
// main() solo coordina: pide los datos, llama a los módulos y muestra el ticket.
// Deja el comentario "// Paso N" sobre cada bloque, con la numeración de TU receta.
//
// Compilar (desde la carpeta del proyecto):
//   g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp -o ticket
// Ejecutar:
//   macOS:   ./ticket
//   Windows: .\ticket.exe

// iostream permite mostrar texto en pantalla (std::cout) y leer del teclado (std::cin)
#include <iostream>
#include <string>

#include "utilerias.h"
#include "ticket.h"

int main() {
    // Variables (siempre inicializadas)
    std::string nombre = "";
    double precio = 0.0;
    int cantidad = 0;
    double porcentajeDescuento = 0.0;
    double subtotal = 0.0;
    double descuento = 0.0;
    double iva = 0.0;
    double total = 0.0;

    // Paso 1: mensaje de bienvenida
    std::cout << "=== Bienvenido a la tienda ===\n";

    // Paso 2: pedir y validar los datos
    // Paso 2.1: nombre del producto (leerCadena ya revisa que no esté vacío)
    nombre = leerCadena("Nombre del producto: ");

    // Paso 2.2: precio (debe ser mayor que 0)
    precio = leerDecimal("Precio: ");
    while (precio <= 0) {
        std::cout << "El precio debe ser mayor que 0.\n";
        precio = leerDecimal("Precio: ");
    }

    // Paso 2.3: cantidad (entero mayor que 0)
    cantidad = leerEntero("Cantidad: ");
    while (cantidad <= 0) {
        std::cout << "La cantidad debe ser mayor que 0.\n";
        cantidad = leerEntero("Cantidad: ");
    }

    // Paso 2.4: descuento (entre 0 y 100)
    porcentajeDescuento = leerDecimal("Descuento (%): ");
    while (porcentajeDescuento < 0 || porcentajeDescuento > 100) {
        std::cout << "El descuento debe estar entre 0 y 100.\n";
        porcentajeDescuento = leerDecimal("Descuento (%): ");
    }

    // Paso 3: calcular los importes llamando a los módulos de ticket.h
    // Paso 3.1: subtotal
    subtotal = calcularSubtotal(precio, cantidad);
    // Paso 3.2: descuento
    descuento = calcularDescuento(subtotal, porcentajeDescuento);
    // Paso 3.3: IVA sobre lo que queda después del descuento
    iva = calcularIVA(subtotal - descuento);
    // Paso 3.4: total
    total = subtotal - descuento + iva;

    // Paso 4: imprimir el ticket
    imprimirTicket(nombre, precio, cantidad, subtotal, porcentajeDescuento,
                   descuento, iva, total);

    // return 0 le indica al sistema operativo que el programa terminó sin errores
    return 0;
}