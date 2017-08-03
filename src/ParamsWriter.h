#ifndef PARAMSWRITER_H
#define PARAMSWRITER_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class ParamsWriter {

public:
	ParamsWriter(string filename);
	ParamsWriter(const char*filename);
	~ParamsWriter();

	bool isValid();

	virtual void write(string&data);

	virtual void writeCurrentData() = 0;

	void setData(vector<string>&in_data);

public:

	string	ImgNam;
	int		ImgIdx;
	float	AngRot;
	float	AngTlt;
	float	AngPsi;
	float	ShiftX;
	float	ShiftY;
	
	vector<string>	current_data;

protected:

	ofstream	output_file;

};


#endif

