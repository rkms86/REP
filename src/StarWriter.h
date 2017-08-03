#ifndef STARWRITER_H
#define STARWRITER_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ParamsWriter.h"
#include "StarHdr.h"

using namespace std;

class StarWriter : public ParamsWriter {

public:
	StarWriter(string filename,StarHdr*header);
	~StarWriter();

	void writeCurrentData();

public:

protected:
	int iMrcFil;
	int iShiftX;
	int iShiftY;
	int iAngRot;
	int iAngTlt;
	int iAngPsi;
	
	int num_labels;
	
protected:
	bool save_header(StarHdr*header);
};


#endif

