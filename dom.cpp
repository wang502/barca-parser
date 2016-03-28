#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <exception>
#include <vector>
#include "parse.cpp"

using namespace std;

class Dom{
		startTag *self;
		Dom *parent;
		vector<Dom*> children;
	public:
		Dom(startTag*, Dom*);

		vector<attribute*> get_attrs();

		string get_name();

		Dom* get_parent();

		vector<Dom*> get_children();

		void add_child(Dom *d);

		~Dom();
};

// constructor for Dom object
Dom::Dom(startTag *st, Dom *p){
	self = st;
	parent = p;
}

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

string Dom::get_name(){
	return self->name;
}

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

Dom::~Dom(void){
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
	char c[] = "<a href='http://golang.com'>";
	startTag *st3 = create_start_tag(c);
	
	Dom *d3 = new Dom(st3, d2);
	d2->add_child(d3);
	cout<<d1<<endl;
	cout<<d2->get_parent()->get_name()<<endl;
	vector<attribute*> d2_attrs = d3->get_parent()->get_attrs();
	print_attrs(d2_attrs);
	delete(d1);
	delete(d2);
	delete(d3);
	return 0;
}

