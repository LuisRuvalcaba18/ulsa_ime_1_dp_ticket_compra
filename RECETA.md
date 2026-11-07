# Receta: Ticket de compra

<!-- Escribe aquí tus recetas en pseudocódigo, ANTES de programar.
     Primero la receta del programa principal (main) y después una receta corta para cada módulo que vas a escribir tú.
     El primer paso de main es solo un ejemplo del formato; el resto es tuyo.
     Si las corriges después de probarlas a mano, deja aquí la versión final. -->

## Receta del programa principal (`main`)

<!-- Debe leerse casi igual que tu árbol de análisis descendente (sección 6 del README). -->

```text
1. MOSTRAR "=== Bienvenido a la tienda ==="
2. PEDIR los datos y VALIDAR su rango
   - nombre ← leerCadena("Nombre del producto: ")
   - precio ← leerDecimal("Precio: ")
     MIENTRAS precio <= 0 HACER volver a PEDIR el precio FIN MIENTRAS
   - cantidad ← leerEntero("Cantidad: ")
     MIENTRAS cantidad <= 0 HACER volver a PEDIR la cantidad FIN MIENTRAS
   - porcentajeDescuento ← leerDecimal("Descuento (%): ")
     MIENTRAS porcentajeDescuento < 0 O > 100 HACER volver a PEDIR el descuento FIN MIENTRAS
3. CALCULAR los importes
   - subtotal ← calcularSubtotal(precio, cantidad)
   - descuento ← calcularDescuento(subtotal, porcentajeDescuento)
   - iva ← calcularIVA(subtotal - descuento)
   - total ← subtotal - descuento + iva
4. IMPRIMIR el ticket con imprimirTicket(nombre, precio, cantidad, subtotal,
                                         porcentajeDescuento, descuento, iva, total)
```

## Recetas de los módulos

<!-- Para cada módulo: qué recibe, qué hace y qué devuelve. -->
MODULO calcularIVA(base)
    TOMAR la tasa TASA_IVA (16.0)
    CALCULAR el porcentaje de la base con calcularPorcentaje(base, TASA_IVA)
    DEVOLVER el monto del IVA
FIN MODULO

### `calcularIVA`

```text
MODULO calcularIVA(base)
    TOMAR la tasa TASA_IVA (16.0)
    CALCULAR el porcentaje de la base con calcularPorcentaje(base, TASA_IVA)
    DEVOLVER el monto del IVA
FIN MODULO
```

### `imprimirTicket`

```text
MODULO imprimirTicket(nombre, precio, cantidad, subtotal,
                      porcentajeDescuento, descuento, iva, total)
    ARMAR las etiquetas "Descuento (X%):" e "IVA (Y%):"
    CONFIGURAR la salida a 2 decimales y texto alineado a la izquierda
    DIBUJAR las lineas y MOSTRAR el titulo "TICKET DE COMPRA"
    MOSTRAR producto, precio y cantidad
    MOSTRAR subtotal, descuento e IVA
    MOSTRAR el total
    MOSTRAR "Le atendio:" con la constante NOMBRE_VENDEDOR
    (no DEVOLVER nada: es un procedimiento)
FIN MODULO
```

### `calcularPorcentaje` (Fase 4)

```text
MODULO calcularPorcentaje(base, porcentaje)
    MULTIPLICAR la base por el porcentaje
    DIVIDIR entre 100
    DEVOLVER el resultado
FIN MODULO
```

### Otros módulos que agregues (por ejemplo, para tu reto)

```text
- PASAR porcentajeDescuento a imprimirTicket
- ARMAR la etiqueta "Descuento (X%):" con ostringstream, para que salga 10% y no 10.00%
- AUMENTAR ANCHO_ETIQUETA a 18 para mantener la alineacion
```
