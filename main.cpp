#include "DOM_Tree.h"
int main()
{
	DOM_Tree DOM,B,C,D,E,F,G,H,V,J;
	Element document,html,head,title,body,h1,p1,p2;
	list<string> l;
	list< DOM_Tree > hijos;
	
	/**Carga de Página HTML**/
	document.setTagName("document");
		html.setTagName("html");
			head.setTagName("head");
				title.setTagName("title");
				title.setInnerHTML("Ejemplo de Página Web");
			//</head>
			body.setTagName("body");
				h1.setTagName("h1");
				h1.setInnerHTML("Una Página Web");
				//</h1>
				p1.setTagName("p");
				l.push_back("id");
				l.push_back("=");
				l.push_back("'Contenido'");
				p1.setAttributeList(l);
				p1.setInnerHTML("Hola Mundo!!!");
				p2.setTagName("p");
				p2.setInnerHTML("Bye!!!");
			//</body>
		//</html>
	/**Construcción del árbol y Prueba de sus Métodos**/
	//~ cout<< B;
	B=DOM_Tree(html);
	//~ cout << B;
	C=DOM_Tree(head);
	D=DOM_Tree(title);
	E=DOM_Tree(body);
	F=DOM_Tree(h1);
	G=DOM_Tree(p1);
	H=DOM_Tree(p2);
	C.appendChild(D);
	//~ cout << C;
	E.appendChild(F);
	//~ cout << E;
	E.appendChild(G);
	E.appendChild(H);
	B.appendChild(1,C);
	B.appendChild(2,E);
	//~ cout << B;
	hijos.push_front(B);
	DOM=DOM_Tree(document,hijos);
	//~ cout << DOM;	
	J=DOM.childNode(1);
	//~ cout << J;
	V=DOM.getElementByID("'Contenido'");	
	cout << V;	
	//~ DOM.replaceChild(1,E);		
	//~ cout << DOM;
	//~ DOM.removeChild(1);
	//~ cout << V;
	return 0;
}
