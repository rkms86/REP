#ifndef STARHDR_H
#define STARHDR_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class StarHdr {

public:
	StarHdr(ifstream&in_file);
	StarHdr(vector<string>&in_list_fields);

	void read(ifstream&in_file);
	void write(ofstream&out_file);

	bool isValid();	

	int getTagIndex(string tag_name);
public:
	vector<string>	listFields;
	streampos	dataStartPos;
};

#endif

