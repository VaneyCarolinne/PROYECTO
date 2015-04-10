#ifndef DOM_H
#define DOM_H
#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <queue>
#include <stack>
#include "Element.h"
#include "Node.h"
using std::list;
using std::queue;
using std::stack;
using std::string;
class DOM_Tree
{
	private:
	//atributos
		Node *First;
		//Métodos de Inspección:
	    void buscar(string e,Node *aux,Node *&found);
	    void mostrar(Node *p);
		//Métodos de Modificación
		Node *copiar(Node *p);
		void destruir(Node *apRaiz);
		DOM_Tree convertir(string h);
	public : // (Públicos)
		//Constructores:
		DOM_Tree():First(NULL){}
		DOM_Tree(Element e);
		DOM_Tree(const DOM_Tree &copying);
		DOM_Tree(Element parameter,list< DOM_Tree > x);
		//Metodos de Inspeccion:
		DOM_Tree childNode(int pos);
		DOM_Tree getElementByID(string e);
		//Metodos de Modificacion:
		void appendChild(int pos,DOM_Tree &a);
		void appendChild(DOM_Tree &a);
		void removeChild(int pos);
		void replaceChild(int pos, DOM_Tree &subArbol);	
		void appendChild(std::string cadena);
		void replaceChild(int pos,std::string cadena);	
		void appendChild(int pos,std::string cadena);
		//Sobrecarga de operadores:
		void operator=(const DOM_Tree &orig);
		friend std::ostream& operator<<(std::ostream& salida ,const DOM_Tree  &A);
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
	Node *aux;
	DOM_Tree a;
	int p=1;
	aux=First->firstChild();
	while(p<pos && aux->nextSibling()!=NULL){
		p++;
		aux=aux->nextSibling();
	}
	if(p==pos){
		aux->setNextSibling(NULL);
		a.First=copiar(aux);
	}
	return a;
}
DOM_Tree DOM_Tree::getElementByID(string e)
{
	DOM_Tree r;
	Node *aux;
	aux=NULL;
	buscar(e,First,aux);
	//cout<<aux->element().getTagName();
	r.First=copiar(aux);
	
	return (r);
}
void DOM_Tree::buscar(string e,Node *aux,Node *&found)
{
	bool band=false;
	list<string> l;
	string k;
	if(aux!=NULL)
	{
		l=aux->element().attributeList();
		while(!l.empty()&&band==false){
			k=l.front();
			l.pop_front();
			if(k==e){
				cout<<"encontrado"<<endl;
				band=true;
			}
			
		}
		
		if(band)
		{
			found=aux;
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
	
  if(pos!=0){
	Node *aux,*aux2,*aux3;
	int p=1;
	if(pos==1 && First->firstChild()==NULL){
		First->setFirstChild(copiar(a.First));
	}
	else{
		if(First->firstChild()!=NULL)
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
	}
  }else{
	cerr << "Quiere insertar una posición del árbol inexistente" <<endl;  
  }	
}
void DOM_Tree::replaceChild(int pos,string h)
{
  if(pos!=0){
    DOM_Tree DOM=convertir(h);
    replaceChild(pos,h);
  }else{
	cerr << "Quiere modificar una posición del árbol inexistente" <<endl;  
  } 
}

void DOM_Tree::appendChild(int pos,string h)
{
   if(pos!=0){
    DOM_Tree DOM=convertir(h);
    appendChild(pos,DOM);
   }else{
	 cerr << "Quiere insertar una posición del árbol inexistente" <<endl;   
   } 
}

void DOM_Tree::appendChild(std::string cadena)
{
	DOM_Tree DOM=convertir(cadena);
	appendChild(DOM);
}
DOM_Tree DOM_Tree::convertir(string h)
{
    int j, k, i;
    Element e;
    DOM_Tree aux;
    string n1, n2, inn, tag, atr;
    list<string> atrb;
    vector<DOM_Tree> a;
    

    while(!h.empty())
    {
	atrb=list<string>();
        k=h.find('<');
        j=h.find('>');
        if(k!=-1 && j!=-1)
        {
            n1=h.substr(k+1, j-k-1);
            if(n1.find(' ')!=-1)
            {
                i=n1.find(' ');
                tag=n1.substr(0, i);
                n1.erase(0, i+1);
                while(!n1.empty())
                {
                    if(n1.find(' ')!=-1)
                    {
                        i=n1.find(' ');
                        atr=n1.substr(0, i);
                        atrb.push_back(atr);
                        n1.erase(0, i+1);
                    }
                    else
                    {
                        atrb.push_back(n1);
                        n1.clear();
                    }
                }
                n1=tag;
            }
            n2="</"+n1+'>';
            h.erase(0, j+1);
            k=h.find(n2);
            inn=h.substr(0, k);
            h.erase(k, n2.size());
        }
        else
        {
            inn=h;
            h.clear();
        }
        
        e=Element(n1, atrb, inn);
        aux=DOM_Tree(e);
        a.insert(a.begin(), aux);
    }
    a.erase(a.begin());
    
    while(!a.empty())
    {
        aux=a[0];
        a.erase(a.begin()+0);
        if(!a.empty())
        {
            i=0;
            while(a[i].First->element().innerHTML().find(aux.First->element().innerHTML())==-1)
                i++;
            a[i].appendChild(1,aux);
        }
    }
    return (aux);
}	
void DOM_Tree::appendChild(DOM_Tree &a){
	
	Node *aux;
	if(First==NULL)
		First=copiar(a.First);
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
  if(pos!=0){
	int i;
	Node *aux,*aux2;
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
		if(aux2!=NULL){
			aux->setNextSibling(subArbol.First);
			subArbol.First->setNextSibling(aux2->nextSibling());
			aux2->setNextSibling(NULL);
			destruir(aux2);
		}else{
			cerr << "Quiere modificar una posición del árbol inexistente" <<endl;	
		}	
	}
  }else{
	  cerr << "Quiere modificar una posición del árbol inexistente" <<endl;
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
std::ostream& operator<<(std::ostream& salida ,const DOM_Tree &A)
{
	if(A.First!=NULL){
		Node *actual;
		stack< Node* > P,ant;
		int i=0;
	
		if(A.First->element().tagName()!="document"){
			actual=A.First;	
		}else{
			actual=A.First->firstChild();
			salida <<"<!doctype html>"<<endl;	
		}
		if(actual!=NULL){
			P.push(NULL);	
			if(actual->firstChild()!=NULL)
				ant.push(actual);
			while(actual!=NULL)
			{
				salida << setw(i)<<actual->element();
				if(actual->nextSibling()!=NULL)
				{
					P.push(actual->nextSibling());	
				}
				if(actual->firstChild()!=NULL)
				{
					P.push(actual->firstChild());
					cout <<endl;
				}else{
					salida <<"</" <<actual->element().tagName()<<">"<<endl;
					i=i-5;
					if(!ant.empty()&&ant.top()->firstChild()!=NULL&&actual->nextSibling()==NULL){
						salida <<setw(i+1)<<"</" <<ant.top()->element().tagName()<<">"<<endl;
						i=i-5;	
						ant.pop();
					}	
				}
				i=i+5;
				if(actual->firstChild()!=NULL&&ant.top()->element().tagName()!=actual->element().tagName()){
					ant.push(actual);
				}	
				actual=P.top();
				P.pop();	
			}
			if(!ant.empty()){
				salida <<"</" <<ant.top()->element().tagName()<<">"<<endl;	
				ant.pop();
			}	
		}
	}
	return(salida);		
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
