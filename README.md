# Sudoku

Primer proyecto de Estructura de Datos y Algoritmos I.

## Introducción

El Sudoku es un rompecabezas lógico numérico. Consiste en una cuadrícula de 9x9 casillas, dividida en subgrupos de 3x3 llamados regiones. El objetivo del Sudoku es llenar la cuadrícula con dígitos del 1 al 9, de modo que cada fila, columna y región contenga exactamente una vez cada uno de los dígitos del 1 al 9.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/800px-Sudoku-by-L2G-20050714.svg.png" alt="Tablero de sudoku" width="200" height="200">

## Documentación

#### Bibliotecas

Para garantizar el correcto funcionamiento del programa, se requieren las siguientes bibliotecas estándar de C:

```c
#include <stdio.h>      // Biblioteca estándar de entrada/salida
#include <stdlib.h>     // Biblioteca estándar para gestión de memoria y otras utilidades
#include <time.h>       // Biblioteca estándar para manejo de fechas y horas
```

#### Definición de tipos

La estructura de datos `Movimiento` almacena información relacionada con un movimiento realizado por un jugador. Esta estructura contiene tres campos:

* `fila`: Representa la fila donde se realizó el movimiento.
* `columna`: Representa la columna donde se realizó el movimiento.
* `valor`: Almacena el valor asociado a la casilla.

```c
struct Movimiento {
    int fila;
    int columna;
    int valor;
};

typedef struct Movimiento Movimiento;
```

La estructura de datos `Registro` se utiliza para almacenar información relacionada con cada juego creado. Esta estructura contiene cinco campos:

- `modificaciones`: Un entero que representa el número de modificaciones realizadas en el juego.
- `juego_inicial`: Una matriz de enteros de 9x9 que almacena el estado inicial del juego.
- `juego`: Una matriz de enteros de 9x9 que representa el estado actual del juego. En otras palabras, el progreso del jugador.
- `nombre`: Un arreglo de caracteres que almacena el nombre del jugador.
- `ultimo_movimiento`: Una estructura de tipo `Movimiento` que guarda información sobre el último movimiento realizado en el juego.


```c
struct Registro {
    int modificaciones;
    int juego_inicial[9][9];
    int juego[9][9];
    char nombre[20];
    Movimiento ultimo_movimiento;
};

typedef struct Registro Registro;
```

#### Funciones

La función `mostrar_menu` se encarga de imprimir en la consola un menú de opciones para que el jugador interactúe con el juego. Toma como argumento un puntero a una estructura `Registro` que contiene información sobre el juego actual.

```c
void mostrar_menu(Registro *registro) {
    printf("Jugador: %s\n", registro->nombre);
    printf("Opciones para jugar:\n");
    printf("1. Imprimir estado actual del juego.\n");
    printf("2. Imprimir el tablero inicial.\n");
    printf("3. Ingresar un valor en una casilla.\n");
    printf("4. Borrar un valor.\n");
    printf("Opciones para modificar el juego: \n");
    printf("5. Rotar tablero.\n");
    printf("6. Intercambiar números.\n");
    printf("7. Intercambiar filas.\n");
    printf("8. Volver al menú inicial.\n");
}
```

La función `leer_entero` se utiliza para leer un número entero ingresado por el usuario desde la consola. Realiza la validación del dato ingresado para garantizar que sea un número entero válido.

```c
int leer_entero() {
    int numero;
    int esValido;
    do {
        printf("> ");
        esValido = (scanf("%d", &numero) == 1);
        if (!esValido) {
            printf("Error: Debes ingresar un número.\n");
            while (getchar() != '\n');
        }
    } while (!esValido);
    return numero;
}
```

La función `copiar_matriz` se utiliza para copiar los elementos de una matriz de enteros de 9x9 desde una matriz de origen a una matriz de destino. Ambas matrices deben tener el mismo tamaño y estructura.

```c
void copiar_matriz(int origen[9][9], int destino[9][9]) {
    int *ptr_origen = (int *) origen;
    int *ptr_destino = (int *) destino;
    for (int i = 0; i < 9 * 9; i++) {
        *ptr_destino = *ptr_origen;
        ptr_destino++;
        ptr_origen++;
    }
}
```

La función `imprimir_juego` se utiliza para imprimir una matriz de juego en formato de tablero en la consola. La matriz representa un juego de Sudoku.

```c
void imprimir_juego(int matriz[9][9]) {
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < 9; i++) {
        if (i != 0 && i % 3 == 0) {
            printf("+-------+-------+-------+\n");
        }
        for (int j = 0; j < 9; j++) {
            if (j == 0 || j % 3 == 0) {
                printf("| ");
            }
            printf("%d ", matriz[i][j]);
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
}
```

La función `ocultar_valores` toma como argumentos un puntero a una estructura `Registro` y una matriz que representa un juego de Sudoku resuelto. Esta función oculta de 5 a 6 valores por fila en el juego resuelto, generando así un nuevo juego con casillas vacías para que el jugador pueda completarlo.  

```c
void ocultar_valores(Registro *registro, int resuelto[9][9]) {
    int i, j, x, contador;

    srand(time(NULL));

    copiar_matriz(resuelto, registro->juego_inicial);

    for (i = 0; i < 9; i++) {
        contador = rand() % 2 + 5; // Número aleatorio entre 5 y 6
        x = 0;
        while (x < contador) {
            j = rand() % 9;
            if (registro->juego_inicial[i][j] != 0) {
                registro->juego_inicial[i][j] = 0;
                x++;
            }
        }
    }

    copiar_matriz(registro->juego_inicial, registro->juego);
}
```

La función `validar_fila` se utiliza para verificar si un valor dado se repite en una fila específica de un juego de Sudoku representado por la matriz `juego` dentro de la estructura `Registro`.

```c
int validar_fila(Registro *registro, int fila, int valor) {
    int j;
    for (j = 0; j < 9; j++) {
        if (registro->juego[fila][j] == valor) {
            printf("Valor no permitido. %x se repite en la casilla %dx%d.\n", valor, fila + 1, j + 1);
            return 0;
        }
    }
    return 1;
}
```

La función `validar_columna` se utiliza para verificar si un valor dado se repite en una columna específica de un juego de Sudoku representado por la matriz `juego` dentro de la estructura `Registro`.

```c
int validar_columna(Registro *registro, int columna, int valor) {
    int i;
    for (i = 0; i < 9; i++) {
        if (registro->juego[i][columna] == valor) {
            printf("Valor no permitido. %x se repite en la casilla %dx%d.\n", valor, i + 1, columna + 1);
            return 0;
        }
    }
    return 1;
}
```

La función `ingresar_valor` se encarga de solicitar al usuario que ingrese una fila, una columna y un valor para insertar en el juego de Sudoku representado por la matriz `juego` dentro de la estructura `Registro`. Antes de realizar la inserción, valida si el valor ingresado cumple con las reglas del Sudoku utilizando las funciones `validar_fila` y `validar_columna`.

```c
void ingresar_valor(Registro *registro) {
    int fila, columna, valor;
    printf("Ingrese la fila (1-9):\n");
    fila = leer_entero() - 1;
    printf("Ingrese la columna (1-9):\n");
    columna = leer_entero() - 1;
    printf("Ingrese el valor:\n");
    valor = leer_entero();

    if (validar_fila(registro, fila, valor) && validar_columna(registro, columna, valor)) {
        Movimiento movimiento = {fila, columna, valor};
        registro->ultimo_movimiento = movimiento;
        registro->juego[fila][columna] = valor;
        registro->modificaciones++;
    }

    imprimir_juego(registro->juego);
}
```

La función `borrar_valor` se encarga de eliminar el valor de una casilla específica en el juego de Sudoku representado por la matriz `juego` dentro de la estructura `Registro`.

```c
void borrar_valor(Registro *registro) {
    int fila, columna;
    printf("Ingrese la fila (1-9):\n");
    fila = leer_entero() - 1;
    printf("Ingrese la columna (1-9):\n");
    columna = leer_entero() - 1;

    Movimiento movimiento = {fila, columna, 0};
    registro->ultimo_movimiento = movimiento;
    registro->juego[fila][columna] = 0;
    registro->modificaciones++;

    imprimir_juego(registro->juego);
}
```

La función `rotar_juego` se utiliza para rotar el juego de Sudoku representado por la matriz `juego` dentro de la estructura `Registro`. La rotación se realiza en sentido antihorario.


```c
void rotar_juego(Registro *registro) {
    int i, j, juego_rotado[9][9];

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            juego_rotado[j][i] = registro->juego_inicial[8 - i][j];
        }
    }

    copiar_matriz(juego_rotado, registro->juego);
    imprimir_juego(registro->juego);
}
```

La función `intercambiar_numeros` se encarga de intercambiar los números en el juego de Sudoku representado por la matriz `juego` dentro de la estructura `Registro`. Este intercambio se realiza de manera aleatoria, manteniendo las reglas del juego.

```c
void intercambiar_numeros(Registro *registro) {
    int i, j, num, valores[9], juego_intercambiado[9][9];
    srand(time(NULL));

    for (i = 0; i < 9; i++) {
        valores[i] = i + 1;
    }

    for (i = 8; i >= 0; i--) {
        j = rand() % (i + 1);
        num = valores[i];
        valores[i] = valores[j];
        valores[j] = num;
    }

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            juego_intercambiado[i][j] = valores[juego_resuelto[i][j] - 1];
        }
    }
    
    ocultar_valores(registro, juego_intercambiado);
    imprimir_juego(registro->juego);
}
```

## Integrantes

* [Briones Sánchez Erick Alan](https://github.com/erick-brsa)
* Escobar Hernández Angel Emiliano
* Gernandt Ortiz Elizabeth
* Guzman Carbajal Claudio
* Ramirez Gudiño JeanCarlo
* Rosete Manzano Karina Lizbeth
* Sánchez Soperanes Raúl Haziel