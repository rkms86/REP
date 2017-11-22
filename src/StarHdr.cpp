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

#include "StarHdr.h"

#include <iostream>

#include "StringUtils.h"

/* Constructor */
StarHdr::StarHdr(ifstream&in_file) {
	read(in_file);
}

StarHdr::StarHdr(vector<string>&in_list_fields) {
	for( unsigned ix = 0; ix < in_list_fields.size(); ix++ ) {
		listFields.push_back( in_list_fields[ix] );
	}
}

/* Read/Write */
void StarHdr::read(ifstream&in_file) {

	if( listFields.size() > 0 )
		listFields.clear();

	string tmp_line;
	vector<string> tmp_words;

	/* Go to beginning of file */
	in_file.clear();
	in_file.seekg(0, ios::beg);

	/* Search for "data_" tag */
	while( getline( in_file, tmp_line ) ) {
		if( get_first_word(tmp_line) == "data_" )
			break;
	}
	
	/* Search for "loop_" tag */
	while( getline( in_file, tmp_line ) ) {
		if( get_first_word(tmp_line) == "loop_" )
			break;
	}

	/* Read fields: */
	dataStartPos = in_file.tellg();
	while( getline( in_file, tmp_line ) ) {
		vector<string> words = split_string(tmp_line);
		if( words.size() > 0 ) {
			if( words[0].at(0) == '_' ) {
				listFields.push_back( words[0] );
			}
			else {
				in_file.seekg(dataStartPos, ios::beg);
				break;
			}
		}
		dataStartPos = in_file.tellg();	
	}
}

/* Read/Write */
void StarHdr::write(ofstream&out_file) {
	if( listFields.size() ) {
		out_file.seekp(0);
		out_file << "\ndata_\n\nloop_\n";
		for( unsigned ix = 0; ix < listFields.size(); ix++ ) {
			out_file << listFields[ix] << " #" << (ix+1) << "\n";
		}
	}
	
	return;
}

/* Other */
bool StarHdr::isValid() {
	return (listFields.size()>0);
}

int StarHdr::getTagIndex(string tag_name) {
	int rslt = -1;
	for( unsigned ix = 0; ix < listFields.size(); ix++ ) {
		int l = listFields[ix].length();
		if( tag_name.compare(listFields[ix]) == 0 || 
                    listFields[ix].compare(4,l-4,tag_name) == 0 )
		{
			rslt = ix;
		}
	}
	return rslt;
}


