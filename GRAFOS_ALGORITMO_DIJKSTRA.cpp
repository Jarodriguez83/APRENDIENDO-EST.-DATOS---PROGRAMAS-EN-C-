#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <tuple>
#include <limits> // Para usar numeric_limits

using namespace std;

// Definimos un número muy grande para representar la distancia infinita.
const int INFINITO = numeric_limits<int>::max();
// Número de vértices para el grafo de ejemplo
const int V = 5; 

// Tipo de dato para almacenar aristas: tupla<destino, peso>
using Arista = pair<int, int>; 
// Tipo de dato para la Cola de Prioridad: tupla<distancia, nodo>
// Usamos 'greater' para que la distancia más PEQUEÑA tenga la mayor prioridad.
using ParDistancia = pair<int, int>; 

/**
 * @brief Implementación del algoritmo de Dijkstra para encontrar la ruta más corta.
 * @param grafo La lista de adyacencia del grafo (nodo, peso).
 * @param inicio El nodo de partida (fuente).
 */
void dijkstra(const vector<list<Arista>>& grafo, int inicio) {
    cout << "\n--- Ejecución del Algoritmo de Dijkstra (Nodo Inicial: " << inicio << ") ---" << endl;
    
    // 1. Inicialización de Distancias
    // Vector para almacenar la distancia mínima conocida desde 'inicio' a cada nodo.
    vector<int> distancia(V, INFINITO); 
    
    // Cola de Prioridad: Almacena los nodos a visitar, priorizando la menor distancia.
    priority_queue<ParDistancia, vector<ParDistancia>, greater<ParDistancia>> cp; 

    // La distancia del nodo inicial a sí mismo es 0.
    distancia[inicio] = 0;
    // Insertamos el nodo inicial en la CP: (distancia, nodo)
    cp.push({0, inicio});

    // 2. Bucle Principal
    while (!cp.empty()) {
        // Extraer el nodo 'u' con la menor distancia registrada (la clave de Dijkstra)
        int dist_u = cp.top().first;
        int u = cp.top().second;
        cp.pop();

        // Control de distancias obsoletas (si ya encontramos una ruta más corta)
        if (dist_u > distancia[u]) {
            continue;
        }
        
        cout << "\nProcesando nodo " << u << " (Distancia: " << dist_u << ")" << endl;

        // 3. Relajación: Revisar todos los vecinos 'v' de 'u'
        for (const auto& arista : grafo[u]) {
            int v = arista.first;    // Vértice vecino
            int peso = arista.second; // Peso de la arista (u -> v)
            
            // Calcular la nueva distancia total si pasamos por 'u'
            int nueva_distancia = dist_u + peso; 

            // 4. Actualizar (Relajar): Si la nueva distancia es menor que la registrada
            if (nueva_distancia < distancia[v]) {
                cout << "  -> Relajación de " << v << ": " << distancia[v] << " -> " << nueva_distancia << endl;
                
                distancia[v] = nueva_distancia;
                // Insertar el nodo con la nueva distancia en la CP
                cp.push({nueva_distancia, v});
            } else {
                cout << "  -> Vecino " << v << ": No hay mejora (" << nueva_distancia << " vs " << distancia[v] << ")" << endl;
            }
        }
    }

    // 5. Mostrar Resultados
    cout << "\n--- Resultados Finales ---" << endl;
    for (int i = 0; i < V; ++i) {
        if (distancia[i] == INFINITO) {
            cout << "Ruta más corta a " << i << ": Inalcanzable" << endl;
        } else {
            cout << "Ruta más corta a " << i << ": " << distancia[i] << endl;
        }
    }
}

/**
 * @brief Función principal para demostrar el algoritmo.
 */
int main() {
    // Grafo con 5 Vértices (0 a 4)
    vector<list<Arista>> grafo(V);

    // Aristas del Ejemplo (mismo del concepto):
    // A=0, B=1, C=2, D=3, E=4
    // 0 -> 1 (6), 0 -> 2 (1)
    // 2 -> 1 (2), 2 -> 3 (4)
    // 1 -> 4 (2)
    // 3 -> 4 (5)

    // Grafo[origen].push_back({destino, peso});
    grafo[0].push_back({1, 6}); // 0 -> 1, peso 6
    grafo[0].push_back({2, 1}); // 0 -> 2, peso 1

    grafo[2].push_back({1, 2}); // 2 -> 1, peso 2
    grafo[2].push_back({3, 4}); // 2 -> 3, peso 4

    grafo[1].push_back({4, 2}); // 1 -> 4, peso 2

    grafo[3].push_back({4, 5}); // 3 -> 4, peso 5

    // Ejecutar Dijkstra comenzando desde el nodo 0 (A)
    dijkstra(grafo, 0); 
    // 

    return 0;
}