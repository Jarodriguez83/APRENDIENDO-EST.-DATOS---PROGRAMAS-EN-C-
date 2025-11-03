//RELACIÓN ENTRE ARREGLOS Y PUNTEROS
#include <iostream>
using namespace std;  

int main(){
	int numeros[ ]= {11,22,33,44,55}; 
	int *ptr; 
	ptr = numeros; 
	for (int i=1; i<=5; i++){
		cout<<"El elemento "<<i<<" es: "<<*ptr++<<endl; 
}
	for (int i=1; i<=5; i++){
		cout<<"La dirección del elemento "<<i<<" es: "<<&numeros[i]<<endl; 
	}
	numeros[3]=44; 
	return 0;  
}
