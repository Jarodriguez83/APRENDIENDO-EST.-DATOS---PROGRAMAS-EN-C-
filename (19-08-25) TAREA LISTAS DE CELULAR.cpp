#include <iostream>
using namespace std;  

struct Celular {
	int referencia;  
	string marca; 
	float precio; 
	Celular * siguiente; 
};

// Insertar al final
void insertar(int r, string m, float p, Celular *&cab) {
	Celular * nuevo = new Celular{r,m,p,NULL}; 
	if (cab==NULL) {
		cab=nuevo; 
	} else {
		Celular *temporal=cab; 
		while(temporal->siguiente!=NULL) {
			temporal=temporal->siguiente; 
		}
		temporal->siguiente=nuevo; 
	}
}

// Imprimir lista
void imprimir(Celular * cab) {
	Celular * temporal = cab; 
	while (temporal!=NULL) {
		cout<<"Referencia: "<< temporal->referencia<<endl;  
		cout<<"Marca: "<< temporal->marca<<endl; 
		cout<<"Precio: "<< temporal->precio<<endl; 
		temporal = temporal -> siguiente; 
		cout<<"--------------------------------"<<endl; 
	}
}

// Insertar después de una posición (como ya lo tenías)
void insertarMedio(int r, string m, float p, Celular *cab, int pos) {
	Celular * nuevo = new Celular{r,m,p,NULL}; 
	Celular * temporal = cab; 
	for (int i=1; i<pos && temporal!=NULL; i++) {
		temporal= temporal->siguiente; // Para recorrer la lista
	}
	if (temporal!=NULL) {
		nuevo->siguiente=temporal->siguiente;  
		temporal->siguiente=nuevo; 
	}
}

// Insertar antes de una posición
void insertarAntes(int r, string m, float p, Celular *&cab, int pos) {
	Celular * nuevo = new Celular{r,m,p,NULL}; 
	if (pos==1) { // Insertar al inicio
		nuevo->siguiente=cab; 
		cab=nuevo; 
	} else {
		Celular * temporal=cab; 
		for (int i=1; i<pos-1 && temporal!=NULL; i++) {
			temporal=temporal->siguiente; 
		}
		if (temporal!=NULL) {
			nuevo->siguiente=temporal->siguiente; 
			temporal->siguiente=nuevo; 
		}
	}
}

// Insertar después de un celular por referencia
void insertarDespuesRef(int ref, int r, string m, float p, Celular *cab) {
	Celular * temporal=cab; 
	while (temporal!=NULL && temporal->referencia!=ref) {
		temporal=temporal->siguiente; 
	}
	if (temporal!=NULL) {
		Celular * nuevo = new Celular{r,m,p,NULL}; 
		nuevo->siguiente=temporal->siguiente; 
		temporal->siguiente=nuevo; 
	}
}

int main() {
	int r; 
	string m; 
	double p; 
	Celular *cab= NULL;  
	cout<<" INGRESE LOS SIGUIENTES DATOS: "<<endl; 
	cout<<"- CUANTOS CELULARES DESEA INGRESAR: ";  
	int w = 0; 
	cin>>w;  
	for (int i=0; i<w; i++) {
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

	// Insertar antes de una posición
	cout<<"- INGRESE LA REFERENCIA DEL CELULAR: ";
	cin>>r;   
	cout<<"- INGRESE LA MARCA DEL CELULAR: "; 
	cin>>m; 
	cout<<"- INGRESE EL PRECIO DEL CELULAR: ";
	cin>>p; 
	int pos=0; 
	cout<<"- DIGITE LA POSICIÓN EN LA CUAL DESEA INGRESAR EL CELULAR ANTES: "; 
	cin>>pos; 
	cout<<"----------------------------------------"<<endl; 
	insertarAntes(r,m,p,cab,pos); 
	imprimir(cab); 

	// Insertar después de un celular por referencia
	cout<<"- INGRESE LA REFERENCIA DEL CELULAR EXISTENTE DESPUÉS DEL CUAL DESEA INSERTAR: ";
	int refBuscar; 
	cin>>refBuscar; 
	cout<<"- INGRESE LA NUEVA REFERENCIA DEL CELULAR: ";
	cin>>r;   
	cout<<"- INGRESE LA MARCA DEL CELULAR: "; 
	cin>>m; 
	cout<<"- INGRESE EL PRECIO DEL CELULAR: ";
	cin>>p; 
	cout<<"----------------------------------------"<<endl; 
	insertarDespuesRef(refBuscar,r,m,p,cab); 
	imprimir(cab); 

	return 0;  
}
