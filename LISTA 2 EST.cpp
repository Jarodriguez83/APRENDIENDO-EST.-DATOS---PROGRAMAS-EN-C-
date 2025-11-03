#include <iostream>
using namespace std;  

struct Estudiante {
    string nombre;  
    int codigo;  
    Estudiante *enlace; 
};

// FUNCIÓN PARA MOSTRAR LA LISTA (sirve igual para inicio o final)
void mostrarEstudiantes(Estudiante *cab) {
    cout << "LA LISTA DE LOS ESTUDIANTES ES: " << endl; 
    Estudiante *temporal = cab; 
    int pos = 1; // Para mostrar orden 1, 2, 3...
    while (temporal != NULL) {
        cout << pos << ". NOMBRE: " << temporal->nombre << endl;  
        cout << "   CODIGO: " << temporal->codigo << endl;  
        cout << "   DIREC. DE MEMORIA SIG. EST.: " << temporal->enlace << endl;  
        cout << endl; 
        temporal = temporal->enlace; 
        pos++;
    }
}

// FUNCIÓN PARA INSERTAR AL INICIO
void insertarInicio(string n, int c, Estudiante *&cab) {
    Estudiante *est = new Estudiante;
    est->nombre = n; 
    est->codigo = c; 
    est->enlace = cab; 
    cab = est; 
}

// FUNCIÓN PARA INSERTAR AL FINAL
void insertarFinal(string n, int c, Estudiante *&cab) {
    Estudiante *est = new Estudiante;
    est->nombre = n;
    est->codigo = c;
    est->enlace = NULL; // Nuevo nodo siempre apunta a NULL al final

    if (cab == NULL) { 
        // Si la lista está vacía, el nuevo es la cabeza
        cab = est;
    } else {
        // Recorremos hasta el último nodo
        Estudiante *temporal = cab;
        while (temporal->enlace != NULL) {
            temporal = temporal->enlace;
        }
        temporal->enlace = est;
    }
}

int main() {
    Estudiante *cab = NULL;  
    int codigo; 
    string nombre;  

    cout << "----------------------------------------------------" << endl; 
    cout << "     BIENVENIDO A LA LISTA DE ESTUDIANTES. " << endl; 
    cout << "----------------------------------------------------" << endl; 
    cout << " - DIGITE LA CANTIDAD DE ESTUDIANTES QUE DESEA AGREGAR A LA LISTA: "; 
    int b = 0;
    cin >> b;  

    for (int i = 0; i < b; i++) {
        cout << "INGRESE EL NOMBRE DEL ESTUDIANTE: "; 
        cin >> nombre; 
        cout << "INGRESE EL CODIGO DEL ESTUDIANTE " << nombre << ": ";  
        cin >> codigo;  

        insertarFinal(nombre, codigo, cab);
        mostrarEstudiantes(cab); 
    }
    return 0; 
}

