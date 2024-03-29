#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int juego_resuelto[9][9] = {
        {6, 9, 4, 1, 5, 7, 8, 3, 2},
        {8, 1, 2, 3, 9, 6, 7, 4, 5},
        {3, 5, 7, 2, 8, 4, 1, 9, 6},
        {2, 6, 9, 4, 1, 5, 3, 7, 8},
        {5, 8, 1, 7, 6, 3, 4, 2, 9},
        {4, 7, 3, 9, 2, 8, 5, 6, 1},
        {1, 3, 5, 6, 7, 2, 9, 8, 4},
        {9, 4, 6, 8, 3, 1, 2, 5, 7},
        {7, 2, 8, 5, 4, 9, 6, 1, 3}
};

struct Movimiento {
    int x;
    int y;
    int valor;
};

typedef struct Movimiento Movimiento;

struct Registro {
    int modificaciones;
    int juego_inicial[9][9];
    int juego[9][9];
    char nombre[20];
    struct Movimiento ultimo_movimiento;
};

typedef struct Registro Registro;

void mostrar_menu(Registro *registro);

int leer_entero();

void imprimir_juego(int matriz[9][9]);

void copiar_matriz(int origen[9][9], int destino[9][9]);

void nuevo_juego(Registro *registro);

void ingresar_valor(Registro *registro);

void borrar_valor(Registro *registro);

void rotar_juego();

void intercambiar_numeros();

void intercambiar_filas();

void guardar_juego();

int main() {
    Registro registro;
    int opcion;

    nuevo_juego(&registro);

    printf("Ingrese su nombre:\n");
    printf(">%c", 255);
    scanf("%s", registro.nombre);

    do {
        mostrar_menu(&registro);
        opcion = leer_entero();
        switch (opcion) {
            case 1:
                imprimir_juego(registro.juego);
                break;
            case 2:
                imprimir_juego(registro.juego_inicial);
                break;
            case 3:
                ingresar_valor(&registro);
                break;
            case 4:
                borrar_valor(&registro);
                break;
            case 5:
                rotar_juego();
                break;
            case 6:
                intercambiar_numeros();
                break;
            case 7:
                intercambiar_filas();
                break;
            case 8:
                printf("Bye.\n");
                break;
            default:
                printf("Ingrese una opci%c v%clida.\n", 162, 160);
                break;
        }
    } while (opcion != 9);

    return 0;
}

void mostrar_menu(Registro *registro) {
    printf("Jugador: %s\n", registro->nombre);
    printf("Opciones para jugar:\n");
    printf("1. Imprimir estado actual del juego.\n");
    printf("2. Imprimir el tablero inicial.\n");
    printf("3. Ingresar un valor en una casilla.\n");
    printf("4. Borrar un valor.\n");
    // Para estas opciones el juego debe estar resuelto
    printf("Opciones para modificar el juego: \n");
    printf("5. Rotar tablero.\n");
    printf("6. Intercambiar n%cmeros.\n", 163);
    printf("7. Intercambiar filas.\n");
    printf("8. Salir del juego.\n");
}

int leer_entero() {
    int numero;
    int esValido;
    do {
        printf(">%c", 255);
        esValido = (scanf("%d", &numero) == 1);
        if (!esValido) {
            printf("Error: Debes ingresar un n%cmero.\n", 163);
            while (getchar() != '\n');
        }
    } while (!esValido);
    return numero;
}

void copiar_matriz(int origen[9][9], int destino[9][9]) {
    int *ptr_origen = (int *) origen;
    int *ptr_destino = (int *) destino;
    for (int i = 0; i < 9 * 9; i++) {
        *ptr_destino = *ptr_origen;
        ptr_destino++;
        ptr_origen++;
    }
}

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

void nuevo_juego(Registro *registro) {
    int i, j, x, contador;
    srand(time(NULL));

    copiar_matriz(juego_resuelto, registro->juego_inicial);

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

void ingresar_valor(Registro *registro) {
    int i, j, x;
    printf("Ingrese la fila (1-9):\n");
    i = leer_entero() - 1;
    printf("Ingrese la columna (1-9):\n");
    j = leer_entero() - 1;
    printf("Ingrese el valor:\n");
    x = leer_entero();
    registro->juego[i][j] = x;
}

void borrar_valor(Registro *registro) {
    int i, j;
    printf("Ingrese la fila (1-9):\n");
    i = leer_entero() - 1;
    printf("Ingrese la columna (1-9):\n");
    j = leer_entero() - 1;
    registro->juego[i][j] = 0;
}

void rotar_juego() {}

void intercambiar_numeros() {}

void intercambiar_filas() {}

void guardar_juego() {}
