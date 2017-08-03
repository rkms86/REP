#ifndef PARAMSREADER_H
#define PARAMSREADER_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class ParamsReader {

public:
	ParamsReader(string filename);
	ParamsReader(const char*filename);
	~ParamsReader();

	bool isValid();
	
	virtual bool isDescriptor();

	virtual bool dataAvailable() = 0;
	virtual void readStart() = 0;
	virtual void readNext() = 0;

public:

	string	ImgNam;
	int		ImgIdx;
	float	AngRot;
	float	AngTlt;
	float	AngPsi;
	float	ShiftX;
	float	ShiftY;

	string			line_buffer;
	vector<string>	current_data;

protected:

	ifstream	input_file;

};


#endif

