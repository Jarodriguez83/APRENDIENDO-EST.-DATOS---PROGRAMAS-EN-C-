#include <iostream>

using namespace std;

// --- 1. Definición de la Estructura del Nodo ---

/**
 * @brief Estructura de un Nodo. Es auto-referenciada,
 * lo que significa que contiene punteros a sí misma.
 */
struct Nodo {
    int dato;        // El valor que almacena el nodo
    Nodo* izquierda; // Puntero al sub-árbol izquierdo
    Nodo* derecha;   // Puntero al sub-árbol derecho
};
// 

/**
 * @brief Función para crear un nuevo nodo.
 * @param valor El dato que se almacenará en el nuevo nodo.
 * @return Un puntero al nodo recién creado.
 */
Nodo* crearNuevoNodo(int valor) {
    // Usamos 'new' para reservar memoria dinámicamente para el nodo.
    Nodo* nuevoNodo = new Nodo(); 
    
    nuevoNodo->dato = valor;
    // Inicializamos los punteros a NULL (o nullptr en C++) para indicar que
    // el nodo recién creado aún no tiene hijos.
    nuevoNodo->izquierda = nullptr;
    nuevoNodo->derecha = nullptr;
    return nuevoNodo;
}

// --- 2. Inserción (Usando Lógica de Árbol de Búsqueda Binaria) ---

/**
 * @brief Inserta un nuevo nodo en el árbol de forma recursiva.
 * @param raiz Puntero a la raíz del sub-árbol actual.
 * @param valor El valor a insertar.
 * @return La raíz actualizada del sub-árbol.
 */
Nodo* insertar(Nodo* raiz, int valor) {
    // Caso base: Si la raíz es nula, encontramos el lugar.
    if (raiz == nullptr) {
        // Creamos y retornamos el nuevo nodo, que se convierte en el hijo del nodo anterior.
        return crearNuevoNodo(valor); 
    }

    // Regla del Árbol de Búsqueda Binaria (ABB):
    if (valor < raiz->dato) {
        // Si el valor es menor, vamos a la izquierda.
        // La recursión actualiza el puntero izquierda de la raíz actual.
        raiz->izquierda = insertar(raiz->izquierda, valor);
    } else if (valor > raiz->dato) {
        // Si el valor es mayor, vamos a la derecha.
        raiz->derecha = insertar(raiz->derecha, valor);
    } 
    // Si el valor es igual, no hacemos nada (ABB no permite duplicados).

    // Retornamos el puntero a la raíz actual (sin cambios si no se insertó nada).
    return raiz;
}

// --- 3. Recorrido (Inorden Recursivo) ---

/**
 * @brief Recorre el árbol en orden Inorden (Izquierda -> Raíz -> Derecha).
 * @param raiz Puntero a la raíz del sub-árbol actual.
 * * Este recorrido imprime los valores del ABB en orden ascendente.
 */
void recorridoInorden(Nodo* raiz) {
    // Caso base: Si el nodo es nulo, terminamos la rama.
    if (raiz == nullptr) {
        return;
    }

    // 1. Recorrer Sub-árbol Izquierdo (Recursión)
    recorridoInorden(raiz->izquierda);

    // 2. Visitar el nodo actual (Imprimir el dato)
    cout << raiz->dato << " ";

    // 3. Recorrer Sub-árbol Derecho (Recursión)
    recorridoInorden(raiz->derecha);
}

// --- Función Principal ---
int main() {
    // La raíz del árbol inicialmente es nula (vacía).
    Nodo* raiz = nullptr;

    // Insertamos los nodos. La función 'insertar' retorna la nueva raíz
    // o la raíz sin cambios.
    cout << "Insertando elementos: 50, 30, 70, 20, 40, 60, 80" << endl;
    raiz = insertar(raiz, 50); // 50 es la raíz
    insertar(raiz, 30);
    insertar(raiz, 70);
    insertar(raiz, 20);
    insertar(raiz, 40);
    insertar(raiz, 60);
    insertar(raiz, 80);

    cout << "\n--- Recorrido Inorden (Muestra los datos ordenados) ---" << endl;
    cout << "Orden: ";
    recorridoInorden(raiz); // Imprimirá: 20 30 40 50 60 70 80
    cout << endl;

    // Nota: En un código real, se necesitaría una función adicional
    // para liberar la memoria dinámica (usando 'delete') después de usar el árbol.

    return 0;
}