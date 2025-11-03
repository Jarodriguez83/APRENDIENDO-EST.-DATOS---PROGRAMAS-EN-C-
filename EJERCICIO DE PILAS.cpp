#include <iostream>
using namespace std;  

struct Nodo{
	int dato;  
	Nodo * siguiente; 
};

class Pila{
	private: 
		Nodo * cima; 
	public: 
		Pila(){
			cima = NULL;
		}
		void push (int valor){
			Nodo * nuevo = new Nodo(); 
				nuevo->dato = valor; 
				nuevo->siguiente = cima;  
				cima = nuevo;  
				cout << "Se apilo: " << valor<<endl;
				 
			}
		void pop (int valor)
		}
};

int main(){
	
	return 0;  
}