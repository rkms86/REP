#ifndef STARREADER_H
#define STARREADER_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ParamsReader.h"
#include "StarHdr.h"

using namespace std;

class StarReader : public ParamsReader {

public:
	StarReader(string filename);
	~StarReader();

	bool isValid();

	bool dataAvailable();
	void readStart();
	void readNext();

public:
	StarHdr	*header;

protected:
	int iMrcFil;
	int iShiftX;
	int iShiftY;
	int iAngRot;
	int iAngTlt;
	int iAngPsi;
	
protected:
	bool load_header();
};


#endif

