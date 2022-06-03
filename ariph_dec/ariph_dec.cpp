#include <iostream>
#include <map>
#include <fstream>
#include <list>
#include <vector>
#include <locale.h>

using namespace std;

struct Node
{
	char key; float p;
};

bool comp(Node* a, Node* b)
{
	return a->p > b->p;
}

void vlist(list<Node*>& l, float &weight1)
{
	char s, pr; float ch;
	ifstream aa("D:/chst.txt");

	aa.seekg(0, ios::beg);
	aa.get(pr); aa.get(s); aa >> ch;
	weight1 = ch;
	while (aa)
	{
		Node* r = new Node; r->key = s; r->p = ch;
		/*cout << r->key << '-' << r->p << endl;*/
		l.push_back(r);
		aa.get(pr); aa.get(s); aa >> ch;
		if (aa) weight1+=ch;
	}
	/*cout << weight1 << endl;*/
	aa.close();
}

void vmapy(map<char, float[2]>& m, list<Node*> l, float weight1)
{
	float low = 0, high = 0;
	list<Node*>::iterator j;
	map<char, float[2]>::iterator it;
	for (j = l.begin(); j != l.end(); j++)
	{
		/*cout << (*j)->key;*/
		low = high; high = low + (*j)->p/weight1;
		m[(*j)->key][0] = low;
		m[(*j)->key][1] = high;
		/*cout << '[' << low << ';' << high << ']' << endl;*/
	}
}

void vec(vector<bool>& v, char s) 
{
	int i = 7;
	while (i >= 0) 
	{
		if (s & 1 << i)
		{
			v.push_back(1); /*cout << '1';*/
		}
		else {
			v.push_back(0); /*cout << '0';*/
		}
		i--;
	}
	
}

double chp(vector<bool>& v)
{   
	double ch=0; int p=1;
	for (int i=0;i<v.size();i++)
	{
		if (v[i] == 1) ch += pow(2, -p);
		p++;
	}
	return ch;
}

void srv(double ch, ifstream& pos, ofstream& dec, map<char, float[2]>& m)
{
	map<char, float[2]>::iterator it;
	double low, high;
	int posl, pod=0;
	pos >> posl;
	/*cout << posl << endl;*/
	while (pod != posl)
	{
		it = m.begin();
		while (ch <= m[it->first][0] || ch > m[it->first][1]) it++;
		dec << it->first;
		/*cout << it->first << ' ';*/
	    low = m[it->first][0];
		high = m[it->first][1];
		ch = (ch - low) / (high - low);
		pod++;
	}
	/*cout << endl;*/
}

void decn(map<char, float[2]>& m, float& weight2)
{
	ifstream aa("D:/r.txt", ios::binary);
	ofstream dec("D:/dec.txt");
	ifstream pos("D:/posl.txt");
	double ch; char s;
	int kol = 0;
	vector<bool>v;
	aa.get(s);
	char bu;
	while(aa)
	{
		
		v.clear();
		kol = 0;
		while(kol!=4&&aa)
		{
			if ((int)s == 13)
			{
				aa.get(bu);
				if ((int)bu == 10)
				{
					s = bu; weight2--;
				}
				else aa.seekg(-1, ios::cur);
			}
			vec(v, s);
			aa.get(s);
			kol++;
		}
		/*cout << endl;*/
		ch = chp(v);
		/*cout << ch << endl;*/
		srv(ch, pos, dec, m);
		weight2 += 4;
	}
	aa.close(); dec.close(); pos.close();
}

bool proof()
{
	ifstream dec("D:/dec.txt");
	ifstream ish("D:/text.txt");
	char sim1, sim2;
	dec >> sim1; ish >> sim2;
	while (dec || ish)
	{
		
		if (sim1 != sim2) return false;
		dec >> sim1; ish >> sim2;
	}
	return true;
}

void weight(float weight1, float weight2)
{
	cout << "файл сжат в " << weight1 / weight2 << " раз";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char s, pr; float ch;
	float weight1 = 0, weight2 = 0;
	cout << fixed;
	cout.precision(16);
	list<Node*> l;
	map<char, float[2]> ma;
	vlist(l, weight1);
	l.sort(comp);
	vmapy(ma, l, weight1);
	decn(ma, weight2);
	cout << endl;
	if (proof()) cout << "совпали";
	else cout << "не совпали";
	cout << endl;
	weight(weight1, weight2);


}