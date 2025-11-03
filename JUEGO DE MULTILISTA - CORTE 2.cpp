#include <iostream>
using namespace std;  

struct Articulo {
    string nom;  
    int potenciadano; 
    Articulo* sig; 
}; 

struct Categoria {
    string nom; 
    Categoria* sig; 
    Articulo* sub; 
};

Categoria* crearcategoria(string nom) {
    Categoria* nuevo = new Categoria{nom, NULL, NULL};
    return nuevo; 
}

void insertarcategoria(Categoria*& cab, Categoria* nuevo) {
    nuevo->sig = cab; 
    cab = nuevo; 
}

Articulo* creararticulo(string nom, int potenciadano) {
    Articulo* nuevo = new Articulo{nom, potenciadano, NULL};
    return nuevo;  
}

void insertararticulo(Articulo*& cab, Articulo* nuevo) {
    nuevo->sig = cab; 
    cab = nuevo; 
}

void imprimirtodo(Categoria* cab) {
    Categoria* actualcategoria = cab; 
    Articulo* actualarticulo;  
    while (actualcategoria != NULL) {
        cout << "\nCATEGORIA: " << actualcategoria->nom << endl;  
        actualarticulo = actualcategoria->sub; 
        while (actualarticulo != NULL) {
            cout << "   - NOMBRE ART: " << actualarticulo->nom << endl; 
            cout << "   - POTENCIA DEL " << actualarticulo->nom << ": " << actualarticulo->potenciadano << endl; 
            actualarticulo = actualarticulo->sig; 
        }
        actualcategoria = actualcategoria->sig;  
    }
}

// 🔥 Nueva función: buscar, mostrar y eliminar un artículo
void usarYEliminarArticulo(Categoria*& cab, string usarArt) {
    Categoria* actualCategoria = cab;
    bool encontrado = false;

    while (actualCategoria != NULL) {
        Articulo* actualArticulo = actualCategoria->sub;
        Articulo* anterior = NULL;

        while (actualArticulo != NULL) {
            if (actualArticulo->nom == usarArt) {
                cout << "\n>>> Has usado el artículo: " << usarArt 
                     << " (Potencia: " << actualArticulo->potenciadano << ")" << endl;
                encontrado = true;

                // Eliminar el artículo de la sublista
                if (anterior == NULL) {
                    // Era el primer artículo
                    actualCategoria->sub = actualArticulo->sig;
                } else {
                    anterior->sig = actualArticulo->sig;
                }

                delete actualArticulo;
                cout << "El artículo '" << usarArt << "' ha sido eliminado de la multilista.\n";
                return; // Termina la función después de eliminarlo
            }
            anterior = actualArticulo;
            actualArticulo = actualArticulo->sig;
        }
        actualCategoria = actualCategoria->sig;
    }

    if (!encontrado) {
        cout << "\nNo se encontró el artículo '" << usarArt << "' en ninguna categoría.\n";
    }
}

int main() {
    Categoria* cab = NULL;
    string nom; 
    int potenciadano; 
    int cantcateg, cantart;  

    cout << "==============================\n";
    cout << "|          JUEGO             |\n"; 
    cout << "==============================\n\n";
    cout << " CREADO POR: Jhon Rodriguez | CODIGO: 67001483\n\n"; 
    cout << "-------------------------------------------------------------------\n";
    cout << "DESCRIPCION: Juego de Heroes y Villanos...\n";
    cout << "-------------------------------------------------------------------\n\n";

    cout << "Ingrese la cantidad de categorias: ";  
    cin >> cantcateg; 
    cin.ignore(); // Limpia el buffer

    for (int i = 1; i <= cantcateg; i++) {
        cout << "Nombre de la categoria #" << i << ": ";  
        getline(cin, nom); 
        insertarcategoria(cab, crearcategoria(nom));  
    }

    Categoria* aux = cab;  
    while (aux != NULL) {
        cout << "\nCategoria: " << aux->nom << endl; 
        cout << "Cantidad de articulos a agregar: "; 
        cin >> cantart; 
        cin.ignore(); // Limpia buffer

        for (int i = 1; i <= cantart; i++) {
            cout << "   - Nombre del articulo #" << i << ": "; 
            getline(cin, nom); 
            cout << "   - Potencia de golpe: ";  
            cin >> potenciadano; 
            cin.ignore();
            insertararticulo(aux->sub, creararticulo(nom, potenciadano));  
        }
        aux = aux->sig;  
    }  

    cout << "\n========== LISTA COMPLETA ==========\n"; 
    imprimirtodo(cab); 

    string usarArt; 
    cout << "\nIngrese el nombre del articulo que desea usar: "; 
    getline(cin, usarArt); 

    usarYEliminarArticulo(cab, usarArt);

    cout << "\n========== LISTA ACTUALIZADA ==========\n"; 
    imprimirtodo(cab);

    return 0;  
}

