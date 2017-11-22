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

