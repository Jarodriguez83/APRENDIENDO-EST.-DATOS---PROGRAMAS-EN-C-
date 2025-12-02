#include <iostream>

using namespace std;

// --- 1. Definición del Nodo ---
struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;
};

/**
 * @brief Crea un nuevo nodo con el valor dado.
 */
Nodo* crearNuevoNodo(int valor) {
    Nodo* nuevoNodo = new Nodo(); 
    nuevoNodo->dato = valor;
    nuevoNodo->izquierda = nullptr;
    nuevoNodo->derecha = nullptr;
    return nuevoNodo;
}

// --- 2. Función de Inserción ---

/**
 * @brief Inserta un valor nuevo en el ABB de forma recursiva.
 * @param raiz Puntero a la raíz del sub-árbol actual.
 * @param valor El valor a insertar.
 * @return La raíz actualizada del sub-árbol.
 */
Nodo* insertar(Nodo* raiz, int valor) {
    // Caso 1: Si la raíz es nula, el valor se inserta aquí.
    if (raiz == nullptr) {
        return crearNuevoNodo(valor); 
    }

    // Caso 2: El valor va a la izquierda.
    if (valor < raiz->dato) {
        raiz->izquierda = insertar(raiz->izquierda, valor);
    } 
    // Caso 3: El valor va a la derecha.
    else if (valor > raiz->dato) {
        raiz->derecha = insertar(raiz->derecha, valor);
    } 
    // Nota: Si valor == raiz->dato, no se hace nada (no se permiten duplicados en este ABB).

    return raiz;
}

// --- 3. Función de Búsqueda ---

/**
 * @brief Busca un valor en el ABB de forma recursiva.
 * @param raiz Puntero a la raíz del sub-árbol actual.
 * @param valor El valor a buscar.
 * @return true si el valor es encontrado, false en caso contrario.
 */
bool buscar(Nodo* raiz, int valor) {
    // Caso 1: El árbol está vacío o llegamos al final de una rama.
    if (raiz == nullptr) {
        return false;
    }

    // Caso 2: Encontramos el valor.
    if (valor == raiz->dato) {
        return true;
    }

    // Caso 3: Buscar a la izquierda (valor menor).
    else if (valor < raiz->dato) {
        return buscar(raiz->izquierda, valor);
    }

    // Caso 4: Buscar a la derecha (valor mayor).
    else { // if (valor > raiz->dato)
        return buscar(raiz->derecha, valor);
    }
}

// --- 4. Recorrido Inorden (Para mostrar que está ordenado) ---

void recorridoInorden(Nodo* raiz) {
    if (raiz == nullptr) return;
    recorridoInorden(raiz->izquierda);
    cout << raiz->dato << " ";
    recorridoInorden(raiz->derecha);
}


// --- 5. Función Principal ---
int main() {
    Nodo* raiz = nullptr;

    // --- CONSTRUCCIÓN DEL ABB ---
    cout << "Construyendo el ABB con la secuencia: 50, 30, 70, 20, 40, 60, 80" << endl;
    raiz = insertar(raiz, 50); // La raíz
    insertar(raiz, 30);
    insertar(raiz, 70);
    insertar(raiz, 20);
    insertar(raiz, 40);
    insertar(raiz, 60);
    insertar(raiz, 80);

    cout << "\nVerificación del orden (Inorden): ";
    recorridoInorden(raiz);
    cout << "\n(Los datos se muestran ordenados: 20 30 40 50 60 70 80)" << endl;

    // --- DEMOSTRACIÓN DE BÚSQUEDA ---
    int valor1 = 40;
    int valor2 = 99;

    cout << "\n--- Pruebas de Búsqueda ---" << endl;

    // Prueba 1: Valor que SÍ existe (40)
    if (buscar(raiz, valor1)) {
        cout << "Buscando " << valor1 << ": ¡Encontrado!" << endl;
    } else {
        cout << "Buscando " << valor1 << ": No encontrado." << endl;
    }

    // Prueba 2: Valor que NO existe (99)
    if (buscar(raiz, valor2)) {
        cout << "Buscando " << valor2 << ": ¡Encontrado!" << endl;
    } else {
        cout << "Buscando " << valor2 << ": No encontrado." << endl;
    }
    
    // Nota: Es fundamental liberar la memoria con un recorrido Postorden y 'delete' en un código de producción.

    return 0;
}