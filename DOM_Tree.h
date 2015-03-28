#ifndef DOM_H
#define DOM_H
#include <list>
#include<iostream>
#include "Node.h"
#include "element.h"
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
		DOM_Tree(Element parameter,list< DOM_Tree > x);
		Element childNode(int pos);	
		void appendChild(int pos , DOM_Tree adding);
		void removeChild(int pos);	
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
