#include <iostream>
using namespace std; 
struct Persona{
	int cedula;  
	int edad; 
	Persona *siguiente, *antes; 
};

Persona * crearPersona(int c, int e){
	Persona * nuevo = new Persona{c, e};  
	return nuevo; 
}

int main(){
	
	return 0; 
}