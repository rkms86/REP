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

