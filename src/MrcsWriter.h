#ifndef MRCSWRITER_H
#define MRCSWRITER_H

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

class MrcsWriter {

public:
	MrcsWriter(string filename, int in_l);
	~MrcsWriter();

	void writeCurrentFrame();
	void updateHeader();
public:
	bool		do_normalize;
	float		normalize_mean;
	float		normalize_std;
	float		normalize_range;
	bool		normalize_invert;
	ofstream 	out_file;
	MrcHdr		header;
	float		*buffer_float;
	int		w;
	int		h;
	int		count;
	float		curr_min;
	float		curr_max;
	float		curr_mean;
};

#endif

