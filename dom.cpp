#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <exception>
#include <vector>
#include "parse.h"

using namespace std;

class Dom{
		startTag *self;
		Dom *parent;
		vector<Dom*> children;
	public:
		Dom(startTag*, Dom*);

		vector<attribute*> get_attrs();

		string get_name();

		string get_text();

		Dom* get_parent();

		vector<Dom*> get_children();


		void add_child(Dom *d);

		// check whether the str is same as 
		// the tag name, name attribute of id attribute
		bool is_tag(string str);

		bool is_name(string n);

		bool is_id(string i);

		bool has_link();

		string getLink();

		~Dom();
};

// constructor for Dom object
Dom::Dom(startTag *st, Dom *p){
	self = st;
	parent = p;
}

// get the attributes of current dom
vector<attribute*> Dom::get_attrs(){
	vector<attribute*> attrs;
			try {
				attrs = self->attrs;
			}
			catch(exception &e){
				cout<<e.what();
			}
			return attrs;
}

// get the name of the current tag
string Dom::get_name(){
	return self->name;
}

// get the text if the current dom has text
string Dom::get_text(){
	return self->text;
}

// get the parent of current dom
Dom* Dom::get_parent(){
	return parent;
}
// get the vector of children
vector<Dom*> Dom::get_children(){
	vector<Dom*> childs;
	try{
		childs = children;
	}
	catch(exception &e){
		cout<<e.what();
	}
	return childs;
}

// check whether the tag name is same as current dom's name
bool Dom::is_tag(string str){
	if (self->name == str){
		return true;
	}
	else {
		return false;
	}
}

// check whether the current dom's name attribute is same as the input name
bool Dom::is_name(string n){
	bool is = false;
	for (int i=0; i<self->attrs.size();i++){
		if (self->attrs[i]->name == "name" && self->attrs[i]->value == n){
			is = true;
		}
	}
	return is;
}

// check whether the current dom's id attribute is same as the input id
bool Dom::is_id(string id){
	bool is = false;
	for (int i=0; i<self->attrs.size();i++){
		if (self->attrs[i]->name == "id" && self->attrs[i]->value == id){
			is = true;
		}
	}
	return is;
}

// check whther current dom has a link
bool Dom::has_link(){
	bool has = false;
	for (int i=0; i<self->attrs.size();i++){
		if (self->attrs[i]->name == "href"){
			has = true;
		}
	}
	return has;
}

// get the link if current dom has link
string Dom::getLink(){
	string l = "";
	if (this->has_link()){
		for (int i=0; i<self->attrs.size();i++){
			if (self->attrs[i]->name == "href"){
				l = self->attrs[i]->value;
			}
		}
	}
	return l;
}

// destructor of Dom
Dom::~Dom(void){
	for (int i=0; i<self->attrs.size();i++){
		delete(self->attrs[i]);
		cout<<"attribute deleted"<<endl;
	}
	cout<<"The dom object is being deleted"<<endl;
}
// add children dom to the current dom 
void Dom::add_child(Dom* d){
	children.push_back(d);
}

// test the dom object

int main(){
	char h[] = "<html>";
	startTag *st1 = create_start_tag(h);
	Dom *d1 = new Dom(st1, NULL);
	char b[] = "<body name='b1' id='bb'>This is body";
	startTag *st2 = create_start_tag(b);
	
	Dom *d2 = new Dom(st2, d1);
	d1->add_child(d2);
	char c[] = "<a href='http://golang.com' id='li'>This is a link";
	startTag *st3 = create_start_tag(c);
	
	Dom *d3 = new Dom(st3, d2);
	d2->add_child(d3);
	cout<<d1<<endl;
	cout<<d2->get_parent()->get_name()<<endl;
	vector<attribute*> d2_attrs = d3->get_parent()->get_attrs();
	print_attrs(d2_attrs);
	cout<<"child d2's text: "<<d1->get_children()[0]->get_text()<<endl;
	cout<<"child d3's text: "<<d2->get_children()[0]->get_text()<<endl;
	cout<<"d2 is body tag: "<<d2->is_tag("<body")<<endl;
	cout<<"d2's name is bb: "<<d2->is_name("'bb'")<<endl;
	cout<<"d3 's id is li: "<<d3->is_id("'li'")<<endl;
	cout<<"d2 has links: "<<d2->has_link()<<endl;
	cout<<"d3's link: "<<d3->getLink()<<endl;
	delete(d1);
	delete(d2);
	delete(d3);
	return 0;
}

