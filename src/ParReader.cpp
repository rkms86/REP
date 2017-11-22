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

#include "ParReader.h"

#include "StringUtils.h"

#include <ctype.h>

ParReader::ParReader(string filename, string mrc, float in_apix)
  : ParamsReader(filename)
{
	mrc_file = mrc;
	apix = in_apix;
	is_descriptor = false;
}

ParReader::~ParReader()
{
	
}

bool ParReader::dataAvailable() {
	return ( !input_file.eof() );
}

void ParReader::readStart() {
	input_file.clear();
	input_file.seekg(0);
	readNext();
}

void ParReader::readNext() {
	
	getline(input_file, line_buffer);
	
	if( line_buffer[0] == 'C' ) {
		is_descriptor = false;
	}
	else {
		is_descriptor = true;
		
		current_data = split_string(line_buffer);
		
		if( current_data.size() > 0 ) {

			ImgIdx = atof( current_data[0].c_str() );
			AngPsi = atof( current_data[1].c_str() );
			AngTlt = atof( current_data[2].c_str() );
			AngRot = atof( current_data[3].c_str() );
			ShiftX = atof( current_data[4].c_str() );
			ShiftY = atof( current_data[5].c_str() );
			ImgNam = mrc_file;
			
			ShiftX = angs_to_pix(ShiftX);
			ShiftY = angs_to_pix(ShiftY);
		}
	}
}

float ParReader::angs_to_pix(float angs) {
  
	return -1.0f*angs/apix;
  
}

bool ParReader::isDescriptor() {
	
	return is_descriptor;
}

