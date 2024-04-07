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
    int fila;
    int columna;
    int valor;
};

typedef struct Movimiento Movimiento;

struct Registro {
    int modificaciones;
    int juego_inicial[9][9];
    int juego_inicial_modificado[9][9];
    int juego[9][9];
    char nombre[20];
    struct Movimiento ultimo_movimiento;
};

typedef struct Registro Registro;

void mostrar_menu(Registro *registro);

int leer_entero();

void imprimir_juego(int matriz[9][9]);

void copiar_matriz(int origen[9][9], int destino[9][9]);

void ocultar_valores(Registro *registro, int resuelto[9][9]);

int validar_casilla(int fila, int columna);

int validar_fila(Registro *registro, int i, int valor);

int validar_columna(Registro *registro, int j, int valor);

int es_modificable(Registro *registro, int fila, int columna);

void ingresar_valor(Registro *registro);

void borrar_valor(Registro *registro);

void rotar_juego(Registro *registro);

void intercambiar_numeros(Registro *registro);

void intercambiar_filas(Registro *registro);

void intercambiar_columnas(Registro *registro);

void guardar_juego(Registro *registro);

void cargar_juego();

void nuevo_juego();

int main() {
    int opcion;

    do {
        printf("Seleccione una opci%cn:\n", 162);
        printf("1. Cargar juego preexistente.\n");
        printf("2. Nuevo juego.\n");
        printf("3. Salir.\n");
        opcion = leer_entero();

        switch (opcion) {
            case 1:
                cargar_juego();
                break;
            case 2:
                nuevo_juego();
                break;
            case 3:
                printf("Bye.\n");
                break;
            default:
                printf("Ingrese una opci%c v%clida.\n", 162, 160);
        }
    } while (opcion != 3);

    return 0;
}

void cargar_juego() {}

void nuevo_juego() {
    Registro registro;
    int opcion;
    int intercambiar;

    printf("Ingrese su nombre:\n");
    printf(">%c", 255);
    scanf("%s", registro.nombre);

    ocultar_valores(&registro, juego_resuelto);

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
                rotar_juego(&registro);
                break;
            case 6:
                intercambiar_numeros(&registro);
                break;
            case 7:
                intercambiar_filas(&registro);
                break;
            case 8:
                intercambiar_columnas(&registro);
                break;
            case 9:
                guardar_juego(&registro);
                break;
            default:
                printf("Ingrese una opci%c v%clida.\n", 162, 160);
                break;
        }
    } while (opcion != 9);
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
    printf("8. Intercambiar columnas.\n");
    printf("9. Guardar y volver al men%c inicial.\n", 163);
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

    copiar_matriz(registro->juego_inicial, registro->juego_inicial_modificado);
    copiar_matriz(registro->juego_inicial, registro->juego);
}

int validar_casilla(int fila, int columna) {
    if (fila < 0 || fila > 0 || columna < 0 || columna > 8) {
        return 0;
    }
    return 1;
}

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

int es_modificable(Registro *registro, int fila, int columna) {
    // Devuelve 1 si la casilla es modificable
    // Devuelve 0 si no si no se puede modificar
    return registro->juego_inicial_modificado[fila][columna] == 0;
}

void ingresar_valor(Registro *registro) {
    int fila, columna, valor;
    printf("Ingrese la fila (1-9):\n");
    fila = leer_entero() - 1;
    printf("Ingrese la columna (1-9):\n");
    columna = leer_entero() - 1;
    printf("Ingrese el valor:\n");
    valor = leer_entero();

    if (!validar_casilla(fila, columna)) {
        printf("Casilla no permitida.\n");
        return;
    }

    if (!es_modificable(registro, fila, columna)) {
        printf("Advertencia: No puedes modificar un valor del juego inicial.\n");
        return;
    }

    if (validar_fila(registro, fila, valor) && validar_columna(registro, columna, valor)) {
        Movimiento movimiento = {fila, columna, valor};
        registro->ultimo_movimiento = movimiento;
        registro->juego[fila][columna] = valor;
        registro->modificaciones++;
    }

    imprimir_juego(registro->juego);
}

void borrar_valor(Registro *registro) {
    int fila, columna;
    printf("Ingrese la fila (1-9):\n");
    fila = leer_entero() - 1;
    printf("Ingrese la columna (1-9):\n");
    columna = leer_entero() - 1;

    if (!validar_casilla(fila, columna)) {
        printf("Casilla no permitida.\n");
        return;
    }

    if (!es_modificable(registro, fila, columna)) {
        printf("Advertencia: No puedes borrar un valor del juego inicial.\n");
        return;
    }

    Movimiento movimiento = {fila, columna, 0};
    registro->ultimo_movimiento = movimiento;
    registro->juego[fila][columna] = 0;
    registro->modificaciones++;

    imprimir_juego(registro->juego);
}

void rotar_juego(Registro *registro) {
    int i, j, juego_rotado[9][9], juego_inicial_rotado[9][9];

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            juego_inicial_rotado[j][i] = registro->juego_inicial[8 - i][j];
            juego_rotado[j][i] = registro->juego[8 - i][j];
        }
    }

    copiar_matriz(juego_inicial_rotado, registro->juego_inicial_modificado);
    copiar_matriz(juego_rotado, registro->juego);
    imprimir_juego(registro->juego);
}

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
    // copiar_matriz(juego_intercambiado, registro->juego);
    ocultar_valores(registro, juego_intercambiado);
    imprimir_juego(registro->juego);
}

void intercambiar_filas(Registro *registro) {
    int temp, grupo, fila0, fila1, fila2, i;

    for (grupo = 0; grupo < 3; grupo++) {
        fila0 = grupo * 3;

        fila1 = fila0 + (rand() % 3);
        do {
            fila2 = fila0 + (rand() % 3);
        } while (fila1 == fila2);

        for (i = 0; i < 9; i++) {
            temp = registro->juego[fila1][i];
            registro->juego[fila1][i] = registro->juego[fila2][i];
            registro->juego[fila2][i] = temp;
            temp = registro->juego_inicial_modificado[fila1][i];
            registro->juego_inicial_modificado[fila1][i] = registro->juego_inicial_modificado[fila2][i];
            registro->juego_inicial_modificado[fila2][i] = temp;
        }
    }
    imprimir_juego(registro->juego);
}

void intercambiar_columnas(Registro *registro) {
    int temp, grupo, columna0, columna1, columna2, i;

    for (grupo = 0; grupo < 3; grupo++) {
        columna0 = grupo * 3;

        columna1 = columna0 + (rand() % 3);
        do {
            columna2 = columna0 + (rand() % 3);
        } while (columna1 == columna2);

        for (i = 0; i < 9; i++) {
            temp = registro->juego[i][columna1];
            registro->juego[i][columna1] = registro->juego[i][columna2];
            registro->juego[i][columna2] = temp;
            temp = registro->juego_inicial_modificado[i][columna1];
            registro->juego_inicial_modificado[i][columna1] = registro->juego_inicial_modificado[i][columna2];
            registro->juego_inicial_modificado[i][columna2] = temp;
        }
    }
    imprimir_juego(registro->juego);
}

void guardar_juego(Registro *registro) {}
