#ifndef MRCSREADER_H
#define MRCSREADER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include <stdint.h>

#include "MrcHdr.h"

using namespace std;

class MrcsReader {

public:
	MrcsReader();
	~MrcsReader();

	bool readFrame(string filename, string dirname, int frame_ix);

	void getRegion(int x, int y, int side_w, int side_h, float*out);
public:
	string 		current_mrc_file;
	MrcHdr		*header;
	ifstream	in_file;
	float		*data_float;
	int			w;
	int			h;
	int			d;
	int			count;

protected:
	void openMRCS(string filename, string dirname);
};

#endif

