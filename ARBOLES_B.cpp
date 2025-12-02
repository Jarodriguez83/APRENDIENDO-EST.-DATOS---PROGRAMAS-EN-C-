#include <iostream>
#include <vector>
#include <algorithm> // Para usar sort y encontrar el medio

using namespace std;

// El Orden del Árbol B (m=3)
const int ORDEN = 3; 
// Número máximo de claves que un nodo puede contener (m-1)
const int MAX_CLAVES = ORDEN - 1; // MAX_CLAVES = 2

// --- 1. Definición de la Estructura del Nodo B ---

/**
 * @brief Estructura de un Nodo de Árbol B.
 * * Debe almacenar múltiples claves (datos) y múltiples punteros (hijos).
 */
struct NodoB {
    vector<int> claves;  // Lista de claves (máximo 2 en este caso)
    vector<NodoB*> hijos; // Lista de punteros a nodos hijos (máximo 3)
    bool esHoja;         // True si es un nodo hoja (no tiene hijos)

    // Constructor simple
    NodoB(bool hoja) : esHoja(hoja) {}
};
// 


// --- 2. Clase Principal del Árbol B ---

class ArbolB {
private:
    NodoB* raiz;

    // --- Funciones Lógicas de División y Navegación ---

    /**
     * @brief Función de utilidad para encontrar dónde se debe insertar una clave
     * en el vector ordenado de claves de un nodo.
     */
    int encontrarIndice(NodoB* nodo, int k) {
        int idx = 0;
        // Encuentra el índice 'idx' tal que nodo->claves[idx] >= k
        while (idx < nodo->claves.size() && nodo->claves[idx] < k) {
            idx++;
        }
        return idx;
    }

    /**
     * @brief Realiza la división (Split) del nodo 'y' que está lleno.
     * * Esta función es llamada por la inserción cuando el nodo hijo está lleno.
     * @param nodoPadre El nodo padre donde se subirá la clave media.
     * @param i El índice donde el nodoPadre tiene el puntero a 'y'.
     * @param y El nodo hijo que está lleno (y tiene MAX_CLAVES + 1 elementos temporalmente).
     */
    void dividirHijo(NodoB* nodoPadre, int i, NodoB* y) {
        // Creamos el nuevo nodo que contendrá la mitad derecha de las claves de 'y'
        NodoB* z = new NodoB(y->esHoja); 

        // 1. Promover la clave media:
        // En nuestro caso (3 claves temporales), la clave media es la del índice 1.
        int claveMedia = y->claves[MAX_CLAVES / 2]; // Índice 1 (la segunda clave)

        // 2. Mover las claves de la mitad derecha a 'z':
        for (int j = 0; j < MAX_CLAVES / 2; j++) {
            z->claves.push_back(y->claves[j + (MAX_CLAVES / 2) + 1]); // Clave en índice 2 (la tercera clave)
        }
        
        // 3. Mover los punteros de la mitad derecha a 'z' (solo si no es hoja):
        if (!y->esHoja) {
            for (int j = 0; j <= MAX_CLAVES / 2; j++) {
                z->hijos.push_back(y->hijos[j + (MAX_CLAVES / 2) + 1]);
            }
        }

        // 4. Reducir el tamaño de 'y' (solo deja la mitad izquierda):
        // Eliminamos la clave media y las claves que se movieron a 'z'.
        y->claves.resize(MAX_CLAVES / 2); // Ahora 'y' solo tiene la clave en índice 0

        // 5. Insertar la clave media en el nodoPadre:
        // Movemos el puntero del hijo para hacer espacio para la clave media.
        nodoPadre->hijos.insert(nodoPadre->hijos.begin() + i + 1, z);
        // Insertamos la clave media en el nodoPadre.
        nodoPadre->claves.insert(nodoPadre->claves.begin() + i, claveMedia);

        cout << " -> División: Clave " << claveMedia << " promovida al padre. " << endl;
    }


    /**
     * @brief La función principal que inserta una clave 'k' en un nodo no lleno 'x'.
     * * Maneja el caso de que un hijo necesite ser dividido.
     */
    void insertarNoLleno(NodoB* x, int k) {
        int i = encontrarIndice(x, k); // Encuentra la posición para k

        // Caso 1: Si es un nodo hoja (la inserción finaliza aquí)
        if (x->esHoja) {
            // Insertamos la clave en la posición correcta (mantiene el orden)
            x->claves.insert(x->claves.begin() + i, k);
        } 
        // Caso 2: Si no es hoja, bajamos recursivamente
        else {
            // Vamos al hijo en la posición i
            NodoB* hijo = x->hijos[i];

            // Si el hijo está lleno (tiene MAX_CLAVES, que es 2)
            if (hijo->claves.size() == MAX_CLAVES) {
                // Temporalmente lo llenaremos a 3, antes de dividir
                hijo->claves.push_back(k); 
                sort(hijo->claves.begin(), hijo->claves.end()); // Ordenamos para encontrar la media
                
                // Realizar la división del hijo
                dividirHijo(x, i, hijo);

                // Después de la división, la clave subió al padre 'x'.
                // Decidimos a cuál de los dos nuevos hijos (el viejo 'y' o el nuevo 'z') 
                // debemos bajar ahora para insertar la clave 'k'.
                if (k > x->claves[i]) {
                    i++; // Bajamos al nuevo hijo de la derecha
                }
            }
            // Ahora bajamos recursivamente al hijo que no estaba lleno o fue dividido
            insertarNoLleno(x->hijos[i], k);
        }
    }
    
public:
    // Constructor
    ArbolB() : raiz(nullptr) {}

    // --- 3. Función de Inserción Pública ---
    void insertar(int k) {
        cout << "Insertando " << k;

        // Caso 1: El árbol está vacío
        if (raiz == nullptr) {
            raiz = new NodoB(true);
            raiz->claves.push_back(k);
            cout << endl;
            return;
        }

        // Caso 2: El árbol no está vacío y la raíz está llena (requiere división de la raíz)
        if (raiz->claves.size() == MAX_CLAVES) { // Si la raíz tiene 2 claves
            NodoB* s = new NodoB(false); // Creamos un nuevo nodo raíz (temporal)
            s->hijos.push_back(raiz); // El viejo 'raiz' se convierte en el hijo de 's'
            raiz = s; // 's' se convierte en la nueva raíz

            // Dividimos el antiguo nodo raíz (que ahora es el hijo de 's')
            dividirHijo(s, 0, s->hijos[0]);

            // Ahora insertamos 'k' en la nueva raíz (s) que ya no está llena
            insertarNoLleno(s, k);
        } 
        // Caso 3: La raíz no está llena
        else {
            insertarNoLleno(raiz, k);
        }
        cout << endl;
    }

    // --- Función de Utilidad para Imprimir el Árbol (Simple) ---
    void imprimir(NodoB* n, int nivel) {
        if (n == nullptr) return;
        
        cout << "\nNivel " << nivel << ": [";
        for (int i = 0; i < n->claves.size(); i++) {
            cout << n->claves[i] << (i == n->claves.size() - 1 ? "" : ", ");
        }
        cout << "]";

        if (!n->esHoja) {
            for (int i = 0; i < n->hijos.size(); i++) {
                imprimir(n->hijos[i], nivel + 1);
            }
        }
    }

    void imprimirArbol() {
        if (raiz != nullptr) {
            cout << "\n--- Estado Final del Árbol B (Preorden Simple) ---" << endl;
            imprimir(raiz, 0);
            cout << endl;
        }
    }
};

// --- Función Principal ---
int main() {
    ArbolB arbol;

    cout << "Orden Básico: El nodo soporta un máximo de 2 claves (Orden 3)." << endl;

    // Insertaremos la secuencia que fuerza la división (split): 10, 20, 30, 40
    arbol.insertar(10); // Raíz: [10]
    arbol.insertar(20); // Raíz: [10, 20] -> Llena
    
    // Al insertar 30, se fuerza la división de la raíz [10, 20]
    // Clave 20 sube. Nueva Raíz: [20]. Hijos: [10] y [30].
    arbol.insertar(30); 
    
    // Al insertar 40, se inserta en [30] -> [30, 40]
    arbol.insertar(40);
    
    // Imprimir el árbol final
    arbol.imprimirArbol();
    /* Salida Esperada:
    Nivel 0: [20] (Raíz)
    Nivel 1: [10] (Hijo Izquierdo)
    Nivel 1: [30, 40] (Hijo Derecho)
    */

    return 0;
}