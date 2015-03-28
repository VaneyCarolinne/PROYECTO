#ifndef DOM_H
#define DOM_H
#include <list>
#include <iostream>
#include "Node.h"
#include "Element.h"
using std::list;
class DOM_Tree
{
	private:
		
		
		Node *First;
		Node *copiar(Node *p);
		void destruir(Node *apRaiz);
	public :
		DOM_Tree();
		DOM_Tree(const DOM_Tree &copying);
		DOM_Tree& operator=(const DOM_Tree &orig);
		DOM_Tree(Element parameter,list< DOM_Tree > x);
		Element childNode(int pos);	
		void appendChild(int pos , DOM_Tree adding);
		void removeChild(int pos);
		void replaceChild(int pos, DOM_Tree &subArbol);	
		DOM_Tree getElementByID();
		~DOM_Tree();//Destruye el árbol. 
			
	};


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
DOM_Tree& DOM_Tree::operator=(const DOM_Tree&orig)
{
		if (this != &orig)
		{  destruir(First);
		First=copiar(orig.First);
		}
		return *this;
}

#endif
