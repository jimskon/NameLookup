/***************************************************************************                   
 * namelookup.cpp  -  Program to display name statistics                                       
 *                                                                                             
 * copyright : (C) 2017 by Jim Skon                                                            
 *                                                                            
 * This program create an index US Census name                                       
 * Data on the frequency of names in response to requestes.                           
 * It then allows you to look up any name, giving the 10 closest matches               
 *                                                            
 *     
 *
 ***************************************************************************/
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include "NameMap.h"
#include "NameEntry.h"
#include <string>

// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#define XML_USE_STL

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

// Files with the name data
const string path = "/home/skon/NameLookup/namedata/";
const string lastFile = path+"dist.all.last";
const string maleFile = path+"dist.male.first";
const string femaleFile = path+"dist.female.first";

int main() {
  // Object used for receiving AJAX call (and getting parameters)
  Cgicc cgi;    // Ajax object

  // Build the name maps
  NameMap lastMap(lastFile);
  NameMap femaleMap(femaleFile);
  NameMap maleMap(maleFile);
  if (!lastMap.NameMapSuccess() || !femaleMap.NameMapSuccess()|| !maleMap.NameMapSuccess()) {
      /* send back the results */
      cout << "Content-Type: text/plain\n\n";
      cout << "File open failure!" << endl;
      return 0;
    }
  vector<NameEntry> matchList; // place to stare the matches
  
  // Create AJAX objects to receive information from web page.
  form_iterator itts = cgi.getElement("type_select");
  form_iterator itname = cgi.getElement("name");

  // Retrieve the actual paramaters
  string type = **itts;
  string name = **itname;
  
  /* Convert name to upper case*/
  transform(name.begin(), name.end(), name.begin(), ::toupper);

  // Lookup the name in the appropriate name map
  if (type.compare("Last")==0) {
    matchList = lastMap.getMatches(name);
  } else if (type.compare("Female")==0){
    matchList = femaleMap.getMatches(name);
  } else if (type.compare("Male")==0){
    matchList = maleMap.getMatches(name);
  }
  
  /* send back the results */
  cout << "Content-Type: text/plain\n\n";

  /* Results are comma delimited (name, percent, rank, name, ...) for up to 10 names */
  for (int i = 0; i < matchList.size(); i++) {
    cout << matchList.at(i).name << "," <<  matchList.at(i).percent << "," << matchList.at(i).rank;
    if (i<matchList.size()-1)
      cout << ","; // Only put out this comma if not last entry.
  }
  
return 0;
}

