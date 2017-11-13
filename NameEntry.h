
#ifndef NAMEENTRY_H
#define NAMEENTRY_H
#include <string>

using namespace std;

class NameEntry {
public:
    NameEntry();
    string name; // Last name
    string percent; // Frequency of occurrence of a given name
    string cumulative; // cumulative frequency of all name up to and including this name
    string rank; // Rank of this Name in terms of frequency
private:

};

#endif /* NAMEENTRY_H */

