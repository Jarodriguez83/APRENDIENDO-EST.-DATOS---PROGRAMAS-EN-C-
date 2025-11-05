#include <iostream> 
using namespace std; 

struct arbol{ 
	int dato; 
	arbol *i,*d; 
};

arbol* crearNodo(int d){	
	arbol* nuevo = new arbol;
    nuevo->d=NULL;
    nuevo->i=NULL;
    nuevo->dato=d;    
	return nuevo;
}

void insertar(arbol* &a, int d){ 

	if(a==NULL)     
           a = crearNodo(d);
    else if(d < a->dato)
          insertar(a->i,d);
    else if(d > a->dato)
          insertar(a->d,d);
}
	
void inorden(arbol *a){
		if (a!= NULL) {
			inorden(a->i);
			cout<<a->dato<<"  ";	
			inorden(a->d);
		}
}

void buscar(arbol* p, int b){
		
		if(p==NULL)
			cout<<"dato no existe"<<endl;
		else{
			if (b==p->dato)
				cout<<p->dato<<endl;
			else {
				if(b<p->dato)
					buscar (p->i,b);
				else
					buscar (p->d,b);
			}
		}		
}

int main() { 
	arbol* raiz=NULL; 
	int op=1; 
	arbol* e; 
	int d; 
	while (op==1){ 
		cout<<"Ingrese el dato"<<endl; 
		cin>>d; 
		insertar(raiz,d); 
		cout<<"1 Para ingresar otro dato"<<endl; 
		cin>>op; 
	} 
	inorden(raiz);
	cout<<"nodo a buscar "<<endl;
	int b;
	cin>>b;
	buscar(raiz,b);
	return 0; 
}