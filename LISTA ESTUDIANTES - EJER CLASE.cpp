#include <iostream>
using namespace std;  
struct Estudiante {
	string nombre;  
	int codigo;  
	Estudiante * enlace; 
};
//JHON (11-08-25): FUNCIÓN PARA MOSTRAR LOS ESTUDIANTES EN PANTALLA PARA INSERTAR AL INICIO
void mostrarEstIni(Estudiante *cab){
	cout<<"LA LISTA DE LOS ESTUDIANTES ES: "<<endl; 
	Estudiante *temporal=cab; 
	while(temporal!=NULL){
		cout<<"- NOMBRE: "<<temporal->nombre<<endl;  
		cout<<"- CODIGO: "<<temporal->codigo<<endl;  
		cout<<"- DIREC. DE MEMORIA SIG. EST.: "<<temporal->enlace<<endl;  
		cout<<endl; 
		temporal=temporal->enlace; 
	}
}
//JHON (11-08-25): FUNCIÓN PARA MOSTRAR LOS ESTUDIANTES EN PANTALLA PARA INSERTAR AL FINAL
void mostrarEstFin(Estudiante *cab, *enlace){
	cout<<"LA LISTA DE LOS ESTUDIANTES ES: "<<endl; 
	Estudiante *temporal=enlace; 
	while(temporal!=NULL){
		cout<<"- NOMBRE: "<<temporal->nombre<<endl;  
		cout<<"- CODIGO: "<<temporal->codigo<<endl;  
		cout<<"- DIREC. DE MEMORIA SIG. EST.: "<<temporal->enlace<<endl;  
		cout<<endl; 
		temporal=temporal->enlace; 
	}
}
//JHON (11-08-25): FUNCIÓN PARA INSERTAR ESTUDIANTES AL INICIO DE LA LISTA
void insertarInicio(string n, int c, Estudiante *& cab){
	Estudiante *est=new Estudiante;
	est->nombre = n; 
	est->codigo = c; 
	est->enlace = cab; 
	cab=est; 
}
//JHON (11-08-25): FUNCIÓN PARA INSERTAR ESTUDIANTES AL FINAL DE LA LISTA
void insertarFinal(string n, int c, Estudiante *& cab){
	Estudiante *est=new Estudiante; 
	est->nombre = n; 
	est->codigo = c; 
	est->enlace = cab; 
	cab=est;
}

//JHON (11-08-25): CODIFICACIÓN DEL MAIN
int main(){
	Estudiante *cab=NULL;  
	int codigo; 
	string nombre;  
	cout<<"----------------------------------------------------"<<endl; 
	cout<<"     BIENVENIDO A LA LISTA DE ESTUDIANTES. "<<endl; 
	cout<<"----------------------------------------------------"<<endl; 
	cout<<"		- DIGITE LA CANTIDAD DE ESTUDIANTES QUE DESEA AGREGAR A LA LISTA: "; 
	int b=0;
	cin>>b;  
	for (int i=0; i<b; i++){
		cout<<"INGRESE EL NOMBRE DEL ESTUDIANTE: "; 
		cin>>nombre; 
		cout<<"INGRESE EL CODIGO DEL ESTUDIANTE "<<nombre<<": ";  
		cin>>codigo;  
		
		insertarFinal(nombre, codigo, cab);
		mostrarEstFin(cab); 
	}
	return 0; 
}