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

#include "StarReader.h"

#include "StringUtils.h"

#include <ctype.h>

StarReader::StarReader(string filename)
  : ParamsReader(filename)
{
	if( !load_header() ) {
		exit(-1);
	}
}

StarReader::~StarReader()
{
	delete header;
}

bool StarReader::load_header() {
  
	if( input_file.is_open() )
		header = new StarHdr(input_file);
	
	if( !header->isValid() ) {
		cerr << "Error loading STAR file header.\n";
		exit(-1);
	}

	iMrcFil = header->getTagIndex(string("ImageName"));
	iShiftX = header->getTagIndex(string("OriginX"));
	iShiftY = header->getTagIndex(string("OriginY"));
	iAngRot = header->getTagIndex(string("AngleRot"));
	iAngTlt = header->getTagIndex(string("AngleTilt"));
	iAngPsi = header->getTagIndex(string("AnglePsi"));

	bool result = true;

	if( iMrcFil < 0 ) {
		cerr << "ImageName field could not be found on input STAR file.\n";
		result = false;
	}

	if( iShiftX < 0 ) {
		cerr << "OriginX field could not be found on input STAR file.\n";
		result = false;
	}

	if( iShiftY < 0 ) {
		cerr << "OriginY field could not be found on input STAR file.\n";
		result = false;
	}

	if( iAngRot < 0 ) {
		cerr << "AngleRot field could not be found on input STAR file.\n";
		result = false;
	}

	if( iAngTlt < 0 ) {
		cerr << "AngleTilt field could not be found on input STAR file.\n";
		result = false;
	}

	if( iAngPsi < 0 ) {
		cerr << "AnglePsi field could not be found on input STAR file.\n";
		result = false;
	}
	
	return result;
  
}

bool StarReader::isValid() {
	return ( input_file.good() && header->isValid() );
}

bool StarReader::dataAvailable() {
	return ( input_file.good() && current_data.size()>0 );
}

void StarReader::readStart() {
	input_file.clear();
	input_file.seekg(header->dataStartPos);
	readNext();
}

void StarReader::readNext() {
	getline(input_file, line_buffer);
	current_data = split_string(line_buffer);
	
	if( current_data.size() > 0 ) {

		AngRot = atof( current_data[iAngRot].c_str() );
		AngTlt = atof( current_data[iAngTlt].c_str() );
		AngPsi = atof( current_data[iAngPsi].c_str() );
		ShiftX = atof( current_data[iShiftX].c_str() );
		ShiftY = atof( current_data[iShiftY].c_str() );

		ImgIdx = 1;
		ImgNam = current_data[iMrcFil];
		
		int at_ix = -1;
		int i;
		
		for(i=0;i<ImgNam.length();i++) {
			if( !isdigit(ImgNam[i]) ) {
				at_ix = i;
				break;
			}
		}
		
		if( ImgNam[at_ix] == '@' ) {
			ImgIdx = atoi( ImgNam.substr(0,at_ix).c_str() );
			ImgNam = ImgNam.substr(at_ix+1,ImgNam.length());
		}
	}
}



