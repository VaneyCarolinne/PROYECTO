#ifndef DOM_H
#define DOM_H
#include <iostream>
#include <list>
#include "Element.h"
#include "Node.h"
using std::list;
class DOM_Tree
{
	private:
	//atributos
		Node *First;
		//Métodos de Inspección:
	    void buscar(Element e,Node *aux,Node &found);
		//Métodos de Modificación
		Node *copiar(Node *p);
		void destruir(Node *apRaiz);
	public : // (Públicos)
		//Constructores:
		DOM_Tree():First(NULL){}
		DOM_Tree(Element e);
		DOM_Tree(const DOM_Tree &copying);
		DOM_Tree(Element parameter,list< DOM_Tree > x);
		//Metodos de Inspeccion:
		DOM_Tree childNode(int pos);
		DOM_Tree getElementByID(Element e);
		//Metodos de Modificacion:
		void appendChild(int pos,DOM_Tree &a);
		void appendChild(DOM_Tree &a);
		void removeChild(int pos);
		void replaceChild(int pos, DOM_Tree &subArbol);	
		//Sobrecarga de operadores:
		void operator=(const DOM_Tree &orig);
		//Destructor: 
		~DOM_Tree();	
}; 
/******************************************/
/********Constructores de la Clase:*******/
/*****************************************/
DOM_Tree::DOM_Tree(Element e)
{	
	First= new Node(e,NULL,NULL);
}
DOM_Tree::DOM_Tree(Element parameter,list< DOM_Tree > x)
{
	
	Node *creado,*a;
		
		if(!x.empty()){
			First= new  Node(parameter);
			creado=copiar(x.front().First);
			First->setFirstChild(creado);
			x.pop_front();
			a=creado;
			while(!x.empty())
			{
				
				creado=copiar(x.front().First);
				a->setNextSibling(creado);
				x.pop_front();
				a=creado;
			}
		}
}
DOM_Tree::DOM_Tree(const DOM_Tree &copying)
{
	Node *c;
	c=copiar(copying.First);
	First=c;
}
/*****************************/
/***Métodos de Inspección:****/
/*****************************/

DOM_Tree DOM_Tree::childNode(int pos){
	Node *aux,*aux2;
	DOM_Tree a;
	int p=1;
	aux=First->firstChild();
	while(p<pos && aux->nextSibling()!=NULL){
		p++;
		aux=aux->nextSibling();
	}
	if(p==pos){
		aux2=aux->nextSibling();
		aux->setNextSibling(NULL);
		a.First=copiar(aux);
	}
	return a;
}
DOM_Tree DOM_Tree::getElementByID(Element e)
{
	DOM_Tree r;
	Node *aux;
	aux=NULL;
	buscar(e,First,*aux);
	r.First=copiar(aux);
	return (r);
}
void DOM_Tree::buscar(Element e,Node *aux,Node &found)
{
	if(aux!=NULL)
	{
		if(e==aux->element())
		{
			found=*aux;
		}
		else{
			buscar(e,aux->firstChild(),found);
			buscar(e,aux->nextSibling(),found);	
		}	
	}	
}
/*****************************/
/****Métodos Modificadores:***/
/*****************************/
void DOM_Tree::appendChild(int pos,DOM_Tree &a){
	
	Node *aux,*aux2,*aux3;
	int p=1;
	aux2=a.First;
	if(pos==1 && First->firstChild()==NULL){
		First->setFirstChild(copiar(a.First));
	}
	else{
		aux=First->firstChild();
		aux3=aux;
		while(p<pos && aux->nextSibling()!=NULL){
			aux3=aux;
			aux=aux->nextSibling();
			p++;
		}
		if(p==pos){
			aux3->setNextSibling(copiar(a.First));
			aux2=aux3->nextSibling();
			aux2->setNextSibling(aux);
		}else{
		  if(p+1==pos){
			aux3->setNextSibling(copiar(a.First));
			aux2=aux3->nextSibling();
			aux2->setNextSibling(NULL);
		  }		
		}
		else{
			if(p+1==pos){
				aux3->setNextSibling(copiar(a.First));
				aux2=aux3->nextSibling();
				aux2->setNextSibling(NULL);
			}
		}
	}
}
	
void DOM_Tree::appendChild(DOM_Tree &a){
	
	Node *aux;
	if(First->firstChild()==NULL){
		First->setFirstChild(copiar(a.First));
	}
	else{
		aux=First->firstChild();
		while(aux->nextSibling()!=NULL){
			aux=aux->nextSibling();
		}
		aux->setNextSibling(copiar(a.First));
	}
}
Node * DOM_Tree::copiar(Node *p)
{
	if(p!=NULL)
	{
		return(new Node(p->element(),copiar(p->firstChild()),copiar(p->nextSibling())));
		
	}else
		{
			return (NULL);
		}	
}
void DOM_Tree::replaceChild(int pos, DOM_Tree &subArbol)
{
	int i;
	Node* aux,*aux2;
	aux=First->firstChild();
	aux2=aux->nextSibling();
	if(pos==1)
	{
		aux->setNextSibling(NULL);
		First->setFirstChild(subArbol.First);
		subArbol.First->setNextSibling(aux2);
		destruir(aux);	
	}else{
		for(i=2;i<pos;i++)
		{
			aux=aux2;
			aux2=aux2->nextSibling();
		}
		aux->setNextSibling(subArbol.First);
		subArbol.First->setNextSibling(aux2->nextSibling());
		aux2->setNextSibling(NULL);
		destruir(aux2);
	}		
}
void DOM_Tree::removeChild(int pos)
{
	Node *aux,*aux2;
	int i;
	
	if(First!=NULL&&pos!=0){
		if(pos==1){
			aux=First->firstChild();
			First->setFirstChild(aux->nextSibling());
			aux->setNextSibling(NULL);
			destruir(aux);
		}else{
			aux=First->firstChild();
			i=2;
			while(i<pos&&aux!=NULL)
			{
				aux=aux->nextSibling();
				i++;
			}
			if(aux!=NULL&&aux->nextSibling()!=NULL){
				aux2=aux->nextSibling();
				aux->setNextSibling(aux->nextSibling()->nextSibling());
				aux2->setNextSibling(NULL);
				destruir(aux2);
			}
			
		}	
	}else{
		cout << "Se intento eliminar un SubArbol Inexistente" <<std::endl;
	}	
}
void DOM_Tree::destruir(Node *apRaiz)
{
	// Recorrido en Postorden
	if (apRaiz != NULL)
	{
		destruir(apRaiz->firstChild());
		destruir(apRaiz->nextSibling());
		apRaiz = NULL;
	}
}
/*****************************/
/**Sobrecarga de Operadores:**/
/*****************************/
void DOM_Tree::operator=(const DOM_Tree&orig)
{
		if (this!=&orig)
		{  
			First=copiar(orig.First);
		}
}
/*********************************/
/**Único Destructor de la Clase:**/
/*********************************/
DOM_Tree::~DOM_Tree()
{	
	if(First!=NULL){
		destruir(First);
	}
}
#endif
