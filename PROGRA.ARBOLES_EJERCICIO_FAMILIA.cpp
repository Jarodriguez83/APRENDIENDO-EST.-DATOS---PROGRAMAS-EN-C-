#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Para usar std::find

using namespace std;

// Definimos el tamaño máximo de la familia.
// Contando los nodos de la imagen: ros (1) + isis(3) + her(2) + der(2) + will(3) + santi(2) + jen(1) + car(1) + hec(1) + jhon(1) + osc(1) + mich(1) + davl(1) + luiz(1) + alfo(1) + mari(1) + nico(1) = 17 personas.
const int MAX_PERSONAS = 20; // Un poco más de 17 para futuras expansiones.

// Arreglos para almacenar los datos (índices y nombres)
string nombres[MAX_PERSONAS];
int hijo_mayor_idx[MAX_PERSONAS];    // Índice del hijo mayor (izquierdo)
int hijo_medio_idx[MAX_PERSONAS];   // Índice del hijo de la mitad
int hijo_menor_idx[MAX_PERSONAS];    // Índice del hijo menor (derecho)
int contador_personas = 0; // Lleva la cuenta de cuántas personas se han agregado

/**
 * @brief Inicializa los arreglos de índices con -1 para indicar que no hay hijos.
 */
void inicializar_indices() {
    for (int i = 0; i < MAX_PERSONAS; ++i) {
        hijo_mayor_idx[i] = -1;
        hijo_medio_idx[i] = -1;
        hijo_menor_idx[i] = -1;
    }
}

/**
 * @brief Busca el índice de una persona dado su nombre.
 * @param nombre_buscar El nombre de la persona.
 * @return El índice en los arreglos, o -1 si no se encuentra.
 */
int buscar_persona(const string& nombre_buscar) {
    for (int i = 0; i < contador_personas; ++i) {
        if (nombres[i] == nombre_buscar) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Ingresa una nueva persona a los arreglos.
 * @param nombre_persona El nombre de la nueva persona.
 * @return El índice donde se insertó la persona, o -1 si está lleno.
 */
int ingresar_persona(const string& nombre_persona) {
    if (contador_personas < MAX_PERSONAS) {
        nombres[contador_personas] = nombre_persona;
        // Inicializamos los índices de los hijos en -1, se asignarán después
        hijo_mayor_idx[contador_personas] = -1;
        hijo_medio_idx[contador_personas] = -1;
        hijo_menor_idx[contador_personas] = -1;
        return contador_personas++;
    } else {
        cout << "Error: La familia está llena (máximo " << MAX_PERSONAS << " personas)." << endl;
        return -1;
    }
}

/**
 * @brief Agrega los hijos a una persona.
 * @param padre_nombre El nombre del padre.
 * @param hijo1_nombre Nombre del hijo mayor.
 * @param hijo2_nombre Nombre del hijo de la mitad.
 * @param hijo3_nombre Nombre del hijo menor.
 */
void agregar_hijos(const string& padre_nombre, const string& hijo1_nombre = "", const string& hijo2_nombre = "", const string& hijo3_nombre = "") {
    int padre_idx = buscar_persona(padre_nombre);

    if (padre_idx != -1) {
        // Ingresar el hijo mayor (hijo1)
        if (!hijo1_nombre.empty()) {
            int hijo1_idx = buscar_persona(hijo1_nombre);
            if (hijo1_idx == -1) hijo1_idx = ingresar_persona(hijo1_nombre);
            hijo_mayor_idx[padre_idx] = hijo1_idx;
        }

        // Ingresar el hijo de la mitad (hijo2)
        if (!hijo2_nombre.empty()) {
            int hijo2_idx = buscar_persona(hijo2_nombre);
            if (hijo2_idx == -1) hijo2_idx = ingresar_persona(hijo2_nombre);
            hijo_medio_idx[padre_idx] = hijo2_idx;
        }

        // Ingresar el hijo menor (hijo3)
        if (!hijo3_nombre.empty()) {
            int hijo3_idx = buscar_persona(hijo3_nombre);
            if (hijo3_idx == -1) hijo3_idx = ingresar_persona(hijo3_nombre);
            hijo_menor_idx[padre_idx] = hijo3_idx;
        }
    } else {
        cout << "Error: Padre " << padre_nombre << " no encontrado." << endl;
    }
}

// --- Llenado de la Estructura (Basado en la Imagen) ---
void cargar_arbol_familiar() {
    // Ingresar todas las personas primero para asegurar los índices
    ingresar_persona("ros");
    ingresar_persona("isis");
    ingresar_persona("her");
    ingresar_persona("der");
    ingresar_persona("car");
    ingresar_persona("will");
    ingresar_persona("hec");
    ingresar_persona("jhon");
    ingresar_persona("santi");
    ingresar_persona("osc");
    ingresar_persona("jen");
    ingresar_persona("alfo");
    ingresar_persona("mari");
    ingresar_persona("lui");
    ingresar_persona("mich");
    ingresar_persona("davl");
    ingresar_persona("nico");

    // Asignar los hijos (siguiendo el orden de la imagen: izquierda a derecha)
    agregar_hijos("ros", "isis", "her", "der");
    agregar_hijos("isis", "car", "will", "hec");
    agregar_hijos("her", "jhon", "santi"); // her solo tiene 2 hijos
    agregar_hijos("der", "osc", "jen"); // der solo tiene 2 hijos
    agregar_hijos("will", "alfo", "mari", "lui");
    agregar_hijos("santi", "mich", "davl"); // santi solo tiene 2 hijos
    agregar_hijos("jen", "nico"); // jen solo tiene 1 hijo
    
    // Las personas 'car', 'hec', 'jhon', 'osc', 'alfo', 'mari', 'lui', 'mich', 'davl', 'nico' ya no tienen hijos en la imagen,
    // por defecto sus índices de hijos ya son -1 (inicializados en inicializar_indices).
}

// --- Consultas Requeridas ---

/**
 * @brief Muestra los nombres de los hijos de una persona.
 * @param nombre_padre El nombre de la persona (padre/madre).
 */
void consultar_hijos(const string& nombre_padre) {
    int padre_idx = buscar_persona(nombre_padre);

    if (padre_idx != -1) {
        cout << "Hijos de " << nombre_padre << ": ";
        bool tiene_hijos = false;

        // Comprobamos si tiene hijo mayor
        if (hijo_mayor_idx[padre_idx] != -1) {
            cout << nombres[hijo_mayor_idx[padre_idx]];
            tiene_hijos = true;
        }

        // Comprobamos si tiene hijo medio
        if (hijo_medio_idx[padre_idx] != -1) {
            if (tiene_hijos) cout << ", ";
            cout << nombres[hijo_medio_idx[padre_idx]];
            tiene_hijos = true;
        }

        // Comprobamos si tiene hijo menor
        if (hijo_menor_idx[padre_idx] != -1) {
            if (tiene_hijos) cout << ", ";
            cout << nombres[hijo_menor_idx[padre_idx]];
            tiene_hijos = true;
        }

        if (!tiene_hijos) {
            cout << "Ninguno";
        }
        cout << endl;
    } else {
        cout << "Persona " << nombre_padre << " no encontrada." << endl;
    }
}

/**
 * @brief Muestra los nombres de las personas que no tienen hijos (hojas del árbol).
 */
void consultar_sin_hijos() {
    cout << "Personas que no tienen hijos (hojas):" << endl;
    bool encontrado = false;
    for (int i = 0; i < contador_personas; ++i) {
        // Una persona no tiene hijos si todos sus índices de hijos son -1
        if (hijo_mayor_idx[i] == -1 && hijo_medio_idx[i] == -1 && hijo_menor_idx[i] == -1) {
            cout << "- " << nombres[i] << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "Todas las personas tienen al menos un hijo." << endl;
    }
}

/**
 * @brief Función recursiva para contar la cantidad de nietos (hijos de los hijos) de una persona.
 * Nota: Implementación básica y sencilla.
 * @param idx El índice de la persona a partir de la cual se cuentan los nietos.
 * @return La cantidad de nietos.
 */
int contar_nietos_recursivo(int idx) {
    if (idx == -1) {
        return 0; // Caso base: No hay persona en este índice.
    }

    int nietos = 0;
    
    // Obtener los índices de los hijos de la persona actual
    vector<int> hijos_idx;
    if (hijo_mayor_idx[idx] != -1) hijos_idx.push_back(hijo_mayor_idx[idx]);
    if (hijo_medio_idx[idx] != -1) hijos_idx.push_back(hijo_medio_idx[idx]);
    if (hijo_menor_idx[idx] != -1) hijos_idx.push_back(hijo_menor_idx[idx]);

    // Iterar sobre los hijos para contar sus hijos (que serían los nietos de la persona original)
    for (int hijo_idx : hijos_idx) {
        // Los hijos del hijo mayor (o medio, o menor) son los nietos
        if (hijo_mayor_idx[hijo_idx] != -1) nietos++;
        if (hijo_medio_idx[hijo_idx] != -1) nietos++;
        if (hijo_menor_idx[hijo_idx] != -1) nietos++;
        
        // Sumamos los nietos de los demás hijos del hijo. Esto es para contar los bisnietos, etc.,
        // si la pregunta fuese "descendientes". Para "nietos" puros, solo miramos los hijos
        // del hijo. Pero dado que la función está como recursiva, se mantiene el patrón de recorrido.
        // **Para cumplir con 'nietos' (hijos de los hijos) la recursión NO debe seguir.**
        // Si quisieras "descendientes" (nietos, bisnietos, tataranietos...), la línea de abajo sería:
        // nietos += contar_nietos_recursivo(hijo_idx);
    }
    
    // Si la función se llamara "contar_descendientes", la línea de abajo sería:
    // return nietos + (contar_nietos_recursivo(hijo_mayor_idx[idx]) + contar_nietos_recursivo(hijo_medio_idx[idx]) + contar_nietos_recursivo(hijo_menor_idx[idx]));
    // Pero como solo pide NIETOS (nivel 3), solo contamos los hijos de los hijos (nivel 2).
    return nietos;
}

/**
 * @brief Consulta la cantidad de nietos de una persona dado su nombre.
 * @param nombre_abuelo El nombre de la persona (abuelo/abuela).
 */
void consultar_cantidad_nietos(const string& nombre_abuelo) {
    int abuelo_idx = buscar_persona(nombre_abuelo);

    if (abuelo_idx != -1) {
        int cantidad_nietos = contar_nietos_recursivo(abuelo_idx);
        cout << nombre_abuelo << " tiene " << cantidad_nietos << " nietos." << endl;
    } else {
        cout << "Persona " << nombre_abuelo << " no encontrada." << endl;
    }
}

// --- Menú y Función Principal ---
int main() {
    inicializar_indices(); // Inicializa todos los índices de hijos a -1
    cargar_arbol_familiar(); // Carga la estructura de la imagen

    cout << "¡Estructura de árbol familiar cargada correctamente!" << endl;

    int opcion;
    string nombre_input;

    do {
        cout << "\n--- Menú de Consultas ---" << endl;
        cout << "1. Consultar hijos de una persona" << endl;
        cout << "2. Personas que no tienen hijos (hojas)" << endl;
        cout << "3. Cantidad de nietos de una persona" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Limpiar el buffer de entrada para evitar problemas con getline()
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre de la persona: ";
                getline(cin, nombre_input);
                consultar_hijos(nombre_input);
                break;
            case 2:
                consultar_sin_hijos();
                break;
            case 3:
                cout << "Ingrese el nombre del abuelo/abuela: ";
                getline(cin, nombre_input);
                consultar_cantidad_nietos(nombre_input);
                break;
            case 0:
                cout << "Saliendo del programa. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}