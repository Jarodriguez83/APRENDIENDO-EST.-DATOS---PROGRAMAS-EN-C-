#include <iostream>
#include <string>
using namespace std;

// Estructura para guardar los jugadores
struct Jugador {
    string nombre;
    Jugador* siguiente; // Apunta al siguiente jugador (lista circular)
    Jugador* anterior;  // Apunta al anterior jugador (para poder ir antihorario)
};

// Función para crear un nuevo jugador
Jugador* crearJugador(string nombre) {
    Jugador* nuevo = new Jugador;
    nuevo->nombre = nombre;
    nuevo->siguiente = nullptr;
    nuevo->anterior = nullptr;
    return nuevo;
}

// Función para mostrar la lista de jugadores actuales
void mostrarJugadores(Jugador* inicio) {
    if (inicio == nullptr) {
        cout << "No hay jugadores en la lista.\n";
        return;
    }
    Jugador* temp = inicio;
    do {
        cout << temp->nombre << " -> ";
        temp = temp->siguiente;
    } while (temp != inicio);
    cout << "(circular)\n";
}

// Función para mostrar los equipos
void mostrarEquipos(string equipo1[], int tam1, string equipo2[], int tam2) {
    cout << "\nEquipo 1: ";
    for (int i = 0; i < tam1; i++) {
        cout << equipo1[i] << " ";
    }
    cout << "\nEquipo 2: ";
    for (int i = 0; i < tam2; i++) {
        cout << equipo2[i] << " ";
    }
    cout << "\n";
}

// Función para eliminar a un jugador de la lista
Jugador* eliminarJugador(Jugador* inicio, Jugador* eliminado) {
    if (inicio == eliminado && inicio->siguiente == inicio) {
        // Si queda un solo jugador
        delete eliminado;
        return nullptr;
    }

    eliminado->anterior->siguiente = eliminado->siguiente;
    eliminado->siguiente->anterior = eliminado->anterior;

    Jugador* siguiente = eliminado->siguiente;
    if (eliminado == inicio) {
        inicio = siguiente;
    }

    delete eliminado;
    return inicio;
}

// Función principal del juego
void procedimientoSeleccion(Jugador* inicio, int total) {
    string equipo1[50];
    string equipo2[50];
    int tam1 = 0, tam2 = 0;
    bool turnoEquipo1 = true; // alterna entre equipo1 y equipo2

    Jugador* actual = inicio;

    while (inicio != nullptr) {
        mostrarJugadores(inicio);

        int dado;
        cout << "Ingrese valor del dado (1-6): ";
        cin >> dado;

        if (turnoEquipo1) {
            // Sentido horario
            for (int i = 0; i < dado; i++) {
                actual = actual->siguiente;
            }
            cout << "Seleccionado: " << actual->nombre << " para Equipo 1\n";
            equipo1[tam1++] = actual->nombre;
        } else {
            // Sentido antihorario
            for (int i = 0; i < dado; i++) {
                actual = actual->anterior;
            }
            cout << "Seleccionado: " << actual->nombre << " para Equipo 2\n";
            equipo2[tam2++] = actual->nombre;
        }

        Jugador* siguiente = actual->siguiente; // Guardamos el siguiente antes de eliminar
        inicio = eliminarJugador(inicio, actual);
        actual = siguiente;

        mostrarEquipos(equipo1, tam1, equipo2, tam2);

        // Cambiar de turno
        turnoEquipo1 = !turnoEquipo1;
    }
}

int main() {
    int n;
    cout << "Ingrese el numero de jugadores: ";
    cin >> n;

    // Crear lista circular de jugadores
    Jugador* inicio = nullptr;
    Jugador* ultimo = nullptr;

    for (int i = 0; i < n; i++) {
        string nombre;
        cout << "Ingrese nombre del jugador " << i+1 << ": ";
        cin >> nombre;

        Jugador* nuevo = crearJugador(nombre);

        if (inicio == nullptr) {
            inicio = nuevo;
            inicio->siguiente = inicio;
            inicio->anterior = inicio;
            ultimo = inicio;
        } else {
            nuevo->siguiente = inicio;
            nuevo->anterior = ultimo;
            ultimo->siguiente = nuevo;
            inicio->anterior = nuevo;
            ultimo = nuevo;
        }
    }

    // Preguntar jugador inicial
    string inicioNombre;
    cout << "Ingrese el nombre del jugador inicial: ";
    cin >> inicioNombre;

    Jugador* temp = inicio;
    while (temp->nombre != inicioNombre) {
        temp = temp->siguiente;
    }

    // Iniciar el procedimiento de selección
    procedimientoSeleccion(temp, n);

    return 0;
}
