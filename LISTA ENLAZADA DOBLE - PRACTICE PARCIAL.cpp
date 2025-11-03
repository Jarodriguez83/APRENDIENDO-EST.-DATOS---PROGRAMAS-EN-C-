#include <iostream>
using namespace std;
struct Atleta{
	int id;
	int tiempo;
	Atleta* sig, * ant;	
};
Atleta* crearAtleta(int i, int t){
	Atleta* nuevoA=new Atleta{i,t};
	return nuevoA;
}
void insertarInicio(Atleta* & cab, Atleta* nuevo){
	if(cab==NULL){
		cab=nuevo;
	}else{
		nuevo->sig=cab;
		cab->ant=nuevo;
		cab=nuevo;
	}	
}
void mostrarAtletas(Atleta* cab){
	Atleta* aux=cab;
	while(aux!=NULL){
		cout<<"ID: "<<aux->id<<" Tiempo: "<<aux->tiempo<<endl;
		aux=aux->sig;
	}
}
int main(){
Atleta* cab=NULL;
	Atleta* aux;
	int tiempo, id=100, N;
	cout<<"Cuantos atletas quiere registrar"<<endl;
	cin>>N;
	for(int i=1;i<=N;i++) {
		cout<<"Ingrese el tiempo"<<endl;
		cin>>tiempo;
		aux=crearAtleta(id,tiempo);	
		insertarInicio(cab,aux);
		id++;
	}
	mostrarAtletas(cab);
	return 0;
}








