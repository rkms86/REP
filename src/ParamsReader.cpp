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

#include "ParamsReader.h"

#include "StringUtils.h"

ParamsReader::ParamsReader(string filename)
{
	input_file.open(filename.c_str());
	
	if( !input_file.is_open() ) {
		cerr << "File cannot be opened: " << filename << "\n";
		exit(-1);
	}
}

ParamsReader::ParamsReader(const char*filename)
{
	input_file.open(filename);
	
	if( !input_file.is_open() ) {
		cerr << "File cannot be opened: " << filename << "\n";
		exit(-1);
	}
}

ParamsReader::~ParamsReader()
{
	input_file.close();
}

bool ParamsReader::isValid() {
	return input_file.good();
}

bool ParamsReader::isDescriptor() {
	return true;
}

