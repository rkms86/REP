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

