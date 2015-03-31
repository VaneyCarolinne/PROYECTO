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
		Node *First;
		Node *copiar(Node *p);
		void destruir(Node *apRaiz);
	public:
		DOM_Tree();
		DOM_Tree(const DOM_Tree &copying);
		DOM_Tree(Element parameter,list< DOM_Tree > x);
		DOM_Tree childNode(int pos);	
		void appendChild(int pos,DOM_Tree a);
		void appendChild(DOM_Tree a);
		void removeChild(int pos);	
		DOM_Tree getElementByID();
		~DOM_Tree();//Destruye el árbol. 	
};

DOM_Tree DOM_Tree::childNode(int pos){
	Node *aux,*aux2;
	DOM_Tree a;
	int p=1;
	aux=First;
	aux=aux->firstChild();
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

void DOM_Tree::appendChild(int pos,DOM_Tree a){
	Node *aux,*aux2,*aux3;
	int p=1;
	aux=First;
	aux2=a.First;
	if(pos==1 && aux->firstChild()==NULL){
		aux->setFirstChild(aux2);
	}
	else{
		aux=aux->firstChild();
		while(p<pos && aux->nextSibling()!=NULL){
			aux3=aux;
			aux=aux->nextSibling();
			p++;
		}
		if(p==pos){
			aux3->setNextSibling(aux2);
			aux2->setNextSibling(aux);
		}
	}
}

void DOM_Tree::appendChild(DOM_Tree a){
	Node *aux,*aux2;
	aux=First;
	aux2=a.First;
	if(aux->firstChild()==NULL){
		aux->setFirstChild(aux2);
	}
	else{
		aux=aux->firstChild();
		while(aux->nextSibling()!=NULL){
			aux=aux->nextSibling();
		}
		aux->setFirstChild(aux2);
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
/********************************destructor *********************************/

void DOM_Tree::destruir(Node *apRaiz)
{
	// Recorrido en Postorden
	if (apRaiz != NULL)
	{
		destruir(apRaiz->firstChild());
		destruir(apRaiz->nextSibling());
		delete apRaiz;
		apRaiz = NULL;
	}
}

DOM_Tree::~DOM_Tree()
{	
	if(First!=NULL){
		destruir(First);
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


#endif
