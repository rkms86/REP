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

#include "StringUtils.h"

#include <sstream>
#include <iostream>

#include <string>
#include <cmath>

#include <unistd.h>
#include <linux/limits.h>

#include <cctype>

using namespace std;

vector<string> split_string(string&input_line) {

	stringstream ss(input_line);
	vector<string> rslt;
	string word;

	while (ss >> word)
        	rslt.push_back(word);

	return rslt;
}

string get_first_word(string&input_line) {
	stringstream ss(input_line);
	string word;
	ss >> word;
	return word;
}

string to_lower(string&str) {
	string rslt = str;
	
	int i;
	for(i=0;i<rslt.length();i++)
		rslt[i] = tolower(rslt[i]);
	
	return rslt;
}

string get_file_fullpath(string&file_name) {
	
	string result;
  
	if( access(file_name.c_str(), F_OK) == 0 ) {
		char actualpath[PATH_MAX];
	
		result = realpath(file_name.c_str(), actualpath);
		
		string::size_type ix = result.rfind('/', result.length());
		
		if (ix != string::npos) {
			result.erase(result.begin()+ix+1,result.end());
		}
	}
	return result;
}

string get_file_path(string&file_name) {
	
	string result;
  
	string::size_type ix = file_name.rfind('/', file_name.length());
	
	if (ix != string::npos) {
		result = file_name;
		result.erase(result.begin()+ix+1,result.end());
	}
	return result;
}

bool check_file_ext(string file_name, string ext) {
  
  
	bool result = false;
  
	if( file_name.length() > ext.length() ) {

		string file_ext = file_name.substr( file_name.length()-ext.length(), file_name.length());
		file_ext = to_lower(file_ext);
		string local_ext = to_lower(ext);
		if( file_ext.compare(local_ext) == 0 )
			result = true;
	
	}

	return result;
}

string set_file_ext(string file_name, string ext) {

	string rslt = file_name;

	if( !check_file_ext(rslt,ext) ) {
	  
		if( ext[0] != '.' ) {
			rslt = rslt + ".";
		}
		rslt = rslt + ext;	  
	}
	
	
	return rslt;
}

string swap_file_ext(string file_name, string ext_old, string ext_new) {

	string rslt = file_name;
	
	if( check_file_ext(rslt,ext_old) ) {
		rslt = rslt.substr(0,file_name.length()-ext_old.length());
		rslt = rslt + ext_new;
	}
	
	
	return rslt;
}


