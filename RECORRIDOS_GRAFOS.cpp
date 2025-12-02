#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

// Número de vértices para el grafo de ejemplo
const int V = 6; 

/**
 * @brief Inicializa el grafo usando una Lista de Adyacencia.
 * @param lista El vector de listas que representa el grafo.
 */
void inicializarGrafo(vector<list<int>>& lista) {
    lista.resize(V);
}

/**
 * @brief Agrega una arista a un grafo.
 * @param lista La lista de adyacencia.
 * @param u Vértice de origen.
 * @param v Vértice de destino.
 * @param dirigido Indica si la arista es solo u->v (true) o u<->v (false).
 */
void agregarArista(vector<list<int>>& lista, int u, int v, bool dirigido) {
    lista[u].push_back(v);
    if (!dirigido) {
        lista[v].push_back(u);
    }
}

// ------------------------------------------------------------------
// 1. BÚSQUEDA EN AMPLITUD (BFS)
// ------------------------------------------------------------------

/**
 * @brief Realiza el recorrido BFS.
 * * Lógica: Explora nivel por nivel (usa una Cola).
 * @param lista La lista de adyacencia del grafo.
 * @param inicio El vértice desde donde empezar el recorrido.
 */
void BFS(const vector<list<int>>& lista, int inicio) {
    cout << "\n--- Recorrido BFS (Amplitud) ---" << endl;
    vector<bool> visitado(V, false); // Arreglo para marcar nodos visitados
    queue<int> cola;                // La estructura clave del BFS

    // Paso 1: Inicializar la cola con el nodo de inicio
    visitado[inicio] = true;
    cola.push(inicio);

    while (!cola.empty()) {
        // Paso 2: Desencolar el nodo actual 'u'
        int u = cola.front();
        cola.pop();
        cout << u << " ";

        // Paso 3: Explorar vecinos no visitados y encolarlos
        for (int v : lista[u]) {
            if (!visitado[v]) {
                visitado[v] = true;
                cola.push(v);
            }
        }
    }
    cout << endl;
}

// ------------------------------------------------------------------
// 2. BÚSQUEDA EN PROFUNDIDAD (DFS)
// ------------------------------------------------------------------

/**
 * @brief Función recursiva auxiliar para el recorrido DFS.
 * * Lógica: Explora lo más profundo posible (usa Recursión/Pila).
 * @param lista La lista de adyacencia.
 * @param u El nodo actual.
 * @param visitado El arreglo de marcas.
 */
void DFS_Util(const vector<list<int>>& lista, int u, vector<bool>& visitado) {
    // 1. Marcar y procesar el nodo actual
    visitado[u] = true;
    cout << u << " ";

    // 2. Recorrer recursivamente los vecinos no visitados
    for (int v : lista[u]) {
        if (!visitado[v]) {
            DFS_Util(lista, v, visitado);
        }
    }
}

void DFS(const vector<list<int>>& lista, int inicio) {
    cout << "\n--- Recorrido DFS (Profundidad) ---" << endl;
    vector<bool> visitado(V, false);
    DFS_Util(lista, inicio, visitado);
    cout << endl;
}

// ------------------------------------------------------------------
// 3. ORDENAMIENTO TOPOLÓGICO
// ------------------------------------------------------------------

/**
 * @brief Función recursiva auxiliar para el Ordenamiento Topológico.
 * * Lógica: Recorre DFS y agrega el nodo a la pila SOLO al salir de la recursión.
 * @param lista La lista de adyacencia (debe ser un DAG).
 * @param u El nodo actual.
 * @param visitado El arreglo de marcas.
 * @param pila La estructura para almacenar el orden.
 */
void topologico_Util(const vector<list<int>>& lista, int u, vector<bool>& visitado, stack<int>& pila) {
    visitado[u] = true;

    // 1. Recorrer recursivamente a todos los vecinos (dependencias)
    for (int v : lista[u]) {
        if (!visitado[v]) {
            topologico_Util(lista, v, visitado, pila);
        }
    }

    // 2. Apilar el nodo SOLO después de que todos sus vecinos dependientes hayan terminado.
    pila.push(u);
}

void ordenamientoTopologico(const vector<list<int>>& lista) {
    cout << "\n--- Ordenamiento Topológico ---" << endl;
    vector<bool> visitado(V, false);
    stack<int> pila; // La estructura para guardar el orden

    // Llamar a la función auxiliar para cada nodo no visitado
    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            topologico_Util(lista, i, visitado, pila);
        }
    }

    // El orden topológico es la pila de arriba a abajo
    cout << "Orden Válido: ";
    while (!pila.empty()) {
        cout << pila.top() << " ";
        pila.pop();
    }
    cout << endl;
}

// --- Función Principal (Ejecución) ---
int main() {
    // V = 6 (Nodos 0 a 5)
    
    // --- GRAFO PARA BFS/DFS (No Dirigido) ---
    vector<list<int>> grafoNoDirigido;
    inicializarGrafo(grafoNoDirigido);

    agregarArista(grafoNoDirigido, 0, 1, false);
    agregarArista(grafoNoDirigido, 0, 2, false);
    agregarArista(grafoNoDirigido, 1, 3, false);
    agregarArista(grafoNoDirigido, 2, 4, false);
    agregarArista(grafoNoDirigido, 3, 5, false);
    agregarArista(grafoNoDirigido, 4, 5, false);
    
    // Ejecutar BFS (Empieza en 0)
    BFS(grafoNoDirigido, 0); // Esperado: 0 1 2 3 4 5

    // Ejecutar DFS (Empieza en 0)
    DFS(grafoNoDirigido, 0); // Esperado: 0 1 3 5 4 2 (o similar, depende del orden de la lista)

    // --- GRAFO PARA ORDENAMIENTO TOPOLÓGICO (Dirigido y Acíclico - DAG) ---
    vector<list<int>> grafoDirigido;
    inicializarGrafo(grafoDirigido);
    
    // Ejemplo: Tareas con prerrequisitos
    // Tarea 5 -> Tarea 2, Tarea 5 -> Tarea 0
    // Tarea 4 -> Tarea 0, Tarea 4 -> Tarea 1
    // Tarea 2 -> Tarea 3
    // Tarea 3 -> Tarea 1

    agregarArista(grafoDirigido, 5, 2, true);
    agregarArista(grafoDirigido, 5, 0, true);
    agregarArista(grafoDirigido, 4, 0, true);
    agregarArista(grafoDirigido, 4, 1, true);
    agregarArista(grafoDirigido, 2, 3, true);
    agregarArista(grafoDirigido, 3, 1, true);

    // Ejecutar Ordenamiento Topológico
    ordenamientoTopologico(grafoDirigido); // Esperado: 4 5 2 3 1 0 (o cualquier otro orden válido)

    return 0;
}