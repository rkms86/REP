/***************************************************************************
*
* Authors: Ricardo Miguel Sanchez Loayza (risanche@biophys.mpg.de)
*
* Dr. Kudryashev/Sofja Kovalevskaja Group,
* Structural Biology - Max Planck Institute for Biophysics
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
* 02111-1307  USA
*
***************************************************************************/

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

