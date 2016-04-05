#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <exception>
#include <vector>
#include "Dom.h"
#include "parse.h"

using namespace std;

// test the dom object

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
