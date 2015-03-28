#ifndef Node_h
#define Node_h
#include <iostream>
#include "Element.h"
class Node
{
	private:
		Element e;
		Node *FirstChild, *NextSibling;
	public:
		Node():e(),FirstChild(NULL),NextSibling(NULL){}
		Node(Element E):e(E),FirstChild(NULL),NextSibling(NULL){}
		Node(Element E, Node *p, Node *n):e(E),FirstChild(p),NextSibling(n){}
		Element element(){return(e);}
		Node* firstChild()const{return(FirstChild);}
		Node* nextSibling()const{return(NextSibling);}
		void setElement(Element E){e=E;}
		void setFirstChild(Node* sig){FirstChild=sig;}
		void setNextSibling(Node* p){NextSibling=p;}
};
#endif
