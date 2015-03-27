#ifndef Nodo_V
#define Nodo_V
#include <iostream>
using namespace std;
#include "NodoA.h"
template<class T>
class NodoA;
template<class T>// un tipo de dato generico 
class NodoV
{
	private:
		T elemento; //elemento generico 
		NodoV<T> *prox;//apuntador a nodo generico
		NodoA<T> *pri;
	public:	
		//Constructores					
		NodoV():prox(NULL){}
		NodoV(T e):prox(NULL),elemento(e){}//Con parametro
		NodoV(T e,NodoV<T>* sig, NodoA<T>* firts):prox(sig),elemento(e),pri(firts){}//Con parametro
		//Métodos de modificación
		void modificarElemento(T e){elemento=e;}
		void modificarProximo(NodoV<T>* sig){prox=sig;}
		void modificarPri(NodoA<T>* f){pri=f;}
		//Métodos de Inspección
		NodoV<T>* proximo()const{return(this->prox);}
		NodoA<T>* ObtAdy()const{return(pri);}
		T obt_elemento()const{return(this->elemento);}
};

#endif
