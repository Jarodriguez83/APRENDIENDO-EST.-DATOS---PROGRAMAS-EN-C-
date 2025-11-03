#include <iostream>
using namespace std; 
void modificar (int x){
	x++; 
	cout<<x;  
}
int modificar2 (int x){
	x++;
	return x; 
	cout<<x<<endl;  
}
void modificar3 (int &x){
	x++; 
	cout<<"Valor del paso por referencia: "<<x<<endl;  
}
int main(){
	int x=5;  
	cout<<x<<endl;  
	modificar(x);
	cout<<endl;   
	cout<<x<<endl;
	cout<<"Valor retornado por modificar 2: "<<modificar2(x)<<endl;   
	cout<<x<<endl;  
	modificar3(x);  
	cout<<x<<endl;  
	return 0; 
}