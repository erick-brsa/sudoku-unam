#include <stdio.h>

typedef struct {
    int x;
    int y;
    int valor;
} Movimiento;

typedef struct {
    int modificaciones;
    int tablero[9][9];
    int juego[9][9];
    char nombre[20];
    Movimiento ultimo_movimiento;
} Registro;

void mostrar_menu(Registro *registro);

int leer_entero();

void imprimir_juego_inicial();

void imprimir_juego_actual();

void ingresar_valor();

void cambiar_valor();

void borrar_valor();

void rotar_juego();

void intercambiar_numeros();

void intercambiar_filas();

void guardar_juego();

// Cargar juego preexistente.
// Leer la matriz inicial del juego
// Leer otra matriz con el avance hasta el momento del usuario

// Guardar el avance del juego
// Guardar la matriz inicial del juego
// Guardar otra matriz con el avance hasta el momento del usuario

int main() {
    Registro registro;
    int opcion;

    printf("Ingrese su nombre:\n");
    scanf("%s", registro.nombre);

    do {
        mostrar_menu(&registro);
        opcion = leer_entero();
        switch (opcion) {
            case 1:
                imprimir_juego_actual();
                break;
            case 2:
                ingresar_valor();
                break;
            case 3:
                imprimir_juego_inicial();
                break;
            case 4:
                cambiar_valor();
                break;
            case 5:
                borrar_valor();
                break;
            case 6:
                rotar_juego();
                break;
            case 7:
                intercambiar_numeros();
                break;
            case 8:
                intercambiar_filas();
                break;
            case 9:
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
    printf("2. Ingresar valor en una casilla.\n");
    printf("3. Imprimir el tablero inicial.\n");
    printf("4. Cambiar un valor.\n");
    printf("5. Borrar un valor.\n");
    // Para estas opciones el juego debe estar resuelto
    printf("Opciones para modificar el juego: \n");
    printf("6. Rotar tablero.\n");
    printf("7. Intercambiar n%cmeros.\n", 163);
    printf("8. Intercambiar filas.\n");
    printf("9. Salir del juego.\n");
}

int leer_entero() {
    int numero;
    int esValido;
    do {
        esValido = (scanf("%d", &numero) == 1);
        if (!esValido) {
            printf("Error: Debes ingresar un n%cmero.\n", 163);
            while (getchar() != '\n');
        }
    } while (!esValido);
    return numero;
}

void imprimir_juego_inicial() {}

void imprimir_juego_actual() {}

void ingresar_valor() {}

void cambiar_valor() {}

void borrar_valor() {}

void rotar_juego() {}

void intercambiar_numeros() {}

void intercambiar_filas() {}

void guardar_juego() {}
