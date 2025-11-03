#include <iostream>
using namespace std; 
struct Estudiante{
	string nombre;  
	int edad; 
}est1;
int main(){
	Estudiante* ptr = &est1; 
	cout<<"La dirección en memoria de la variable est1 es: "<<&est1<<endl; 
	
	
	
	return 0;  
	
}