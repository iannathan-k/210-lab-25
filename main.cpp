#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
using namespace std;
using namespace std::chrono;

// COMSC-210 | Lab 25 | Ian Kusmiantoro

const int SIZE = 20000;

void timeReading(vector<string>& v, list<string>& l, set<string>& s);

int main() {
    
    vector<string> v;
    list<string> l;
    set<string> s;

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/

void timeReading(vector<string>& v, list<string>& l, set<string>& s) {
    ifstream fin;
    fin.open("codes.txt");

    if (!fin.good()) {
        cout << "Error opening file" << endl;
        return;
    }

    // VECTOR TESTING
    auto start = high_resolution_clock::now();

    string code;
    while (fin >> code) {
        v.push_back(code);
    }

    auto end = high_resolution_clock::now();
    auto v_duration = duration_cast<nanoseconds>(end - start);

    // LIST TESTING
    fin.clear();
    fin.seekg(0); // move pointer to the beginning of the file
    start = high_resolution_clock::now();

    while (fin >> code) {
        l.push_back(code);
    }

    end = high_resolution_clock::now();
    auto l_duration = duration_cast<nanoseconds>(end - start);
    
    // SET TESTING
    fin.clear();
    fin.seekg(0); // move pointer to the beginning of the file
    start = high_resolution_clock::now();

    while (fin >> code) {
        s.insert(code);
    }

    end = high_resolution_clock::now();
    auto s_duration = duration_cast<nanoseconds>(end - start);
}