#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <exception>
#include <vector>
#include "Dom.h"

using namespace std;

// find the targeted dom child recursively
void find_helper(Dom *me, vector<Dom*> &result, string filter){
	if (me == NULL){
		return;
	}
	else {
		//cout<<"finding: "<<me->get_name()<<endl;
		if (me->is_tag(filter) || me->has_attribute(filter)){
			result.push_back(me);
		}
		for (int i=0; i<me->get_children().size(); i++){
			find_helper(me->get_children()[i], result, filter);
		}
	}
}

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
				cout<<"Exception name: "<<e.what();
			}
			return attrs;
}

// get the name of the current tag
string Dom::get_name(){
	return self->name;
}

// get the text if the current dom has text
string Dom::getText(){
	return self->text;
}

// get the parent of current dom
Dom* Dom::get_parent(){
	return parent;
}

void Dom::set_parent(Dom *p){
	this->parent = p;
}
// get the vector of children
vector<Dom*> Dom::get_children(){
	vector<Dom*> childs;
	try{
		childs = children;
	}
	catch(exception &e){
		cout<<"Exception name: "<<e.what();
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

bool Dom::is_href(string link){
	bool is = false;
	for (int i=0; i<self->attrs.size();i++){
		if (self->attrs[i]->name == "href" && self->attrs[i]->value == link){
			is = true;
		}
	}
	return is;
}

bool Dom::has_attribute(string attr_name){
	bool has = false;
	for (int i=0; i<self->attrs.size();i++){
		if (self->attrs[i]->value == attr_name){
			has = true;
		}
	}
	return has;
}

// check whther current dom has a link
bool Dom::has_link(){
	/*
	bool has = false;
	for (int i=0; i<self->attrs.size();i++){
		if (self->attrs[i]->name == "href"){
			has = true;
		}
	}
	return has;*/
	return (self->name == "a");
}

bool Dom::has_img(){
	return (self->name == "img");
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
	else {
		l = "Error finding link";
	}
	return l;
}

// get the img src if the current dom is img dom
string Dom::getImg(){
	string l = "";
	if (this->has_img()){
		for (int i=0; i<self->attrs.size();i++){
			if (self->attrs[i]->name == "src"){
				l = self->attrs[i]->value;
			}
		}
	}
	else {
		l = "Error finding img src";
	}
	return l;
}

vector<Dom*> Dom::find(string filter){
	vector<Dom*> result;
	find_helper(this, result, filter);
	return result;
}

// destructor of Dom
Dom::~Dom(void){
	delete(self);
	for (int i=0; i<self->attrs.size();i++){
		delete(self->attrs[i]);
		cout<<"attribute deleted"<<endl;
	}
	for (int i=0; i<this->children.size();i++){
		delete(this->children[i]);
	}
	cout<<"The dom object is being deleted"<<endl;
}
// add children dom to the current dom
void Dom::add_child(Dom* d){
	children.push_back(d);
}

// test the dom object
/*
int main(){
	char h[] = "html>";
	startTag *st1 = create_start_tag(h);
	Dom *d1 = new Dom(st1, NULL);
	char b[] = "body name='b1' id='bb'>This is body";
	startTag *st2 = create_start_tag(b);

	Dom *d2 = new Dom(st2, d1);
	d1->add_child(d2);
	char c[] = "a href='http://golang.com' id='li'>This is a link";
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
*/
