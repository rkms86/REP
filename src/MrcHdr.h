#ifndef MRCHDR_H
#define MRCHDR_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <stdint.h>

using namespace std;

class MrcHdr {

public:
	MrcHdr();
	MrcHdr(u_int8_t*raw_header);
	MrcHdr(ifstream&in_file);

	void read(ifstream&in_file);
	void write(ofstream&out_file);

	int getNX();
	int getNY();
	int getNZ();
	int getMODE();
	float getAMIN();
	float getAMAX();
	float getAMEAN();

	void setNX(int val);
	void setNY(int val);
	void setNZ(int val);
	void setMODE(int val);
	void setAMIN(float val);
	void setAMAX(float val);
	void setAMEAN(float val);
	
	void addLABEL(string lbl);
	void addLABEL(char*lbl);

public:
	typedef union {
		u_int8_t raw[1024];
		struct {
			int		nx;
			int		ny;
			int		nz;
			int		mode;
			int		nxstart;
			int		nystart;
			int		nzstart;
			int		mx;
			int		my;
			int		mz;
			float	xlen;
			float	ylen;
			float	zlen;
			float	alpha;
			float	beta;
			float	gamma;
			int		mapc;
			int		mapr;
			int		maps;
			float	amin;
			float	amax;
			float	amean;
			int		ispg;
			int		next;
			// 0x60
			u_int8_t	skip1[100];
			// 0xC4
			float	xorg;
			float	yorg;
			float	zorg;
			char	cmap[4];
			char	stamp0;
			char	stamp1;
			char	stamp2;
			char	stamp3;
			float	rms;
			// 0x220
			int		nlabl;
			char	labels[10][80];
			// 0x400
		} data;
	} mrc_hdr_t;

	mrc_hdr_t	internal_header;
};

#endif

