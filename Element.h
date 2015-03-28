#ifndef Element_h
#define Element_h
#include <iostream>
#include <string>
#include <list>
using std::list;
template <class T>
class Element
{
	std::string tagName,innerHTML;
	list<std::string> attrList;
};
#endif
