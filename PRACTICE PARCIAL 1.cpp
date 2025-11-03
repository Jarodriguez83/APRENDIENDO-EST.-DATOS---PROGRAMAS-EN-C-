#include <iostream>
using namespace std; 
struct Estudiante{
	string nombre;  
	int codigo; 
	Estudiante * siguiente; 
};

void insertarInicio(Estudiante *& cab, string n, int c){
	Estudiante * nuevo = new Estudiante {n, c}; 
	nuevo->siguiente=cab; 
	cab=nuevo;  
}

void insertarFinal(Estudiante * cab, string n, int c){
	Estudiante * nuevo = new Estudiante {n,c};  
	if (cab==NULL){
		cab=nuevo; 
	} else{
		Estudiante * aux = cab; 
		while (aux->siguiente!=NULL){
			aux= aux->siguiente; 
		}
		aux->siguiente=nuevo; 
	}
}

void imprimir(Estudiante * cab){
	Estudiante * aux = cab;   
	while (aux!=NULL){
		cout<<"NOMBRE: "<<aux->nombre<<endl<<"Codigo: "<<aux->codigo<<endl; 
		aux=aux->siguiente;  
	}	
}


int main(){
	Estudiante * cab = NULL;  
	string n;  
	int c=0;  
	int s=0; 
	cout<<"CANT. ESTUDIANTES PARA REGISTRAR: "; 
	cin>>s; 
	for (int i=0; i<s; i++){
		cout<<"INGRESE EL NOMBRE DEL ESTUDIANTE: ";  
		cin>>n;  
		cout<<"INGRESE EL CODIGO DEL ESTUDIANTE "<<n<<": "; 
		cin>>c;  
		cout<<"-----------------------------------------------"<<endl; 
		insertarInicio(cab, n, c);
		imprimir(cab); 
	}
		cout<<"INGRESE EL NOMBRE DEL ESTUDIANTE: ";  
		cin>>n;  
		cout<<"INGRESE EL CODIGO DEL ESTUDIANTE "<<n<<": "; 
		cin>>c;  
		cout<<"-----------------------------------------------"<<endl; 
		insertarFinal(cab, n, c);
		imprimir(cab); 
	return 0; 
}