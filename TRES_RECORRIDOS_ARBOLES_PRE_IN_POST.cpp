#include <iostream>

using namespace std;

// --- 1. Definición de la Estructura del Nodo ---

/**
 * @brief Estructura simple de un Nodo para el árbol.
 */
struct Nodo {
    int dato;        // El valor del nodo
    Nodo* izquierda; // Puntero al sub-árbol izquierdo
    Nodo* derecha;   // Puntero al sub-árbol derecho
};

/**
 * @brief Función auxiliar para crear y reservar memoria para un nuevo nodo.
 */
Nodo* crearNuevoNodo(int valor) {
    Nodo* nuevoNodo = new Nodo(); 
    nuevoNodo->dato = valor;
    nuevoNodo->izquierda = nullptr;
    nuevoNodo->derecha = nullptr;
    return nuevoNodo;
}

/**
 * @brief Función para insertar nodos usando la lógica de Árbol Binario de Búsqueda (ABB).
 */
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == nullptr) {
        return crearNuevoNodo(valor); 
    }

    if (valor < raiz->dato) {
        raiz->izquierda = insertar(raiz->izquierda, valor);
    } else if (valor > raiz->dato) {
        raiz->derecha = insertar(raiz->derecha, valor);
    } 
    
    return raiz;
}

// --- 2. Implementación de los Recorridos ---

/**
 * @brief Recorrido en PRE-ORDEN.
 * * Lógica: Raíz -> Izquierda -> Derecha.
 * * Aplicación: Crear una copia del árbol o escribir expresiones.
 */
void recorridoPreorden(Nodo* raiz) {
    if (raiz == nullptr) {
        return;
    }

    // 1. Visitar la RAÍZ (Procesar/Imprimir)
    cout << raiz->dato << " ";

    // 2. Ir a la Izquierda
    recorridoPreorden(raiz->izquierda);

    // 3. Ir a la Derecha
    recorridoPreorden(raiz->derecha);
}

/**
 * @brief Recorrido en IN-ORDEN.
 * * Lógica: Izquierda -> Raíz -> Derecha.
 * * Aplicación: Obtener los elementos del ABB en orden ascendente (ordenados).
 */
void recorridoInorden(Nodo* raiz) {
    if (raiz == nullptr) {
        return;
    }

    // 1. Ir a la Izquierda
    recorridoInorden(raiz->izquierda);

    // 2. Visitar la RAÍZ (Procesar/Imprimir)
    cout << raiz->dato << " ";

    // 3. Ir a la Derecha
    recorridoInorden(raiz->derecha);
}

/**
 * @brief Recorrido en POST-ORDEN.
 * * Lógica: Izquierda -> Derecha -> Raíz.
 * * Aplicación: Liberar la memoria del árbol (eliminar primero los hijos, luego el padre).
 */
void recorridoPostorden(Nodo* raiz) {
    if (raiz == nullptr) {
        return;
    }

    // 1. Ir a la Izquierda
    recorridoPostorden(raiz->izquierda);

    // 2. Ir a la Derecha
    recorridoPostorden(raiz->derecha);

    // 3. Visitar la RAÍZ (Procesar/Imprimir)
    cout << raiz->dato << " ";
}

// --- 3. Función Principal ---
int main() {
    Nodo* raiz = nullptr;

    // Construimos el mismo árbol del ejemplo:
    // Estructura: Raíz 50. Izq 30 (hijos 20, 40). Der 70 (hijos 60, 80).
    cout << "Construyendo el árbol con: 50, 30, 70, 20, 40, 60, 80" << endl;
    raiz = insertar(raiz, 50); 
    insertar(raiz, 30);
    insertar(raiz, 70);
    insertar(raiz, 20);
    insertar(raiz, 40);
    insertar(raiz, 60);
    insertar(raiz, 80);

    // 1. Pre-orden
    cout << "\n--- Recorrido en PRE-ORDEN (Raíz, Izq, Der) ---" << endl;
    cout << "Resultado: ";
    recorridoPreorden(raiz); 
    cout << "\n(50 se imprime primero, luego va a 30, 20, 40...)" << endl;

    // 2. In-orden
    cout << "\n--- Recorrido en IN-ORDEN (Izq, Raíz, Der) ---" << endl;
    cout << "Resultado: ";
    recorridoInorden(raiz); 
    cout << "\n(El resultado es siempre ordenado: 20, 30, 40...)" << endl;

    // 3. Post-orden
    cout << "\n--- Recorrido en POST-ORDEN (Izq, Der, Raíz) ---" << endl;
    cout << "Resultado: ";
    recorridoPostorden(raiz); 
    cout << "\n(50 se imprime al final, después de todos sus hijos.)" << endl;

    return 0;
}