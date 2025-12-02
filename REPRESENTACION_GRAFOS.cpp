#include <iostream>
#include <vector>
#include <list>

using namespace std;

// El número total de vértices (nodos) en nuestro grafo de ejemplo
const int V = 5; // Vértices: 0, 1, 2, 3, 4

// --- 1. Implementación de la Matriz de Adyacencia ---

/**
 * @brief Inicializa y representa el grafo usando una Matriz de Adyacencia (Array 2D).
 * @param matriz La matriz V x V (un vector de vectores) que almacenará las conexiones.
 * * Lógica: matriz[i][j] = 1 si hay arista, 0 si no.
 */
void inicializarMatriz(vector<vector<int>>& matriz) {
    // Redimensionamos la matriz a V filas y V columnas, inicializadas a 0 (no hay arista).
    matriz.resize(V, vector<int>(V, 0));
}

/**
 * @brief Agrega una arista al grafo no dirigido en la Matriz de Adyacencia.
 * @param matriz La matriz de adyacencia.
 * @param u Vértice de origen.
 * @param v Vértice de destino.
 */
void agregarAristaMatriz(vector<vector<int>>& matriz, int u, int v) {
    if (u >= 0 && u < V && v >= 0 && v < V) {
        // Marcamos 1 para indicar la conexión.
        matriz[u][v] = 1;
        // Como es no dirigido, la conexión es bidireccional.
        matriz[v][u] = 1;
    }
}

/**
 * @brief Muestra la Matriz de Adyacencia.
 */
void mostrarMatriz(const vector<vector<int>>& matriz) {
    cout << "--- Matriz de Adyacencia (V^2) ---" << endl;
    cout << "  ";
    for (int i = 0; i < V; ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << " ";
        for (int j = 0; j < V; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

// --- 2. Implementación de la Lista de Adyacencia ---

/**
 * @brief Inicializa y representa el grafo usando una Lista de Adyacencia (Vector de Listas).
 * @param lista La lista V (un vector de listas) que almacenará las conexiones.
 * * Lógica: lista[i] contiene todos los vecinos del vértice i.
 */
void inicializarLista(vector<list<int>>& lista) {
    // Redimensionamos el vector para V listas vacías.
    lista.resize(V);
}

/**
 * @brief Agrega una arista al grafo no dirigido en la Lista de Adyacencia.
 * @param lista La lista de adyacencia.
 * @param u Vértice de origen.
 * @param v Vértice de destino.
 */
void agregarAristaLista(vector<list<int>>& lista, int u, int v) {
    if (u >= 0 && u < V && v >= 0 && v < V) {
        // Agregamos v a la lista de u.
        lista[u].push_back(v);
        // Como es no dirigido, agregamos u a la lista de v.
        lista[v].push_back(u);
    }
}

/**
 * @brief Muestra la Lista de Adyacencia.
 */
void mostrarLista(const vector<list<int>>& lista) {
    cout << "\n--- Lista de Adyacencia (V + E) ---" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Vértice " << i << ": ";
        // Iteramos sobre todos los vecinos de i.
        for (int vecino : lista[i]) {
            cout << " -> " << vecino;
        }
        cout << endl;
    }
}

// --- Función Principal ---
int main() {
    // Ejemplo de aristas (conexiones):
    // (0, 1), (0, 4), (1, 2), (1, 3), (1, 4), (2, 3), (3, 4)
    
    // ------------------------------------
    // A. Demostración de Matriz de Adyacencia
    // ------------------------------------
    vector<vector<int>> matriz;
    inicializarMatriz(matriz);
    
    agregarAristaMatriz(matriz, 0, 1);
    agregarAristaMatriz(matriz, 0, 4);
    agregarAristaMatriz(matriz, 1, 2);
    agregarAristaMatriz(matriz, 1, 3);
    agregarAristaMatriz(matriz, 1, 4);
    agregarAristaMatriz(matriz, 2, 3);
    agregarAristaMatriz(matriz, 3, 4);

    mostrarMatriz(matriz);
    // 

    // ------------------------------------
    // B. Demostración de Lista de Adyacencia
    // ------------------------------------
    vector<list<int>> lista;
    inicializarLista(lista);
    
    agregarAristaLista(lista, 0, 1);
    agregarAristaLista(lista, 0, 4);
    agregarAristaLista(lista, 1, 2);
    agregarAristaLista(lista, 1, 3);
    agregarAristaLista(lista, 1, 4);
    agregarAristaLista(lista, 2, 3);
    agregarAristaLista(lista, 3, 4);

    mostrarLista(lista);
    // 

    return 0;
}