/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NameMap.cpp
 * Author: skonjp
 * 
 * Created on November 10, 2017, 11:42 PM
 */

#include "NameMap.h"

NameMap::NameMap(string filename) {

    NameEntry nameData;
    fstream infile(filename);
    if (infile.good()) {
        while (1) {
            infile >> nameData.name;
            infile >> nameData.percent;
            infile >> nameData.cumulative;
            infile >> nameData.rank;
            if (infile.fail()) break;
            nameMap[nameData.name] = nameData;
        }
        infile.close();
        success = true;
    } else {
        success = false;
    }
}

bool NameMap::NameMapSuccess() {
    return success;
}

vector<NameEntry> NameMap::getMatches(string name) {
    vector<NameEntry> matchList;
    NameEntry match;
    // Look up the closest lower match
    map<string, NameEntry>::iterator it = nameMap.lower_bound(name);

    // back up (up to) 5 places
    for (int i = 0; i < 5 && (it != nameMap.begin()); i++) {
        it--;
    }

    // Get (up to) 10 results
    for (int i = 0; i < 10 && (it != nameMap.end()); i++) {
        
        match = (*it).second;
        matchList.push_back(match);
        it++;
    }
    return matchList;;
}