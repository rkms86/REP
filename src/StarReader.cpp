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



