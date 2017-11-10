#include <iostream>
#include <string>
#include <map>

// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#define XML_USE_STL

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

/* Name data structure */
struct name_record
{
  string name;         // Last name
  string percent;      // Frequency of occurance of a given name
  string cumulative;   // Cumulative freqency of all name up to and including this name
  string rank;         // Rank of this Name in terms of frequency
};

void lookupnames(string name, string type);
int createnamemap(std::map<string,name_record> &name_map ,string filename);
string StringToUpper(string myString);

string lastNameFile = "dist.all.last";
string femaleNameFile = "dist.female.first";
string maleNameFile = "dist.male.first";
string dir = "/home/class/SoftDev/namedata/";

int main() {
  Cgicc cgi;    // Ajax object
  char *cstr;
  
  // Create AJAX objects to recieve information from web page.
  form_iterator ts = cgi.getElement("type_select");
  form_iterator name = cgi.getElement("name");

  string type = **ts;
  string stname = **name;
  stname = StringToUpper(stname);
  
  /* send back the results */
  cout << "Content-Type: text/plain\n\n";

  lookupnames(stname, type);
  
return 0;
}

/*
 * Read the US Census data file "dist.all.last" and load it into an
 * in memory b+tree with name as the key.
 *
 * Return 1 if success, 0 if fail
 */
int createnamemap(std::map<string,name_record> &name_map ,string filename) {
  string filepath = dir + filename;
  name_record namedata;
  fstream infile(filepath.c_str());
  if (infile.good()) {
    while (1)
      {
	infile >> namedata.name;
	infile >> namedata.percent;
	infile >> namedata.cumulative;
	infile >> namedata.rank;
	if (infile.fail()) break;
	name_map[namedata.name] = namedata;
	//cout << namedata.name + " " <<  namedata.percent << " "
	// << namedata.cumulative << " " << namedata.rank << endl;
      }
    infile.close();
    return(1);
  } else {
    return(0);
  }
}


void lookupnames(string name, string type) {

  std::map<string,name_record> name_map;
  std::map<string,name_record>::iterator it;
  name_record result;
  string percent, rank;

  /* Get a message from a client */
  if (type == "Last") {
    //Get the closest match
    createnamemap(name_map ,lastNameFile);

  } else if (type == "Male") {
    //Get the closest match
    createnamemap(name_map , maleNameFile);

  } else if (type == "Female") {
    //Get the closest match
    createnamemap(name_map , femaleNameFile);

  }
  it = name_map.lower_bound (name);

  // back up 5 places
  for (int i=0 ; i<5 && (it!=name_map.begin()); i++) {
    it--;
  }

  string outMessage = "";
  // Get 10 results
  for (int i=0 ; i<10 && (it!=name_map.end()); i++) {
    result = (*it).second;
    name = result.name;
    percent = result.percent;
    rank = result.rank;
    if (i!=0) outMessage+=",";
    outMessage += name + "," + percent + "," + rank;
    it++;
    
  }

  cout <<  outMessage << endl;

  }

// Convert string to upper case
string StringToUpper(string myString)
{
  const int length = myString.length();
  for(int i=0; i!=length ; ++i)
    {
      myString[i] = toupper(myString[i]);
    }
  return myString;
}

