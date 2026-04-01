#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <iomanip>
using namespace std;
using namespace std::chrono;

// COMSC-210 | Lab 25 | Ian Kusmiantoro

const int SIZE = 20000;

void displayTimes(string row_name, nanoseconds v, nanoseconds l, nanoseconds s);
void timeReading(vector<string>& v, list<string>& l, set<string>& s);

int main() {
    
    vector<string> v;
    list<string> l;
    set<string> s;

    // Display header
    cout << setw(10) << "Operation";
    cout << setw(10) << right << "Vector";
    cout << setw(10) << right << "List";
    cout << setw(10) << right << "Set" << endl;

    timeReading(v, l, s);

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/

void displayTimes(string row_name, nanoseconds v, nanoseconds l, nanoseconds s) {
    cout << setw(10) << right << row_name;
    cout << setw(10) << right << v.count();
    cout << setw(10) << right << l.count();
    cout << setw(10) << right << s.count() << endl;
}

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

    displayTimes("Read", v_duration, l_duration, s_duration);
}

void timeSorting(vector<string>& v, list<string>& l) {
    // VECTOR TESTING
    auto start = high_resolution_clock::now();

    sort(v.begin(), v.end());

    auto end = high_resolution_clock::now();
    auto v_duration = duration_cast<nanoseconds>(end - start);

    // LIST TESTING
    start = high_resolution_clock::now();
    l.sort();

    end = high_resolution_clock::now();
    auto l_duration = duration_cast<nanoseconds>(end - start);

    // SET TESTING
    nanoseconds s_duration(-1);

    displayTimes("Sort", v_duration, l_duration, s_duration);
}

void timeInserting(vector<string>& v, list<string>& l, set<string>& s) {
    // VECTOR TESTING
    auto start = high_resolution_clock::now();

    v.insert(v.begin() + v.size() / 2, "TESTCODE");

    auto end = high_resolution_clock::now();
    auto v_duration = duration_cast<nanoseconds>(end - start);

    // LIST TESTING
    start = high_resolution_clock::now();

    for (int i = 0; i < SIZE; i++) {
        auto it = l.begin();
        advance(it, l.size() / 2);
        l.insert(it, "code");
    }

    end = high_resolution_clock::now();
    auto l_duration = duration_cast<nanoseconds>(end - start);

    // SET TESTING
    nanoseconds s_duration(-1);

    displayTimes("Insert", v_duration, l_duration, s_duration);
}