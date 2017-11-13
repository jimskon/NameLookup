
#ifndef NAMEMAP_H
#define NAMEMAP_H
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
#include "NameEntry.h"

using namespace std;

class NameMap {
public:
    NameMap(string filename);
    bool NameMapSuccess();
    vector<NameEntry> getMatches(string name);

private:
    map<string, NameEntry> nameMap;
    
    bool success;
};

#endif /* NAMEMAP_H */

