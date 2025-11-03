#include <iostream>
using namespace std;  
struct Celular{
	int referencia;  
	string marca; 
	float precio; 
	Celular * siguiente; 
};
void insertar(int r, string m, float p, Celular *&cab){
	Celular * nuevo = new Celular{r,m,p}; 
	if (cab==NULL){
		cab=nuevo; 
	} else{
		Celular *temporal=cab; 
		while(temporal->siguiente!=NULL){
			temporal=temporal->siguiente; 
		}
		temporal->siguiente=nuevo; 
	}
}
void imprimir(Celular * cab){
	Celular * temporal = cab; 
	while (temporal!=NULL){
		cout<< temporal->referencia<<endl;  
		cout<< temporal->marca<<endl; 
		cout<< temporal->precio<<endl; 
		temporal = temporal -> siguiente; 
		cout<<"--------------------------------"<<endl; 
	}
}
void insertarMedio(int r, string m, float p, Celular *cab, int pos){
	Celular * nuevo = new Celular{r,m,p}; 
	Celular * temporal = cab; 
	for (int i=1; i<=pos; i++){
		temporal= temporal->siguiente; //Para recorrer la lista
	}
	nuevo->siguiente=temporal->siguiente;  
	temporal->siguiente=nuevo; 
}
int main(){
	int r; 
	string m; 
	double p; 
	Celular *cab= NULL;  
	cout<<" INGRESE LOS SIGUIENTES DATOS: "<<endl; 
	cout<<"- CUANTOS CELULARES DESEA INGRESAR: ";  
	int w = 0; 
	cin>>w;  
	for (int i=0; i<w; i++){
		cout<<"- INGRESE LA REFERENCIA DEL CELULAR: ";
		cin>>r;   
		cout<<"- INGRESE LA MARCA DEL CELULAR: "; 
		cin>>m; 
		cout<<"- INGRESE EL PRECIO DEL CELULAR: ";
		cin>>p;  
		cout<<"----------------------------------------"<<endl; 
		insertar(r,m,p,cab);  
	}
	imprimir(cab);
	cout<<"- INGRESE LA REFERENCIA DEL CELULAR: ";
		cin>>r;   
		cout<<"- INGRESE LA MARCA DEL CELULAR: "; 
		cin>>m; 
		cout<<"- INGRESE EL PRECIO DEL CELULAR: ";
		cin>>p; 
		int pos=0; 
		cout<<"- DIGITE LA POSICIÓN EN LA CUAL DESEA INGRESAR EL CELULAR: "; 
		cin>>pos; 
		cout<<"----------------------------------------"<<endl; 
	insertarMedio(r,m,p,cab,pos); 
	imprimir(cab); 

	

	return 0;  
}