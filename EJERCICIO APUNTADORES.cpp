#include <iostream>
using namespace std; 
struct Libro{
	char titulo[100]; 
	int paginas; 
};
int main(){
	Libro l1; 
	Libro*	ptr; 
	ptr = &l1;  
	(*ptr).paginas = 120;  
	strcpy (ptr->titulo, "CIEN AÑOS DE SOLEDAD");   
	cout<<"El nombre del libro es: " << ptr->titulo<<endl; 
	cout<<"La cantidad de paginas que tiene el libro son: "<<(*ptr).paginas<<endl; 
	cout<<"La dirección del puntero es: "<<&l1<<endl;  
	return 0; 
}