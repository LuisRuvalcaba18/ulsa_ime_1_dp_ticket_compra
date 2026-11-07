# Práctica: Ticket de compra

> Llena cada sección en la fase que se indica. Las instrucciones completas están en `PRACTICA.md`.
> Si una pregunta no aplica (por ejemplo, no hiciste el Experimento C o no tuviste dudas), escribe `No aplica`. Si te sobran filas en una tabla, bórralas.

## 1. Descripción del problema (Fase 1)

Programa en C++ que pide el nombre, el precio, la cantidad y el porcentaje de descuento de un producto. Con eso calcula el subtotal, el descuento, el IVA (16 %) y el total, y los muestra en un ticket de compra alineado. En la vida real serviría como el ticket de una papelería o una tienda pequeña.

## 2. Entradas y salidas (Fase 1)

**Entradas:**

| Entrada | Tipo de dato | Función de `utilerias.h` |
|---|---|---|
| descuento (%) | `double` | `leerDecimal` |
| cantidad | `int` | `leerEntero` |
| nombre | `std::string` | `leerCadena` |
| precio | `double` | `leerDecimal` |

**Salida** (¿qué datos muestra el ticket?):
Nombre del producto, precio, cantidad, subtotal, descuento (con su porcentaje), IVA (16 %), total y la línea "Le atendio".

**¿El IVA se calcula sobre el subtotal o sobre lo que queda después del descuento? ¿Por qué?**
Sobre lo que queda después del descuento (subtotal − descuento). En un ticket real el descuento baja el precio que se cobra, y el IVA se aplica sobre el precio final de venta. Compruebo con el caso 2: (100 − 10) × 0.16 = 14.40.

## 3. Restricciones e invariante (Fases 1 y 2)

**Restricciones** (¿qué debe cumplirse?): el precio y la cantidad deben ser mayores que 0, el descuento debe estar entre 0 y 100 y el nombre no puede estar vacío.

| Dato | ¿Qué valores son válidos? | ¿Por qué? |
|---|---|---|
| Nombre del producto | Texto con al menos un carácter que no sea espacio; puede tener espacios en medio | Un ticket sin nombre no identifica qué se compró; `leerCadena` ya lo revisa |
| Precio | Número decimal mayor que 0 | Un producto gratis o con precio negativo no tiene sentido en una venta |
| Cantidad | Entero mayor que 0 | No se puede comprar 0 piezas, ni media pieza, ni piezas negativas |
| Descuento (%) | Número entre 0 y 100 (incluidos) | Menos de 0 sería un recargo y más de 100 regalaría dinero |

**¿Qué hace mi programa si el usuario escribe un dato fuera de rango?**
Muestra un mensaje de error y vuelve a pedir el dato con un ciclo `while`, hasta que el valor sea válido. Si ni siquiera es un número, `leerDecimal` o `leerEntero` lo rechazan y lo piden de nuevo.

**¿Puede el total salir negativo? ¿Por qué?**
No. El descuento máximo es 100 %, así que el descuento nunca supera al subtotal. La base del IVA (subtotal − descuento) es ≥ 0, el IVA es ≥ 0 y por lo tanto el total es ≥ 0.

**Invariante 1** (después del ciclo que valida el precio, ¿qué es siempre cierto sobre `precio`?):
`precio > 0`. El ciclo solo termina cuando la condición `precio <= 0` es falsa.

**Invariante 2** (¿qué relación se cumple siempre entre el subtotal, el descuento, el IVA y el total?):
`total = subtotal − descuento + IVA`, con `0 ≤ descuento ≤ subtotal`, y el IVA siempre se calcula sobre `(subtotal − descuento)`. El descuento nunca puede ser mayor que el subtotal.

## 4. Casos resueltos a mano (Fase 1)

| Caso | Nombre | Precio | Cantidad | Descuento (%) | Subtotal | Descuento ($) | IVA | Total |
|---|---|---|---|---|---|---|---|---|
| 1 (sin descuento) | Caja de colores | 25 | 4 | 0 | 100.00 | 0.00 | 16.00 | 116.00 |
| 2 (con descuento) | Cuaderno | 50 | 2 | 10 | 100.00 | 10.00 | 14.40 | 104.40 |
| 3 (precio con centavos) | Pluma | 19.99 | 1 | 0 | 19.99 | 0.00 | 3.20 | 23.19 |

## 5. Tipo de dato abstracto (Fase 1)

| TDA | Datos (¿qué tiene?) | Operaciones (¿qué se puede hacer con él?) |
|---|---|---|
| Producto | nombre (texto), precio (decimal), cantidad (entero) | calcular su subtotal |
| Ticket | producto, porcentaje de descuento, subtotal, descuento, IVA, total, vendedor | calcular el total, imprimirse |

**Jerarquías:** una tienda vende productos por pieza (un cuaderno) y productos por peso (un kilo de tortillas). ¿Los dos son productos? ¿Qué datos tienen en común y cuál cambia?
Sí, los dos son productos. Tienen en común el nombre y el precio (por pieza o por kilo). Lo que cambia es la cantidad: por pieza es un entero (2 cuadernos) y por peso es decimal (1.5 kg), y también cambia la unidad.

## 6. Análisis descendente (Fase 2)

```
Generar ticket de compra
├── 1. Mostrar bienvenida
├── 2. Pedir los datos
│     ├── 2.1 Pedir el nombre del producto (ya existe: leerCadena)
│     ├── 2.2 Pedir el precio (y validar que sea mayor que 0) (ya existe: leerDecimal)
│     ├── 2.3 Pedir la cantidad (y validar que sea entero mayor que 0) (ya existe: leerEntero)
│     └── 2.4 Pedir el descuento (y validar que esté entre 0 y 100) (ya existe: leerDecimal)
├── 3. Calcular los importes
│     ├── 3.1 Calcular el subtotal (ya existe: calcularSubtotal)
│     ├── 3.2 Calcular el descuento (ya existe: calcularDescuento)
│     ├── 3.3 Calcular el IVA sobre (subtotal - descuento) (calcularIVA)
│     └── 3.4 Calcular el total = subtotal - descuento + IVA
└── 4. Imprimir el ticket (imprimirTicket)
```

**Análisis ascendente: ¿qué partes del árbol ya estaban resueltas por una función que existe? ¿Cuáles?**
La lectura de datos (2.1 a 2.4) ya estaba resuelta por `leerCadena`, `leerDecimal` y `leerEntero` de `utilerias.h`; solo agregué los ciclos de validación de rango. En `ticket.h` ya existían `calcularSubtotal` (3.1) y `calcularDescuento` (3.2, con un error que corregí).

**¿Alguna parte del árbol hacía más de una cosa? ¿Cómo la dividiste?**
Al principio "Calcular los importes" incluía todo junto. La dividí en subtotal, descuento, IVA y total para que cada hoja haga una sola cosa. También separé "pedir los datos" de "imprimir", para que las funciones de cálculo no impriman ni pidan nada.

## 7. Módulos y receta (Fase 2)

| Módulo | ¿Qué recibe? | ¿Qué devuelve? | ¿Función o procedimiento? |
|---|---|---|---|
| `calcularSubtotal` | precio, cantidad | el subtotal | Función |
| `calcularDescuento` | subtotal, porcentaje | el monto del descuento | Función |
| `calcularIVA` | la base (subtotal − descuento) | el monto del IVA | Función |
| `imprimirTicket` | nombre, precio, cantidad, subtotal, porcentaje de descuento, descuento, IVA y total | nada (solo imprime) | Procedimiento |
| `calcularPorcentaje` | una base y un porcentaje | ese porcentaje de la base | Función |

**¿Probé mi receta a mano con mis 3 casos?** Sí
**¿Tuve que corregirla? ¿Qué cambié?** Sí. Al principio calculaba el IVA sobre el subtotal; al probar el caso 2 a mano no coincidía con 14.40, así que cambié el paso 3.3 para que use (subtotal − descuento).

## 8. Cómo compilar y ejecutar (Fase 3)

Compilar (desde la carpeta del proyecto):

```bash
g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp -o ticket
```

Ejecutar en macOS:

```bash
./ticket
```

Ejecutar en Windows:

```bash
.\ticket.exe
```

**¿En qué sistema operativo trabajé?** Windows

## 9. Ejemplo de ejecución (Fase 3)

```
=== Bienvenido a la tienda ===
Nombre del producto: Cuaderno
Precio: 50
Cantidad: 2
Descuento (%): 10

====================================
          TICKET DE COMPRA
====================================
Producto:         Cuaderno
Precio:           $50.00
Cantidad:         2
------------------------------------
Subtotal:         $100.00
Descuento (10%):  $10.00
IVA (16%):        $14.40
------------------------------------
TOTAL:            $104.40
------------------------------------
Le atendio:       TU NOMBRE AQUI
====================================
```

## 10. De la receta al código (Fase 3)

| Paso de la receta | Módulo o instrucción de C++ que lo implementa |
|---|---|
| 1. Mensaje de bienvenida | `std::cout << "=== Bienvenido a la tienda ===\n";` |
| 2.1 Pedir el nombre | `nombre = leerCadena("Nombre del producto: ");` |
| 2.2 Pedir y validar el precio | `leerDecimal` + `while (precio <= 0)` |
| 2.3 Pedir y validar la cantidad | `leerEntero` + `while (cantidad <= 0)` |
| 2.4 Pedir y validar el descuento | `leerDecimal` + `while (porcentajeDescuento < 0 \|\| porcentajeDescuento > 100)` |
| 3.1 Subtotal | `calcularSubtotal(precio, cantidad)` |
| 3.2 Descuento | `calcularDescuento(subtotal, porcentajeDescuento)` |
| 3.3 IVA | `calcularIVA(subtotal - descuento)` |
| 3.4 Total | `total = subtotal - descuento + iva;` |
| 4. Imprimir el ticket | `imprimirTicket(...)` |

**¿Hubo algún paso de mi receta que me costó traducir a C++? ¿Cuál y por qué?**
El formato del ticket (paso 4), porque hay que combinar `std::fixed`, `std::setprecision`, `std::setw` y `std::left`, y mostrar el porcentaje sin `.00` ("10%" y no "10.00%"). Lo resolví armando las etiquetas con `std::ostringstream`, que tiene su propio formato.

**Formato del ticket: ¿qué ancho usé en `std::setw` y por qué? ¿Qué pasa si uso un número menor que el largo de la etiqueta más larga?**
Usé 18 (constante `ANCHO_ETIQUETA`). La etiqueta más larga es `Descuento (10%):` con 16 caracteres, y 18 deja dos espacios de separación. Si usara un número menor que ese largo, la etiqueta ocuparía más que el espacio reservado, no se rellenaría y el valor quedaría pegado o desalineado con el resto de las líneas.

**¿Convertí el ancho de las líneas del ticket (36) en una constante? ¿Cómo la llamé? Si no, ¿por qué?**
Sí, la llamé `ANCHO_TICKET`, en `ticket.h`. Así, si quiero un ticket más ancho, cambio una sola línea.

## 11. Experimentos y depuración (Fase 3)

**Experimento A: depuración de `calcularDescuento`**

| Paso de depuración | Lo que hice o encontré |
|---|---|
| 1. Reproduce: ¿con qué datos falló? | Con 0 % el ticket salía bien. Con Cuaderno, 50, 2 y 10 % el descuento salía enorme y el total negativo. |
| 2. Aísla: ¿qué valor intermedio estaba mal? (salidas `[DEBUG]`) | Con `[DEBUG]` vi que el subtotal era 100.00 (correcto) pero el descuento era 1000.00 en lugar de 10.00. |
| 3. Explica: ¿cuál era la causa? | La función hacía `subtotal * porcentaje` sin dividir entre 100: multiplicaba por 10 en lugar de por 0.10. |
| 4. Corrige: ¿qué cambiaste? | Ahora el cálculo es `subtotal * porcentaje / 100.0` (a través de `calcularPorcentaje`). Volví a probar todos los casos. |
| 5. Limpia: ¿comentaste tus salidas `[DEBUG]`? | Sí, las comenté con `//` y verifiqué que el ticket final no las muestra. |

**La prueba con 0 % pasó aunque la función tenía un error. ¿Qué me enseña eso sobre elegir mis casos de prueba?**
Que 0 por cualquier número es 0, así que ese caso esconde el error. Hay que elegir casos con valores "normales" (como 10 %) y también casos límite (0 % y 100 %), no solo el caso más fácil.

**Experimento B: al cambiar el IVA a 8 %, ¿cuántas líneas tuve que cambiar? ¿Qué mejoraría?**
Una sola línea: `const double TASA_IVA = 8.0;` en `ticket.h`. Como la tasa es una constante con nombre y no un número mágico, no hay nada más que mejorar.

**¿Mi ticket seguía diciendo `IVA (16%)`? ¿Qué hice al respecto?**
No, dijo `IVA (8%)`, porque la etiqueta se arma con la constante `TASA_IVA` y no está escrita a mano. Al terminar regresé la constante a 16.0.

**Experimento C (opcional): al cambiar el parámetro dentro de `calcularIVA`, ¿cambió la variable de `main()`? ¿Por qué?**
No aplica.

## 12. La constante "Le atendio" (Fase 3)

**¿Dónde definí la constante con mi nombre?** (marca una)
- [ ] Constante local dentro de `imprimirTicket`
- [x] Constante a nivel de la librería, en `ticket.h`
- [ ] Función que siempre devuelve la misma cadena

**¿Por qué elegí esa opción?**
Porque el dato queda en un solo lugar y cualquier parte del programa que incluya `ticket.h` puede usarlo, sin depender de una sola función. Es más simple que crear una función para algo que no cambia.

**¿Qué otras partes del programa podrían necesitar el nombre de quien atiende? (un mensaje de bienvenida, un ticket de devolución...)**
El mensaje de bienvenida ("Le atiende..."), un ticket de devolución, un reporte de ventas del día o un registro de la caja.

**Si mañana atiende otra persona, ¿en cuántos lugares tengo que cambiar el nombre?**
En uno solo: la línea de `NOMBRE_VENDEDOR` en `ticket.h`.

**Si el nombre se leyera del teclado o de un archivo, ¿cuánto código tendría que cambiar con mi opción?**
Un poco más que con una función: tendría que quitar el `const` y leer el nombre en `main()` (o dejar una variable global). Con la opción de la función, solo cambiaría el cuerpo de esa función y nadie más se enteraría.

## 13. Tabla de pruebas (Fase 4)

| # | Caso | Esperado (subtotal / descuento / IVA / total) | Obtenido | ¿Pasó? |
|---|---|---|---|---|
| 1 | Sin descuento | 100.00 / 0.00 / 16.00 / 116.00 | 100.00 / 0.00 / 16.00 / 116.00 | Sí |
| 2 | Con descuento | 100.00 / 10.00 / 14.40 / 104.40 | 100.00 / 10.00 / 14.40 / 104.40 | Sí |
| 3 | Descuento de 15 % | 600.00 / 90.00 / 81.60 / 591.60 | 600.00 / 90.00 / 81.60 / 591.60 | Sí |
| 4 | Precio con centavos | 19.99 / 0.00 / 3.20 / 23.19 | 19.99 / 0.00 / 3.20 / 23.19 | Sí |
| 5 | Descuento total | 90.00 / 90.00 / 0.00 / 0.00 | 90.00 / 90.00 / 0.00 / 0.00 | Sí |
| 6 | Precio inválido | vuelve a pedir el precio dos veces; 40.00 / 0.00 / 6.40 / 46.40 | Pidió el precio dos veces más; 40.00 / 0.00 / 6.40 / 46.40 | Sí |
| 7 | Cantidad inválida | vuelve a pedir la cantidad dos veces; 20.00 / 0.00 / 3.20 / 23.20 | Pidió la cantidad dos veces más (0 y 2.5 rechazados); 20.00 / 0.00 / 3.20 / 23.20 | Sí |
| 8 | Descuento inválido | vuelve a pedir el descuento dos veces; 100.00 / 20.00 / 12.80 / 92.80 | Pidió el descuento dos veces más; 100.00 / 20.00 / 12.80 / 92.80 | Sí |
| 9 | Texto en el precio | vuelve a pedir el precio una vez; 100.00 / 0.00 / 16.00 / 116.00 | Pidió el precio una vez más; 100.00 / 0.00 / 16.00 / 116.00 | Sí |
| 10 | Nombre con espacios | muestra el nombre completo; 25.50 / 0.00 / 4.08 / 29.58 | Mostró "Goma de borrar"; 25.50 / 0.00 / 4.08 / 29.58 | Sí |
| 11 | Nombre vacío | vuelve a pedir el nombre una vez; 12.00 / 0.00 / 1.92 / 13.92 | Pidió el nombre una vez más; 12.00 / 0.00 / 1.92 / 13.92 | Sí |
| 12 | Caso propio 1: Lápiz, 7.50, 3, 20 % | 22.50 / 4.50 / 2.88 / 20.88 | 22.50 / 4.50 / 2.88 / 20.88 | Sí |
| 13 | Caso propio 2: Dulce, 0.01, 1, 0 % (precio mínimo) | 0.01 / 0.00 / 0.00 / 0.01 | 0.01 / 0.00 / 0.00 / 0.01 | Sí |

**En el caso 4 el IVA real es 3.1984. ¿Por qué mi ticket muestra 3.20?**
Porque `std::setprecision(2)` con `std::fixed` solo cambia cómo se muestra el número, redondeándolo a dos decimales. La variable sigue valiendo 3.1984.

**En el caso 10, ¿el ticket siguió alineado? Si no, ¿qué corregí?**
Sí, porque `std::setw` solo afecta a la etiqueta y el nombre se imprime después, así que un nombre más largo no mueve las columnas.

## 14. Generalización (Fase 4)

**¿Qué cálculo hacen `calcularDescuento` y `calcularIVA`? ¿Qué cambia entre una y otra?**
Las dos calculan un porcentaje de una cantidad: el descuento es un porcentaje del subtotal y el IVA es un porcentaje de la base (subtotal − descuento). La operación es la misma; solo cambian los datos (la base y el porcentaje).

**Receta de `calcularPorcentaje`** (también va en `RECETA.md`):

```text
MODULO calcularPorcentaje(base, porcentaje)
    resultado ← base * porcentaje / 100
    DEVOLVER resultado
FIN MODULO
```

**¿Cómo quedaron el descuento y el IVA después del cambio?**
`calcularDescuento(subtotal, porcentaje)` devuelve `calcularPorcentaje(subtotal, porcentaje)` y `calcularIVA(base)` devuelve `calcularPorcentaje(base, TASA_IVA)`. Ya no repiten la fórmula.

**¿Volví a correr toda la tabla de pruebas después del cambio? ¿Todo siguió pasando?**
Sí, corrí los 13 casos (prueba de regresión) y todos siguieron pasando.

**¿Agregué `calcularPorcentaje` a mi tabla de módulos (sección 7)?** Sí

**¿En qué otro programa podría reutilizar `calcularPorcentaje`?**
En una calculadora de propinas, de comisiones de ventas, de intereses o en el porcentaje de batería de un robot.

## 15. Revisión de calidad (Fase 4)

| Principio | Pregunta | ¿Lo cumple? | Evidencia |
|---|---|---|---|
| Correcto | ¿Pasa todas las pruebas de la tabla? | Sí | Los 13 casos de la sección 13 pasaron |
| Robusto | ¿Resiste datos inválidos sin fallar ni terminar? | Sí | Los casos 6 a 9 y 11 vuelven a pedir el dato sin fallar |
| Legible | ¿Otra persona entiende tu código sin que se lo expliques? | Sí | Nombres claros (`calcularIVA`, `imprimirTicket`) y comentarios `// Paso N` |
| Modular | ¿Cada función hace una sola cosa? | Sí | Las funciones de cálculo no imprimen ni piden datos; `imprimirTicket` solo imprime |
| Sin números mágicos | ¿Los valores fijos tienen nombre? | Sí | `TASA_IVA`, `ANCHO_TICKET`, `ANCHO_ETIQUETA`, `NOMBRE_VENDEDOR` |
| Fácil de mantener | Si cambia el IVA o quien atiende, ¿cuántas líneas cambias? | Sí | Una línea en cada caso, en `ticket.h` |
| Reutilizable | ¿Alguna de tus funciones serviría en otro programa? | Sí | `calcularPorcentaje` sirve para propinas, comisiones, etc. |

## 16. Reto obligatorio (Fase 4)

**¿Qué reto elegí?** (número y nombre; el 4 no cuenta como obligatorio) Reto 1: mostrar el porcentaje de descuento aplicado en el ticket.

**¿Por qué lo elegí?**
Porque era el que mejor se relaciona con lo visto de formato de salida y me permitió practicar `std::setw` y `std::ostringstream`.

**¿Cómo lo resolví? ¿Qué módulos agregué o cambié?**
Cambié `imprimirTicket` para que reciba también el porcentaje de descuento. Armé la etiqueta `Descuento (10%):` con un `std::ostringstream`, que tiene su propio formato y no hereda `std::fixed`, así el porcentaje sale como `10%` y no como `10.00%`. Subí `ANCHO_ETIQUETA` a 18 para que quepa la etiqueta más larga. Antes de programarlo agregué los pasos a `RECETA.md`.

**¿Hice algún otro reto opcional? ¿Cuál?**
No aplica.

## 17. Bitácora de mejoras (Fase 4)

| # | ¿Qué falló o qué quise mejorar? | ¿Qué cambié? | ¿Funcionó? |
|---|---|---|---|
| 1 | `calcularDescuento` daba 1000 en lugar de 10 con 10 % | Dividí entre 100 (con `calcularPorcentaje`) | Sí |
| 2 | El IVA se calculaba sobre el subtotal y no cuadraba con el caso 2 | Lo calculo sobre (subtotal − descuento) y corregí la receta | Sí |

## 18. Dudas para el profesor (Fase 3)

| Duda | Lo que ya intenté |
|---|---|
| ¿Qué pasa con la alineación si el porcentaje de descuento tiene decimales, como 12.5 %? | Probé con 10 % y 100 % y quedan alineados; con 12.5 % la etiqueta mide 18 caracteres y ocupa todo el `setw(18)`. |

## 19. Reflexión final

**¿Qué aprendí con esta práctica?**
A dividir un programa en módulos con una sola tarea, a escribir primero la receta y a depurar de forma ordenada con salidas `[DEBUG]`. También aprendí a usar constantes y a generalizar con `calcularPorcentaje`.

**Ahora que terminé, ¿qué cambiaría de mi proceso?**
Probaría con más casos desde el inicio, no solo con 0 %, y escribiría la tabla de pruebas antes de programar.

**¿Qué fue lo más difícil y cómo lo resolví?**
El formato del ticket, sobre todo mostrar el porcentaje sin los decimales de `std::fixed`. Lo resolví armando la etiqueta con un `std::ostringstream`.

**¿Qué pregunta me quedó sin responder?**
Cómo se manejarían varios productos en un mismo ticket y qué módulos habría que cambiar.

**Comparado con las prácticas anteriores, donde todo estaba en `main()`, ¿dividir el programa en módulos me facilitó o me complicó el trabajo? ¿Por qué?**
Me facilitó el trabajo. Cuando un total salía mal, pude revisar cada función por separado y encontrar rápido el módulo con el error. Al principio costó más planear, pero ahorró tiempo al depurar y generalizar.

**¿Cómo encontré el error de `calcularDescuento`? ¿Lo habría encontrado si solo hubiera probado sin descuento?**
Lo encontré probando con 10 % y mostrando con `[DEBUG]` los valores intermedios: el subtotal estaba bien y el descuento no. Si solo hubiera probado sin descuento no lo habría encontrado, porque 0 × cualquier número da 0.

## 20. Commits (Fase 5)

**¿Cuántos commits hice durante la práctica?** [ESCRIBE AQUÍ TU NÚMERO REAL DE COMMITS]

**Si hice menos de 3, ¿por qué?**
No aplica.

## 21. Lista de verificación antes de entregar (Fase 5)

- [x] Llené las secciones 1 a 20 (no quedan `_____`; escribí `No aplica` donde corresponde)
- [x] Completé el árbol de análisis descendente y la tabla de módulos
- [x] Escribí en `RECETA.md` la receta de `main` y la de cada módulo, antes de programar
- [x] Cada bloque de `main.cpp` tiene su comentario `// Paso N`, de acuerdo con mi receta
- [x] Corregí el error de `calcularDescuento` y documenté cómo lo encontré
- [x] Hice los Experimentos A y B y dejé el código correcto al terminar
- [x] Mi ticket se ve alineado y termina con la línea "Le atendio:", leída de una constante
- [x] Justifiqué dónde definí la constante con mi nombre
- [x] Escribí `calcularPorcentaje` y volví a correr todas las pruebas
- [x] Hice al menos uno de los retos y lo documenté
- [x] No queda ninguna salida `[DEBUG]` activa
- [x] Mi programa compila sin advertencias
- [x] Probé todos los casos de la tabla
- [x] Revisé los principios de calidad de mi programa
- [x] No modifiqué `utilerias.h`
- [x] Tengo al menos 3 commits con mensajes claros (o justifiqué por qué no)
- [x] Hice `git push` y verifiqué mi fork en GitHub
- [x] Mi fork se llama `ulsa_ime_1_dp_ticket_compra`, mis módulos están en `include/ticket.h` y mi programa principal en `src/main.cpp`
- [x] Entregué el enlace de mi fork en Classroom