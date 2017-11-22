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

