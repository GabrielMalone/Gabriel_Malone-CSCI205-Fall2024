#include "hash_tables/OpenHashTable.hpp"
#include <string>

OpenHashTable<int>oht;

int main(){

    string g = "gabe";
    string a = "able";
    string b = "bubbles";
    string c = "cookie";
    string d = "darlene";
    string e = "loser";
    string f = "fool";
    string h = "hubble";
    string i = "india";

    int value = 100;
    int other = 1;

    oht.put(g, value);
    // print with one insertion
    oht.print();
    cout << oht.get(g) << endl;
    // print with  more insertions and cause a resize
    oht.put(a, other);
    oht.put(b, other);
    oht.put(c, other);
    oht.put(d, other);
    oht.put(e, other);
    oht.put(f, other);
    oht.put(h, other);
    oht.put(i, other);
    // does get still work ?
    oht.print();
    cout << oht.get(g) << endl;

   
}