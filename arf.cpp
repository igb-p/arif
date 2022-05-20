﻿#include <iostream>;
#include <map>;
#include <fstream>;
#include <list>;

using namespace std;

struct Node
{
    char key; float p;
};

bool comp(Node* a, Node* b)
{
    return a->p > b->p;
}

void perc(std::map<char, float[2]>& m) 
{
    char a; ifstream b("text.txt");
    float high, low, ol, oh;
    map<char, float[2]>::iterator it;
    b >> a;
    it = m.find(a); 
    ol = m[it->first][0]; 
    oh = m[it->first][1];
    while(b)
    {
        b >> a; it = m.find(a);
        low = ol + (oh - ol) * m[it->first][0];
        high = ol + (oh - ol) * m[it->first][1];
        ol = low; oh = high;
    }

}

int main() 
{
    cout << fixed;
    cout.precision(6);
    int i;
    float aski[256]; char x;
    float low=0, high=0, num=0;
    list<Node*> l;
    list<Node*>::iterator j;
    map<char, float[2]> ma;
    map<char, float[2]>::iterator it;
    for (i = 0; i < 256; i++) aski[i] = 0;
    ifstream a("text.txt");
    a.get(x); 
    while (a) {
        aski[(int)x]++; a.get(x); num++;
    }
    for (i = 0; i < 256; i++) {
        if (aski[i] != 0)
        {
            Node* r = new Node; r->key = (char)i; r->p = aski[i]/num;
            cout << (char)i << '-' << aski[i] / num<< endl;
            l.push_back(r);
        }
    }
    l.sort(comp);

    for (j=l.begin();j!=l.end();j++)
    {   cout<<(*j)->key;
        low = high; high = low + (*j)->p;
        ma[(*j)->key][0] = low;
        ma[(*j)->key][1] = high;
        cout << '[' << low <<';'<< high << ']'<< endl;
    }


        
}