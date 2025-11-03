#include <iostream>
#include <cstdlib>   // Para rand()
#include <ctime>     // Para time(), localtime()
#include <sstream>   // Para convertir fecha/hora en string
using namespace std;

// Definición de la estructura para cada nodo
struct Nodo {
    int idLugar;
    float pH;
    float temperatura;
    string fecha;
    string hora;
    Nodo* siguiente; // Puntero al siguiente nodo (lista circular)
};

// Función que obtiene la fecha actual del sistema como string
string obtenerFecha() {
    time_t t = time(0);
    tm* ahora = localtime(&t);
    stringstream ss;
    ss << (ahora->tm_mday) << "/" 
       << (ahora->tm_mon + 1) << "/" 
       << (ahora->tm_year + 1900);
    return ss.str();
}

// Función que obtiene la hora actual del sistema como string
string obtenerHora() {
    time_t t = time(0);
    tm* ahora = localtime(&t);
    stringstream ss;
    ss << (ahora->tm_hour) << ":" 
       << (ahora->tm_min) << ":" 
       << (ahora->tm_sec);
    return ss.str();
}

// Función para crear un nuevo nodo
Nodo* crearNodo(int id) {
    Nodo* nuevo = new Nodo;
    nuevo->idLugar = id;
    // Valores iniciales aleatorios
    nuevo->pH = 6 + rand() % 3;           // valores entre 6 y 8
    nuevo->temperatura = 15 + rand() % 11; // valores entre 15 y 25
    nuevo->fecha = obtenerFecha();
    nuevo->hora = obtenerHora();
    nuevo->siguiente = nullptr;
    return nuevo;
}

// Función para mostrar la lista completa
void mostrarLista(Nodo* inicio) {
    if (inicio == nullptr) return;

    Nodo* temp = inicio;
    cout << "\n--- Lista de lugares y datos de muestras ---\n";
    do {
        cout << "Lugar " << temp->idLugar 
             << " | pH: " << temp->pH 
             << " | Temp: " << temp->temperatura << "°C"
             << " | Fecha: " << temp->fecha
             << " | Hora: " << temp->hora << endl;
        temp = temp->siguiente;
    } while (temp != inicio);
    cout << "---------------------------------------------\n";
}

// Función que simula el recorrido del barco
void recorrerBarco(Nodo* inicio) {
    if (inicio == nullptr) return;

    Nodo* temp = inicio;
    do {
        cout << "\n--- Lugar " << temp->idLugar << " ---\n";
        cout << "Valores anteriores -> pH: " << temp->pH 
             << ", Temp: " << temp->temperatura << "°C"
             << ", Fecha: " << temp->fecha
             << ", Hora: " << temp->hora << "\n";

        // Pedir nuevos valores
        float nuevoPH, nuevaTemp;
        string nuevaFecha, nuevaHora;

        cout << "Ingrese nuevo valor de pH: ";
        cin >> nuevoPH;
        cout << "Ingrese nueva temperatura: ";
        cin >> nuevaTemp;

        cin.ignore(); // Limpiar buffer
        cout << "Ingrese fecha (dd/mm/aaaa) o ENTER para usar actual: ";
        getline(cin, nuevaFecha);
        if (nuevaFecha.empty()) nuevaFecha = obtenerFecha();

        cout << "Ingrese hora (hh:mm:ss) o ENTER para usar actual: ";
        getline(cin, nuevaHora);
        if (nuevaHora.empty()) nuevaHora = obtenerHora();

        // Comparaciones con condiciones de advertencia grave
        if (abs(nuevoPH - temp->pH) > 1) {
            cout << "⚠ ADVERTENCIA GRAVE: Variacion en pH (antes: " 
                 << temp->pH << ", ahora: " << nuevoPH << ")\n";
        }
        if (abs(nuevaTemp - temp->temperatura) > 2) {
            cout << "⚠ ADVERTENCIA GRAVE: Variacion en Temperatura (antes: " 
                 << temp->temperatura << "°C, ahora: " << nuevaTemp << "°C)\n";
        }

        // Sobreescribir valores
        temp->pH = nuevoPH;
        temp->temperatura = nuevaTemp;
        temp->fecha = nuevaFecha;
        temp->hora = nuevaHora;

        // Pasar al siguiente nodo
        temp = temp->siguiente;

    } while (temp != inicio);

    cout << "\n--- Recorrido finalizado ---\n";
    mostrarLista(inicio); // Mostrar lista al terminar recorrido
}

int main() {
    srand(time(0)); // Inicializar generador de números aleatorios

    int n;
    cout << "Ingrese el numero de lugares donde se toman muestras: ";
    cin >> n;

    // Crear lista circular
    Nodo* inicio = nullptr;
    Nodo* ultimo = nullptr;

    for (int i = 1; i <= n; i++) {
        Nodo* nuevo = crearNodo(i);

        if (inicio == nullptr) {
            inicio = nuevo;
            inicio->siguiente = inicio; // Apunta a sí mismo
            ultimo = inicio;
        } else {
            nuevo->siguiente = inicio;
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
    }

    // Mostrar valores iniciales
    mostrarLista(inicio);

    char opcion;
    do {
        recorrerBarco(inicio);
        cout << "\n¿Desea repetir el recorrido? (s/n): ";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');

    cout << "\nPrograma finalizado.\n";
    return 0;
}
