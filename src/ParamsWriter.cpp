#include "ParamsWriter.h"

#include "StringUtils.h"

ParamsWriter::ParamsWriter(string filename)
{
	output_file.open(filename.c_str());
}

ParamsWriter::ParamsWriter(const char*filename)
{
	output_file.open(filename);
}

ParamsWriter::~ParamsWriter()
{
	output_file.close();
}

void ParamsWriter::setData(vector<string>&in_data) {
	if( current_data.size() > 0 )
		current_data.clear();
	for( unsigned ix = 0; ix < in_data.size(); ix++ ) {
		current_data.push_back( in_data[ix] );
	}
}

bool ParamsWriter::isValid() {
	return output_file.good();
}

void ParamsWriter::write(string&data) {
  
	if( (data.length()>0) && output_file.good() ) {
	  
		output_file << data << "\n";
	}
  
}

