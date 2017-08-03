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


