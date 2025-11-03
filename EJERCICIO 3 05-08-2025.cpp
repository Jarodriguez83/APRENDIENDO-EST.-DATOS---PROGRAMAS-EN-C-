#include <iostream>
using namespace std; 

struct Computador{
	string marca;  
	float precio; 
	int referencia; 
}c1,c2, c3;

void mostrarpc(Computador){
	cout<<"---------------------------------------------"<<endl;  
	cout<<"\t DATOS DEL COMPUTADOR."<<endl;  
	cout<<" 1. MARCA: "<< c2.marca<< endl;  
	cout<<" 2. PRECIO: "<< c2.precio<<endl;  
	cout<<" 3. REFERENCIA: "<<c2.referencia<<endl;  
}

Computador pcostoso(Computador c1, Computador c2){
	if(c1.precio<c2.precio){
		cout<<"EL COMPUTADOR 2 ES MAS COSTOSO"<<endl; 
		return c2;  
	} else{
		cout<<"EL COMPUTADOR 1 ES MAS COSTOSO"<<endl;  
		return c1;  
	}
}

int main(){

	c1.marca="Dell"; 
	c1.precio=123;  
	c1.referencia=56982;
	
	cout<<c1.marca<<endl;
	cout<<c1.precio<<endl;
	cout<<c1.referencia<<endl;  
	
	cout<<"INGRESE LA MARCA DEL PC: ";  
	cin>>c2.marca;  
	cout<<"INGRESE EL PRECIO DEL PC: ";  
	cin>>c2.precio;  
	cout<<"INGRESE ELA REFERENCIA DEL PC: "; 
	cin>>c2.referencia; 
	mostrarpc(c2); 
	cout<<endl;  
	c3 = pcostoso(c1,c2);
	mostrarpc(c3);  
	return 0;  
}