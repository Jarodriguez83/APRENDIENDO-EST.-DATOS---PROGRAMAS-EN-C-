#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <limits> // Para usar numeric_limits

using namespace std;

// Definimos un número muy grande para representar el costo infinito.
const int INFINITO = numeric_limits<int>::max();
// Número de vértices para el grafo de ejemplo
const int V = 6; 

// Tipo de dato para almacenar aristas: tupla<destino, peso>
// El grafo debe ser no dirigido para Prim.
using Arista = pair<int, int>; 
// Tipo de dato para la Cola de Prioridad: tupla<peso, nodo>
// Usamos 'greater' para que el peso más PEQUEÑO tenga la mayor prioridad.
// NOTA: La prioridad se basa en el PESO, no en la distancia acumulada.
using ParCosto = pair<int, int>; 

/**
 * @brief Implementación del algoritmo de Prim para encontrar el Árbol de Expansión Mínima (MST).
 * @param grafo La lista de adyacencia del grafo (nodo, peso).
 * @param inicio El nodo de partida (arbitrario).
 */
void primMST(const vector<list<Arista>>& grafo, int inicio) {
    cout << "\n--- Ejecución del Algoritmo de Prim (Inicio: " << inicio << ") ---" << endl;
    
    // 1. Inicialización de Claves y Estructuras
    
    // Almacena el costo mínimo para conectar el nodo 'i' al MST. (Inicialmente Infinito)
    vector<int> clave(V, INFINITO); 
    
    // Almacena el predecesor del nodo 'i' en el MST (para reconstruir el árbol).
    vector<int> predecesor(V, -1); 
    
    // Almacena los nodos que YA están incluidos en el MST.
    vector<bool> enMST(V, false); 
    
    // Cola de Prioridad: Almacena pares (costo_arista, nodo), priorizando el menor costo.
    priority_queue<ParCosto, vector<ParCosto>, greater<ParCosto>> cp; 

    // El nodo inicial tiene costo 0 para entrar al MST.
    clave[inicio] = 0;
    // Insertamos el nodo inicial: (costo, nodo)
    cp.push({0, inicio});

    // 2. Bucle Principal
    while (!cp.empty()) {
        // Extraer el nodo 'u' con el menor costo de conexión conocido.
        int costo_u = cp.top().first;
        int u = cp.top().second;
        cp.pop();

        // Si el nodo ya fue incluido en el MST o si el costo es obsoleto, ignorar.
        if (enMST[u]) {
            continue;
        }
        
        // El nodo 'u' entra al MST.
        enMST[u] = true;
        
        cout << "\n-> Nodo Añadido al MST: " << u << " (Costo de Conexión: " << clave[u] << ")" << endl;

        // 3. Relajación: Revisar todos los vecinos 'v' de 'u'
        for (const auto& arista : grafo[u]) {
            int v = arista.first;    // Vértice vecino
            int peso = arista.second; // Peso de la arista (u -> v)
            
            // Si el vecino 'v' NO está en el MST Y el peso de la arista es MENOR que su clave actual
            if (!enMST[v] && peso < clave[v]) {
                cout << "  -> Relajación de " << v << ": Costo " << clave[v] << " -> " << peso << endl;
                
                clave[v] = peso;
                predecesor[v] = u; // Guardamos que 'u' es el mejor camino para entrar a 'v'.
                // Insertar el nodo con el nuevo costo en la CP.
                cp.push({clave[v], v});
            } else {
                 // Esto es importante para entender la diferencia con Dijkstra: 
                 // Aquí solo nos importa si la arista individual es más barata, no el acumulado.
                 cout << "  -> Vecino " << v << ": No hay mejora (" << peso << " vs " << clave[v] << ")" << endl;
            }
        }
    }

    // 4. Mostrar Resultados (Reconstruir el MST)
    cout << "\n--- Aristas del Árbol de Expansión Mínima (MST) ---" << endl;
    long long costo_total = 0;
    
    // Iteramos desde el nodo 1, ya que el nodo de inicio (0) no tiene predecesor.
    for (int i = 0; i < V; ++i) {
        if (predecesor[i] != -1) {
            cout << "Arista: (" << predecesor[i] << " - " << i << ") Peso: " << clave[i] << endl;
            costo_total += clave[i];
        }
    }
    cout << "------------------------------------------------" << endl;
    cout << "Costo Total del MST: " << costo_total << endl;
}

/**
 * @brief Función principal para demostrar el algoritmo.
 */
int main() {
    // Grafo con 6 Vértices (0 a 5)
    vector<list<Arista>> grafo(V);

    // Aristas del Ejemplo (mismo del concepto):
    // A=0, B=1, C=2, D=3, E=4, F=5
    // El grafo es NO DIRIGIDO, por lo que las aristas se añaden en ambos sentidos.

    // (0, 1, 4), (0, 5, 2)
    grafo[0].push_back({1, 4}); grafo[1].push_back({0, 4});
    grafo[0].push_back({5, 2}); grafo[5].push_back({0, 2});

    // (1, 2, 6), (1, 5, 3)
    grafo[1].push_back({2, 6}); grafo[2].push_back({1, 6});
    grafo[1].push_back({5, 3}); grafo[5].push_back({1, 3});

    // (2, 3, 5), (2, 5, 1)
    grafo[2].push_back({3, 5}); grafo[3].push_back({2, 5});
    grafo[2].push_back({5, 1}); grafo[5].push_back({2, 1}); // Esta arista (2, 5) tiene peso 1

    // (3, 4, 8)
    grafo[3].push_back({4, 8}); grafo[4].push_back({3, 8});

    // (4, 5, 7)
    grafo[4].push_back({5, 7}); grafo[5].push_back({4, 7}); 

    // Ejecutar Prim comenzando desde el nodo 0 (A)
    primMST(grafo, 0); 

    // 

    return 0;
}