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

