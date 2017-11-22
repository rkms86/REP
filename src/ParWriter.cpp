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

#include "ParWriter.h"

#include "StringUtils.h"

#include <ctype.h>

ParWriter::ParWriter(string filename,float in_apix)
  : ParamsWriter(filename)
{
	apix = in_apix;
}

ParWriter::~ParWriter()
{
	
}

void ParWriter::writeCurrentData() {
  
	if( (current_data.size()>0) && (current_data.size()==16) ) {
	  
		char tmp[20];

		ImgIdx = atof( current_data[0].c_str() );
		AngPsi = atof( current_data[1].c_str() );
		AngTlt = atof( current_data[2].c_str() );
		AngRot = atof( current_data[3].c_str() );
		ShiftX = atof( current_data[4].c_str() );
		ShiftY = atof( current_data[5].c_str() );

		sprintf(tmp,"%7d",ImgIdx);
		current_data[0] = tmp;
	  
		sprintf(tmp,"%8.2f",AngPsi);
		current_data[1] = tmp;
		
		sprintf(tmp,"%8.2f",AngTlt);
		current_data[2] = tmp;

		sprintf(tmp,"%8.2f",AngRot);
		current_data[3] = tmp;

		sprintf(tmp,"%10.2f",pix_to_angs(ShiftX));
		current_data[4] = tmp;

		sprintf(tmp,"%10.2f",pix_to_angs(ShiftY));
		current_data[5] = tmp;
		
		sprintf(tmp,"%8s",current_data[6].c_str());
		current_data[6] = tmp;
		
		sprintf(tmp,"%6s",current_data[7].c_str());
		current_data[7] = tmp;
		
		sprintf(tmp,"%9s",current_data[8].c_str());
		current_data[8] = tmp;
		
		sprintf(tmp,"%9s",current_data[9].c_str());
		current_data[9] = tmp;
		
		sprintf(tmp,"%8s",current_data[10].c_str());
		current_data[10] = tmp;
		
		sprintf(tmp,"%7s",current_data[11].c_str());
		current_data[11] = tmp;
		
		sprintf(tmp,"%11s",current_data[12].c_str());
		current_data[12] = tmp;
		
		sprintf(tmp,"%11s",current_data[13].c_str());
		current_data[13] = tmp;
		
		sprintf(tmp,"%8s",current_data[14].c_str());
		current_data[14] = tmp;
		
		sprintf(tmp,"%8s",current_data[15].c_str());
		current_data[15] = tmp;
		
		for( unsigned ix = 0; ix < current_data.size(); ix++ ) {
			//if(ix>5)
			//	output_file << "\t";
			output_file << current_data[ix];
		}
		output_file << "\n";
	}
  
}

float ParWriter::pix_to_angs(float pixs) {
  
	return -1.0f*pixs*apix;
  
}

