#include <iostream>
using namespace std;
struct Celular{
	string Marca;
	string modelo;
	Celular* enlace;
};
//función para insertar al inicio
void insertarI(Celular* &cab,string mar,string mod){
	Celular* nuevoCelular=new Celular{mar,mod};
	nuevoCelular->enlace=cab;
	cab=nuevoCelular;
}
//función para insertar al final
void insertarF(Celular* &cab, string mar, string mod){
    Celular* nuevoCelular = new Celular{mar, mod};
    if (cab == NULL) {
        cab = nuevoCelular;
    } else {
        Celular* actual = cab;
        while (actual->enlace != NULL) {
            actual = actual->enlace;
        }
        actual->enlace = nuevoCelular;
    }
}
//función para insertar en el medio después de un celular
//buscado por el modelo
void insertarM(Celular* cab, string mar, string mod, string refMod){
    Celular* nuevoCelular = new Celular{mar, mod};
    Celular* actual = cab;
    while (actual->modelo !=refMod) {
        actual = actual->enlace;
    }
    nuevoCelular->enlace = actual->enlace;
    actual->enlace = nuevoCelular;
}

//eliminar el primer celular
void eliminarI(Celular* &cab){   
        Celular* temp = cab;
        cab = cab->enlace;
        delete temp;  
}

//eliminar celular del medio según su modelo
void eliminarM(Celular* cab, string mod) {
   
    Celular* eliminar = cab;
    Celular* anterior;
    while (eliminar->modelo != mod) {
        anterior=eliminar;
		eliminar = eliminar->enlace;
    }
    anterior->enlace=eliminar->enlace;
    delete eliminar;    
}

//función para mostrar la lista 
void mostrar(Celular* cab){
    Celular* actual = cab;
    while (actual != NULL) {
        cout << "Marca: " << actual->Marca << ", Modelo: " << actual->modelo << endl;
        actual = actual->enlace;
    }   
}

//función que retorna un Celular si encuentra su modelo
Celular* buscar(Celular* cab, string mod){
    Celular* actual = cab;
    while(actual != NULL){
        if(actual->modelo == mod){
            return actual;
        }
        actual = actual->enlace;
    }
    return NULL;
}

int main(){
	
	Celular* listaCelulares = NULL;

    // Insertar celulares al inicio y al final
    cout << "--- Insertando al inicio y al final ---" << endl;
    insertarI(listaCelulares, "Samsung", "S21");
    insertarI(listaCelulares, "Xiaomi", "Redmi Note 10");
    insertarF(listaCelulares, "Apple", "iPhone 13");
    insertarF(listaCelulares, "Google", "Pixel 6");
    mostrar(listaCelulares);

    // Insertar un celular en el medio
    cout << "\n--- Insertando en el medio ---" << endl;
    insertarM(listaCelulares, "OnePlus", "9 Pro", "Redmi Note 10");
    mostrar(listaCelulares);

    // Buscar un celular por su modelo
    cout << "\n--- Buscando un celular (OnePlus 9 Pro) ---" << endl;
    Celular* encontrado = buscar(listaCelulares, "9 Pro");
    if (encontrado != NULL) {
        cout << "Celular encontrado: Marca: " << encontrado->Marca << ", Modelo: " << encontrado->modelo << endl;
    } else {
        cout << "Celular no encontrado." << endl;
    }
    // Eliminar el primer nodo
    cout << "\n--- Eliminando el primer celular ---" << endl;
    eliminarI(listaCelulares);
    mostrar(listaCelulares);
    // Eliminar un nodo en el medio
    cout << "\n--- Eliminando un celular en el medio (iPhone 13) ---" << endl;
    eliminarM(listaCelulares, "iPhone 13");
    mostrar(listaCelulares);
	cout<<"hola mundo";
	return 0;
}