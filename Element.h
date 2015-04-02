#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <iostream>
#include <list>
#include <string>

using namespace std;
using std:: list;

class Element{
	private:
		string tagName, innerHTML;
		list<string> attrList;
	public:
		Element();
		Element(const Element &copying);
		Element(string t,list<string> l,string i);
		string getTagName();
		list<string> attributeList();
		string getInnerHTML();
		void setTagName(string t);
		void setAttributeList(list<string> l);
		void setInnerHTML(string h);
		void operator=(const Element &R);
		bool operator==(const Element &R);
		friend std::ostream& operator<<(std::ostream& salida ,const Element &A);
};

Element:: Element(){
	tagName= " ";
	innerHTML= " ";
}
Element:: Element(const Element &copying)
{
	tagName=copying.tagName;
	innerHTML=copying.innerHTML;
	attrList=copying.attrList;
}
Element:: Element(string t,list<string> l,string i){
	tagName= t;
	attrList= l;
	innerHTML= i;
}

string Element:: getTagName(){
	return tagName;
}

list<string> Element:: attributeList(){
	return attrList;
}

string Element:: getInnerHTML(){
	return innerHTML;
}

void Element:: setTagName(string t){
	tagName= t;
}

void Element:: setAttributeList(list<string> l){
	attrList= l;
}

void Element:: setInnerHTML(string i){
	innerHTML= i;
}

void Element:: operator=(const Element &R)
{
	if(this!=&R){
		tagName=R.tagName;
		innerHTML=R.innerHTML;
		attrList=R.attrList;
	}		
}
bool Element:: operator==(const Element &R)
{
	bool band;
	if(this!=&R){
		if(R.tagName!=tagName||R.innerHTML!=innerHTML||R.attrList!=attrList)
		{
			band=false;	
		}else{
			band=true;	
		}
	}	
	return(band);
}
std::ostream& operator<<(std::ostream& salida ,const Element &A)
{
	Element R=A;
	list<string> l;
	l=R.attributeList();
	salida << "<" << R.getTagName();
	if(!l.empty())
		salida <<" ";
	while(!l.empty())
	{
		salida << l.front();
		l.pop_front();	
	}
	salida<< ">"<<R.getInnerHTML();
	return(salida);
}
#endif
