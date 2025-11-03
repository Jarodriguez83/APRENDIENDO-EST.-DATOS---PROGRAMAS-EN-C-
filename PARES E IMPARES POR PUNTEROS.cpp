//PROGRAMA DONDE DEFINE CUALES SON LOS NÚMEROS PARES E IMPARES PERO POR MEDIO DE PUNTEROS  
#include <iostream>
using namespace std;  

int main(){
	int numero = 0; 
	int *ptr; 
	ptr = &numero;  
	cout<<"- DIGITE UN NUMERO ENTERO: ";  
	cin>>numero; 
	if (*ptr%2==0){
		cout<<"EL NUMERO ES PAR."<<endl;  
	} else{
		cout<<"EL NUMERO ES IMPAR."<<endl; 
	}
	return 0;  
}