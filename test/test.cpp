#include <vector>
#include <cstring>

using namespace std;

void print_attr(attribute* attr){
	cout<<"name: "<<attr->name<<" ";
	cout<<"value: "<<attr->value<<endl;
}

void print_attrs(vector<attribute*> attrs){
	for (int i=0; i<attrs.size();i++){
		print_attr(attrs[i]);
	}
}
