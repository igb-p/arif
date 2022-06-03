#include <iostream>
#include <map>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

struct Node
{
    char key; float p;
};

bool comp(Node* a, Node* b)
{
    return a->p > b->p;
}

void dr(int& kb, double ol, double oh, vector <bool>& v)
{
    double ch = 0; int size = 31;
    kb = 0;
    int i = 0;
    while (ch < ol)
    {

        if (ch + pow(2, -(32 - size)) < oh)
        {
            //cout << 32 - size << ' ' << ch + pow(2, -(32 - size)) << endl;
            ch += pow(2, -(32 - size)); v.push_back(1); 
            /*cout << '1';*/
        }
        else {
            v.push_back(0); /*cout << '0';*/
            //cout << "a " << 32 - size << ' ' << ch + pow(2, -(32 - size)) << endl;
        };/* */
        size--; i++;
        if (i == 8||ch>=ol) { i = 0; kb++; }
    }
    /*cout<<endl << ch << endl;*/
    /*cout << "kb=" << kb;
    cout << endl;*/

}



void perc(std::map<char, float[2]>& m) 
{
    char a, aa=0; ifstream b("D:/text.txt"); ofstream a1("D:/r.txt");
    ofstream aaa("D:/posl.txt");
    double high=0, low=0, ol=0, oh=0;
    int i = 0, kb;
    map<char, float[2]>::iterator it;
    vector <bool>vec;
    vector <bool>vec1;
    b.get(a);
    while (b) {
        vec1.clear();
        int pos=1;
        kb = 0;
        it = m.find(a);
        low = m[it->first][0];
        high = m[it->first][1];
        /*cout << a<<"-";*/
        dr(kb, low, high, vec1);
        if (kb <= 4) { vec = vec1; b.get(a); }
        while (kb < 4 && b)
        {
            /*cout << a<<'-';*/
            vec1.clear();
            kb = 0;
            it = m.find(a); ol = low; oh = high;
            low = ol + (oh - ol) * m[it->first][0];
            high = ol + (oh - ol) * m[it->first][1];
            dr(kb, low, high, vec1);
            if (kb <= 4) { vec = vec1; b.get(a); pos++; }
        }
        /*cout << endl << "pos=" << pos<<endl;*/
        aaa << pos << ' ';
        //cout << '[' << low << ' ' << high << ']' << endl;
        i = 7;
        int byte = 0;
        for (int j = 0; j < vec.size(); j++) 
        {
            /*cout << vec[j];*/
            aa |= vec[j] << i;
            i--;
            if (i < 0 || j == vec.size() - 1) { i = 7; /*cout << (int)aa << endl;*/ a1 << aa; byte++; aa = 0; }
        }
        while (byte < 4) { aa = 0; a1 << aa; byte++; }
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
            aa << ' '; aa << r->key; aa<<aski[i];
            /*cout << (char)i << '-' << aski[i] / num<< endl;*/
            l.push_back(r);
        }
    }
    l.sort(comp);

    for (j=l.begin();j!=l.end();j++)
    {   /*cout<<(*j)->key;*/
        low = high; high = low + (*j)->p;
        ma[(*j)->key][0] = low;
        ma[(*j)->key][1] = high;
       /* cout << '[' << low <<';'<< high << ']'<< endl;*/
    }
    perc(ma);
}