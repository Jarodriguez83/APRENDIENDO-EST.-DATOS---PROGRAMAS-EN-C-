#include <iostream>
#include <algorithm> // Para usar std::max y std::max

using namespace std;

// --- 1. Definición del Nodo AVL ---

/**
 * @brief Estructura de un Nodo AVL. Agrega el campo 'altura'
 * para poder calcular el Factor de Equilibrio.
 */
struct NodoAVL {
    int dato;
    NodoAVL* izquierda;
    NodoAVL* derecha;
    int altura; // Clave para el AVL: Mantiene la altura del sub-árbol
};

/**
 * @brief Crea un nuevo nodo.
 */
NodoAVL* crearNuevoNodo(int valor) {
    NodoAVL* nuevoNodo = new NodoAVL(); 
    nuevoNodo->dato = valor;
    nuevoNodo->izquierda = nullptr;
    nuevoNodo->derecha = nullptr;
    nuevoNodo->altura = 1; // Un nodo nuevo siempre tiene altura 1
    return nuevoNodo;
}

// --- 2. Funciones Auxiliares para Altura y Equilibrio ---

/**
 * @brief Obtiene la altura de un nodo. Si el nodo es nulo, retorna 0.
 */
int getAltura(NodoAVL* N) {
    if (N == nullptr) {
        return 0;
    }
    return N->altura;
}

/**
 * @brief Función para actualizar la altura de un nodo padre
 * después de una inserción o rotación.
 */
void actualizarAltura(NodoAVL* N) {
    // La altura es 1 (el nodo actual) más la altura máxima de sus hijos.
    N->altura = 1 + max(getAltura(N->izquierda), getAltura(N->derecha));
}

/**
 * @brief Calcula el Factor de Equilibrio (FB) del nodo.
 * FB = Altura_Izquierda - Altura_Derecha
 */
int getFactorEquilibrio(NodoAVL* N) {
    if (N == nullptr) {
        return 0;
    }
    return getAltura(N->izquierda) - getAltura(N->derecha);
}

// --- 3. Implementación de Rotaciones (El Corazón del AVL) ---

/**
 * @brief Realiza la Rotación Simple a la Derecha (Caso LL: Izquierda-Izquierda).
 * @param y Nodo desequilibrado (Padre).
 * @return El nuevo nodo raíz del sub-árbol (x).
 */
NodoAVL* rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierda;
    NodoAVL* T2 = x->derecha;

    // 1. Realizar la rotación
    x->derecha = y; // El nodo 'y' se convierte en el hijo derecho de 'x'
    y->izquierda = T2; // El sub-árbol T2 se convierte en el hijo izquierdo de 'y'

    // 2. Actualizar alturas (IMPORTANTE: Primero el que está más abajo)
    actualizarAltura(y);
    actualizarAltura(x);

    // Retorna la nueva raíz
    return x;
}
// 



/**
 * @brief Realiza la Rotación Simple a la Izquierda (Caso RR: Derecha-Derecha).
 * @param x Nodo desequilibrado (Padre).
 * @return El nuevo nodo raíz del sub-árbol (y).
 */
NodoAVL* rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecha;
    NodoAVL* T2 = y->izquierda;

    // 1. Realizar la rotación
    y->izquierda = x; // El nodo 'x' se convierte en el hijo izquierdo de 'y'
    x->derecha = T2; // El sub-árbol T2 se convierte en el hijo derecho de 'x'

    // 2. Actualizar alturas
    actualizarAltura(x);
    actualizarAltura(y);

    // Retorna la nueva raíz
    return y;
}
// 

// --- 4. Inserción y Reequilibrio ---

/**
 * @brief Inserta un nuevo nodo y realiza el reequilibrio si es necesario.
 * @param nodo Raíz del sub-árbol actual.
 * @param valor El valor a insertar.
 * @return La raíz reequilibrada del sub-árbol.
 */
NodoAVL* insertar(NodoAVL* nodo, int valor) {
    // 1. Inserción normal de ABB
    if (nodo == nullptr) {
        return crearNuevoNodo(valor);
    }
    if (valor < nodo->dato) {
        nodo->izquierda = insertar(nodo->izquierda, valor);
    } else if (valor > nodo->dato) {
        nodo->derecha = insertar(nodo->derecha, valor);
    } else {
        return nodo; // No permite duplicados
    }

    // 2. Actualizar Altura del nodo actual
    actualizarAltura(nodo);

    // 3. Obtener el Factor de Equilibrio (FB)
    int fb = getFactorEquilibrio(nodo);

    // 4. Verificar Desequilibrio y Aplicar Rotaciones:

    // Caso LL (Izquierda-Izquierda): FB > 1 y el valor fue insertado a la izquierda del hijo izquierdo
    if (fb > 1 && valor < nodo->izquierda->dato) {
        cout << " -> Aplicando Rotación Simple Derecha (LL) en " << nodo->dato << endl;
        return rotacionDerecha(nodo);
    }

    // Caso RR (Derecha-Derecha): FB < -1 y el valor fue insertado a la derecha del hijo derecho
    if (fb < -1 && valor > nodo->derecha->dato) {
        cout << " -> Aplicando Rotación Simple Izquierda (RR) en " << nodo->dato << endl;
        return rotacionIzquierda(nodo);
    }

    // Caso LR (Izquierda-Derecha): FB > 1 (Requiere Rotación Doble)
    if (fb > 1 && valor > nodo->izquierda->dato) {
        cout << " -> Aplicando Rotación Doble (LR) en " << nodo->dato << endl;
        nodo->izquierda = rotacionIzquierda(nodo->izquierda); // 1. Izquierda
        return rotacionDerecha(nodo); // 2. Derecha
    }

    // Caso RL (Derecha-Izquierda): FB < -1 (Requiere Rotación Doble)
    if (fb < -1 && valor < nodo->derecha->dato) {
        cout << " -> Aplicando Rotación Doble (RL) en " << nodo->dato << endl;
        nodo->derecha = rotacionDerecha(nodo->derecha); // 1. Derecha
        return rotacionIzquierda(nodo); // 2. Izquierda
    }

    // Si está equilibrado
    return nodo;
}

// --- 5. Recorrido Inorden (Para verificación) ---

void inorden(NodoAVL* raiz) {
    if (raiz == nullptr) return;
    inorden(raiz->izquierda);
    cout << raiz->dato << " (H: " << raiz->altura << ") ";
    inorden(raiz->derecha);
}

// --- 6. Función Principal ---
int main() {
    NodoAVL* raiz = nullptr;

    cout << "--- Construcción y Reequilibrio AVL (Caso RR) ---" << endl;
    
    // Secuencia que fuerza el Caso RR (Derecha-Derecha), discutido previamente: 10, 20, 30
    raiz = insertar(raiz, 10);
    raiz = insertar(raiz, 20);
    raiz = insertar(raiz, 30); // Desequilibrio en 10, se resuelve con Rotación Simple Izquierda

    cout << "\nÁrbol después de RR (10, 20, 30): ";
    inorden(raiz); // Debe salir: 10 20 30, con 20 como raíz.

    cout << "\n\n--- Construcción y Reequilibrio AVL (Caso LR) ---" << endl;

    // Secuencia que fuerza el Caso LR (Izquierda-Derecha), discutido previamente: 50, 20, 40
    NodoAVL* raiz2 = nullptr;
    raiz2 = insertar(raiz2, 50);
    raiz2 = insertar(raiz2, 20);
    raiz2 = insertar(raiz2, 40); // Desequilibrio en 50, se resuelve con Rotación Doble (LR)

    cout << "\nÁrbol después de LR (50, 20, 40): ";
    inorden(raiz2); // Debe salir: 20 40 50, con 40 como raíz.
    cout << endl;

    return 0;
}