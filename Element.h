#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <iostream>
#include <list>
#include <string>

using namespace std;
using std:: list;

class Element{
	private:
		string TagName, InnerHTML;
		list<string> attrList;
	public:
		Element();
		Element(const Element &copying);
		Element(string t,list<string> l,string i);
		string tagName();
		list<string> attributeList();
		string innerHTML();
		void setTagName(string t);
		void setAttributeList(list<string> l);
		void setInnerHTML(string h);
		void operator=(const Element &R);
		bool operator==(const Element &R);
		friend std::ostream& operator<<(std::ostream& salida ,const Element &A);
};

Element:: Element(){
	TagName= " ";
	InnerHTML= " ";
}
Element:: Element(const Element &copying)
{
	TagName=copying.TagName;
	InnerHTML=copying.InnerHTML;
	attrList=copying.attrList;
}
Element:: Element(string t,list<string> l,string i){
	TagName= t;
	attrList= l;
	InnerHTML= i;
}

string Element:: tagName(){
	return TagName;
}

list<string> Element:: attributeList(){
	return attrList;
}

string Element:: innerHTML(){
	return InnerHTML;
}

void Element:: setTagName(string t){
	TagName= t;
}

void Element:: setAttributeList(list<string> l){
	attrList= l;
}

void Element:: setInnerHTML(string i){
	InnerHTML= i;
}

void Element:: operator=(const Element &R)
{
	if(this!=&R){
		TagName=R.TagName;
		InnerHTML=R.InnerHTML;
		attrList=R.attrList;
	}		
}
bool Element:: operator==(const Element &R)
{
	bool band;
	if(this!=&R){
		if(R.TagName!=TagName||R.InnerHTML!=InnerHTML||R.attrList!=attrList)
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
	salida << "<" << R.tagName();
	if(!l.empty())
		salida <<" ";
	while(!l.empty())
	{
		salida << l.front();
		l.pop_front();	
	}
	salida<< ">"<<R.innerHTML();
	return(salida);
}
#endif
