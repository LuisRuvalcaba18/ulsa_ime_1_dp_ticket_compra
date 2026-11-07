#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Constantes: cada valor fijo vive en un solo lugar.
const double TASA_IVA = 16.0;                       // IVA en porcentaje
const int ANCHO_TICKET = 36;                        // largo de las lineas
const int ANCHO_ETIQUETA = 18;                      // espacio de cada etiqueta
const std::string NOMBRE_VENDEDOR = "Tu Nombre";    // CAMBIA ESTO por tu nombre (sin acentos)

// Recibe: el precio de un producto y la cantidad comprada.
// Devuelve: el subtotal (precio por cantidad).
inline double calcularSubtotal(double precio, int cantidad) {
    return precio * cantidad;
}

// Recibe: una cantidad base y un porcentaje (de 0 a 100).
// Devuelve: ese porcentaje de la cantidad base.
inline double calcularPorcentaje(double base, double porcentaje) {
    return base * porcentaje / 100.0;
}

// Recibe: el subtotal y el porcentaje de descuento (de 0 a 100).
// Devuelve: el monto del descuento en pesos.
// (El error original era no dividir entre 100.)
inline double calcularDescuento(double subtotal, double porcentaje) {
    return calcularPorcentaje(subtotal, porcentaje);
}

// Recibe: la base sobre la que se cobra IVA (subtotal menos descuento).
// Devuelve: el monto del IVA en pesos.
inline double calcularIVA(double base) {
    return calcularPorcentaje(base, TASA_IVA);
}

// Procedimiento: imprime el ticket completo, no devuelve nada.
// Recibe: nombre, precio, cantidad, subtotal, porcentaje de descuento,
//         monto del descuento, IVA y total.
inline void imprimirTicket(const std::string& nombre, double precio, int cantidad,
                           double subtotal, double porcentajeDescuento,
                           double descuento, double iva, double total) {
    // Etiquetas con porcentaje (sin los ".00" que pone std::fixed)
    std::ostringstream etiquetaDescuento;
    etiquetaDescuento << "Descuento (" << porcentajeDescuento << "%):";
    std::ostringstream etiquetaIVA;
    etiquetaIVA << "IVA (" << TASA_IVA << "%):";

    std::cout << std::fixed << std::setprecision(2) << std::left;

    std::cout << "\n" << std::string(ANCHO_TICKET, '=') << "\n";
    std::cout << "          TICKET DE COMPRA\n";
    std::cout << std::string(ANCHO_TICKET, '=') << "\n";
    std::cout << std::setw(ANCHO_ETIQUETA) << "Producto:" << nombre << "\n";
    std::cout << std::setw(ANCHO_ETIQUETA) << "Precio:" << "$" << precio << "\n";
    std::cout << std::setw(ANCHO_ETIQUETA) << "Cantidad:" << cantidad << "\n";
    std::cout << std::string(ANCHO_TICKET, '-') << "\n";
    std::cout << std::setw(ANCHO_ETIQUETA) << "Subtotal:" << "$" << subtotal << "\n";
    std::cout << std::setw(ANCHO_ETIQUETA) << etiquetaDescuento.str() << "$" << descuento << "\n";
    std::cout << std::setw(ANCHO_ETIQUETA) << etiquetaIVA.str() << "$" << iva << "\n";
    std::cout << std::string(ANCHO_TICKET, '-') << "\n";
    std::cout << std::setw(ANCHO_ETIQUETA) << "TOTAL:" << "$" << total << "\n";
    std::cout << std::string(ANCHO_TICKET, '-') << "\n";
    std::cout << std::setw(ANCHO_ETIQUETA) << "Le atendio:" << NOMBRE_VENDEDOR << "\n";
    std::cout << std::string(ANCHO_TICKET, '=') << "\n";
}