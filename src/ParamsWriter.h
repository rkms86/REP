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

