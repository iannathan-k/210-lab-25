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

const int COLUMN_WIDTH = 15;

void displayTimes(string, nanoseconds, nanoseconds, nanoseconds);
void timeReading(vector<string>&, list<string>&, set<string>&);
void timeSorting(vector<string>&, list<string>&);
void timeInserting(vector<string>&, list<string>&, set<string>&);
void timeDeleting(vector<string>&, list<string>&, set<string>&);

int main() {
    
    vector<string> v;
    list<string> l;
    set<string> s;

    // Display header
    cout << setw(COLUMN_WIDTH) << "Operation";
    cout << setw(COLUMN_WIDTH) << right << "Vector";
    cout << setw(COLUMN_WIDTH) << right << "List";
    cout << setw(COLUMN_WIDTH) << right << "Set" << endl;

    // Code is easily expandible for more races by just adding more functions and calling them here
    // The displayTimes() function can also be reused to make this even simpler
    timeReading(v, l, s);
    timeSorting(v, l);
    timeInserting(v, l, s);
    timeDeleting(v, l, s);

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/

// displayTimes() displays a row, with specified name and times
// parameters: string row_name - the name of the row to be displayed
//             nanoseconds v - the time taken for the vector operation
//             nanoseconds l - the time taken for the list operation
//             nanoseconds s - the time taken for the set operation
// returns: void
void displayTimes(string row_name, nanoseconds v, nanoseconds l, nanoseconds s) {
    cout << setw(COLUMN_WIDTH) << right << row_name;
    cout << setw(COLUMN_WIDTH) << right << v.count();
    cout << setw(COLUMN_WIDTH) << right << l.count();
    cout << setw(COLUMN_WIDTH) << right << s.count() << endl;
}

// timeReading() reads codes from the file into the ADTs and times it
// parameters: vector<string>& v - the vector to read into
//             list<string>& l - the list to read into
//             set<string>& s - the set to read into
// returns: void
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
    fin.clear(); // clear the flags
    fin.seekg(0); // move pointer to the beginning of the file so we can read again
    start = high_resolution_clock::now();

    while (fin >> code) {
        s.insert(code);
    }

    end = high_resolution_clock::now();
    auto s_duration = duration_cast<nanoseconds>(end - start);

    displayTimes("Read", v_duration, l_duration, s_duration);
}

// timeSorting() sorts the ADTs and times it
// parameters: vector<string>& v - the vector to sort
//             list<string>& l - the list to sort
//             set<string>& s - the set to sort
// returns: void
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

// timeInserting() inserts "TESTCODE" into the middle of the ADTs and times it
// parameters: vector<string>& v - the vector to insert into
//             list<string>& l - the list to insert into
//             set<string>& s - the set to insert into
// returns: void
void timeInserting(vector<string>& v, list<string>& l, set<string>& s) {
    // VECTOR TESTING
    auto start = high_resolution_clock::now();

    v.insert(v.begin() + v.size() / 2, "TESTCODE");

    auto end = high_resolution_clock::now();
    auto v_duration = duration_cast<nanoseconds>(end - start);

    // LIST TESTING
    start = high_resolution_clock::now();

    auto it = l.begin();
    advance(it, l.size() / 2);
    l.insert(it, "TESTCODE");

    end = high_resolution_clock::now();
    auto l_duration = duration_cast<nanoseconds>(end - start);

    // SET TESTING
    start = high_resolution_clock::now();

    s.insert("TESTCODE");

    end = high_resolution_clock::now();
    auto s_duration = duration_cast<nanoseconds>(end - start);

    displayTimes("Insert", v_duration, l_duration, s_duration);
}

// timeDeleting() deletes a code from the middle of the ADTs and times it
// parameters: vector<string>& v - the vector to delete from
//             list<string>& l - the list to delete from
//             set<string>& s - the set to delete from
// returns: void
void timeDeleting(vector<string>& v, list<string>& l, set<string>& s) {
    // VECTOR TESTING
    auto start = high_resolution_clock::now();

    v.erase(v.begin() + v.size() / 2);

    auto end = high_resolution_clock::now();
    auto v_duration = duration_cast<nanoseconds>(end - start);

    // LIST TESTING
    start = high_resolution_clock::now();

    auto l_it = l.begin();
    advance(l_it, l.size() / 2);
    l.erase(l_it);

    end = high_resolution_clock::now();
    auto l_duration = duration_cast<nanoseconds>(end - start);

    // SET TESTING
    start = high_resolution_clock::now();

    auto s_it = s.begin(); // Of course it doesn't really make sense to delete from position n of a set
    advance(s_it, s.size() / 2); // But we do so with an iterator in the spirit of the race
    s.erase(s_it);

    end = high_resolution_clock::now();
    auto s_duration = duration_cast<nanoseconds>(end - start);

    displayTimes("Delete", v_duration, l_duration, s_duration);
}