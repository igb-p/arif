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

void perc(std::map<char, float[2]>& m) 
{
    char a; ifstream b("D:/text.txt"); ofstream a1("D:/r.txt");
    double high=0, low=0, ol=0, oh=0, ch;
    int i = 0, size, r;
    map<char, float[2]>::iterator it;
    b >> a;
    it = m.find(a); 
    ol = m[it->first][0]; 
    oh = m[it->first][1];
    while (b)
    {
        while (i < 9&&b) 
        {
            b >> a; it = m.find(a);
            low = ol + (oh - ol) * m[it->first][0];
            high = ol + (oh - ol) * m[it->first][1];
            ol = low; oh = high; i++;
        }
        i = 0; b >> a; 
        it = m.find(a);
        ol = m[it->first][0];
        oh = m[it->first][1];
        //cout << '[' << low << ' ' << high << ']' << endl;
        ch = 0; size = 31, r = 0;
        while (ch < low)
        {

            if (ch + pow(2, -(32 - size)) < high)
            { 
                //cout << 32 - size << ' ' << ch + pow(2, -(32 - size)) << endl;
                ch += pow(2, -(32 - size));
                r |= 1 << size;
                /*cout << '1';*/
            }
            else {
                //cout << "a " << 32 - size << ' ' << ch + pow(2, -(32 - size)) << endl;
            } /*'0'; */
            size--;
        }
        cout << endl;
        cout << ch << endl;
        a1 << r;
    }
}

int main() 
{
    cout << fixed;
    cout.precision(16);
    int i;
    float aski[256]; char x;
    float low=0, high=0, num=0;
    list<Node*> l;
    list<Node*>::iterator j;
    map<char, float[2]> ma;
    map<char, float[2]>::iterator it;
    for (i = 0; i < 256; i++) aski[i] = 0;
    ifstream a("D:/text.txt"); ofstream aa("D:/chst.txt");
    a.get(x); 
    while (a) {
        aski[(int)x]++; a.get(x); num++;
    }
    for (i = 0; i < 256; i++) {
        if (aski[i] != 0)
        {
            Node* r = new Node; r->key = (char)i; r->p = aski[i] / num;
            aa << ' '; aa << r->key; aa<<r->p;
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
    perc(ma);
}