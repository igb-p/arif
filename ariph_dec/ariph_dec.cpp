#include <iostream>
#include <map>
#include <fstream>
#include <list>

using namespace std;

struct Node
{
	char key; float p;
};

bool comp(Node* a, Node* b)
{
	return a->p > b->p;
}

void vlist(list<Node*>& l)
{
	char s, pr; float ch;
	ifstream aa("D:/chst.txt");
	aa.seekg(0, ios::beg);
	aa.get(pr); aa.get(s); aa >> ch;
	while (aa)
	{
		Node* r = new Node; r->key = s; r->p = ch;
		cout << r->key << '-' << r->p << endl;
		l.push_back(r);
		aa.get(pr); aa.get(s); aa >> ch;
	}
}

void vmapy(map<char, float[2]>& m, list<Node*> l)
{
	float low = 0, high = 0;
	list<Node*>::iterator j;
	map<char, float[2]>::iterator it;
	for (j = l.begin(); j != l.end(); j++)
	{
		cout << (*j)->key;
		low = high; high = low + (*j)->p;
		m[(*j)->key][0] = low;
		m[(*j)->key][1] = high;
		cout << '[' << low << ';' << high << ']' << endl;
	}
}

int main()
{
	char s, pr; float ch;
	list<Node*> l;
	map<char, float[2]> ma;
	vlist(l);
	l.sort(comp);
	vmapy(ma, l);
}