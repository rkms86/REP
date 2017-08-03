#ifndef PARWRITER_H
#define PARWRITER_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ParamsWriter.h"

using namespace std;

class ParWriter : public ParamsWriter {

public:
	ParWriter(string filename,float in_apix);
	~ParWriter();

	void writeCurrentData();

public:
	

protected:
	float apix;
	
protected:
	float pix_to_angs(float pixs);
};


#endif

