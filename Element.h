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
		Element(string t,list<string> l,string i);
		string getTagName();
		list<string> attributeList();
		string getInnerHTML();
		void setTagName(string t);
		void setAttributeList(list<string> l);
		void setInnerHTML(string h);
};

Element:: Element(){
	tagName= " ";
	innerHTML= " ";
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


#endif
