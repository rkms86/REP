#ifndef PARREADER_H
#define PARREADER_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ParamsReader.h"

using namespace std;

class ParReader : public ParamsReader {

public:
	ParReader(string filename, string mrc, float in_apix);
	~ParReader();

	bool isDescriptor();
	bool dataAvailable();
	void readStart();
	void readNext();

protected:
	int iMrcFil;
	int iShiftX;
	int iShiftY;
	int iAngRot;
	int iAngTlt;
	int iAngPsi;
	
	float	apix;
	string	mrc_file;
	
protected:
	float angs_to_pix(float angs);
	
	bool is_descriptor;
};


#endif

