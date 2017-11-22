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

#include "StarWriter.h"

#include "StringUtils.h"

#include <ctype.h>

StarWriter::StarWriter(string filename,StarHdr*header)
  : ParamsWriter(filename)
{
	if( !save_header(header) ) {
		exit(-1);
	}
}

StarWriter::~StarWriter()
{
	
}

bool StarWriter::save_header(StarHdr*header) {
  
	
	if( !header->isValid() ) {
		cerr << "Error loading STAR file header.\n";
		exit(-1);
	}
	
	if( output_file.is_open() )
		header->write(output_file);

	iMrcFil = header->getTagIndex(string("ImageName"));
	iShiftX = header->getTagIndex(string("OriginX"));
	iShiftY = header->getTagIndex(string("OriginY"));
	iAngRot = header->getTagIndex(string("AngleRot"));
	iAngTlt = header->getTagIndex(string("AngleTilt"));
	iAngPsi = header->getTagIndex(string("AnglePsi"));

	num_labels = header->listFields.size();

	bool result = true;

	if( iMrcFil < 0 ) {
		cerr << "ImageName field could not be found on output STAR file.\n";
		result = false;
	}

	if( iShiftX < 0 ) {
		cerr << "OriginX field could not be found on output STAR file.\n";
		result = false;
	}

	if( iShiftY < 0 ) {
		cerr << "OriginY field could not be found on output STAR file.\n";
		result = false;
	}

	if( iAngRot < 0 ) {
		cerr << "AngleRot field could not be found on output STAR file.\n";
		result = false;
	}

	if( iAngTlt < 0 ) {
		cerr << "AngleTilt field could not be found on output STAR file.\n";
		result = false;
	}

	if( iAngPsi < 0 ) {
		cerr << "AnglePsi field could not be found on output STAR file.\n";
		result = false;
	}
	
	return result;
  
}

void StarWriter::writeCurrentData() {
  
	if( (current_data.size()>0) && (current_data.size()==num_labels) ) {
	  
		char tmp[ImgNam.length()+20];

		sprintf(tmp,"%13.6f",ShiftX);
		current_data[iShiftX] = tmp;

		sprintf(tmp,"%13.6f",ShiftY);
		current_data[iShiftY] = tmp;

		sprintf(tmp,"%13.6f",AngRot);
		current_data[iAngRot] = tmp;

		sprintf(tmp,"%13.6f",AngTlt);
		current_data[iAngTlt] = tmp;

		sprintf(tmp,"%13.6f",AngPsi);
		current_data[iAngPsi] = tmp;

		sprintf(tmp,"%06d@%s",ImgIdx,ImgNam.c_str());
		current_data[iMrcFil] = tmp;
	  
		for( unsigned ix = 0; ix < current_data.size(); ix++ ) {
			if(ix>0)
				output_file << "\t";
			output_file << current_data[ix];
		}
		output_file << "\n";
	}
  
}
