#include <iostream>
using namespace std;

struct Jugador{
	string nom;
	int bo;
	Jugador* sig;
};

struct Pais{
	string nom;
	Pais* sig;
	Jugador* sub;
};

Pais* crearPais(string nom){
	Pais* nuevo=new Pais{nom};
	return nuevo;
}

void insertarPais(Pais* &cab, Pais* nuevo){
		nuevo->sig=cab;
		cab=nuevo;	
}

Jugador* crearJugador(string nom, int bo){
	Jugador* nuevo=new Jugador{nom,bo};
	return nuevo;
}

void insertarJugador(Jugador* &cab, Jugador* nuevo){
		nuevo->sig=cab;
		cab=nuevo;	
}

void imprimirTodo(Pais* cab){
	Pais* actualPais=cab;
	Jugador* actualJugador;
	while(actualPais!=NULL){//ciclo de lisa principal
		cout<<"Pais "<<actualPais->nom<<endl;
		actualJugador=actualPais->sub;
		while(actualJugador!=NULL){//ciclo sublistas
			cout<<"Nombre "<<actualJugador->nom<<" BO "<<actualJugador->bo<<endl;
			actualJugador=actualJugador->sig;
		}
		actualPais=actualPais->sig;
	}	
}

int main(){
	Pais* cab=NULL;
	string nom;
	int balones;
	for(int i=1;i<=3;i++){
		cout<<"Ingrese el pais"<<endl;
		cin>>nom;
		insertarPais(cab,crearPais(nom));
	}
	imprimirTodo(cab);
	
	Pais* aux=cab;
	while(aux!=NULL){
		cout<<"Pais "<<aux->nom<<endl;
		for(int i=1;i<=3;i++){
			cout<<"Ingrese el jugador"<<endl;
			cin>>nom;
			cout<<"Ingrese la cant de balones"<<endl;
			cin>>balones;
			insertarJugador(aux->sub,crearJugador(nom,balones));
		}
		aux=aux->sig;
		imprimirTodo(cab);
	}
	imprimirTodo(cab);
	
	
	
	
	
	return 0;
}