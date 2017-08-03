#include "MrcsReader.h"

#include <sys/stat.h>
#include <cmath>
#include <iostream>

MrcsReader::MrcsReader() {
	header = NULL;
	data_float = NULL;
	count = 0;
}

MrcsReader::~MrcsReader() {
	if( header != NULL )
		delete header;
	
	if( data_float != NULL )
		delete [] data_float;
}

bool MrcsReader::readFrame(string filename, string dirname, int frame_ix) {

	bool rslt = false;
	openMRCS(filename, dirname);

	if( frame_ix <= d ) {
		in_file.seekg(1024 + (w*h*(frame_ix-1))*sizeof(float),ios_base::beg);
		in_file.read((char*)(data_float),w*h*sizeof(float));
		count = frame_ix;
		rslt = true;
	}
	//else {
		//cout << "MrcsReader: " << filename << " : Trying to read frame " << frame_ix << " from " << d << " availables frames\n.";
		//exit(-1);
	//}
	in_file.clear();
	in_file.seekg(1024,ios_base::beg);		
	return rslt;
}

void MrcsReader::getRegion(int x, int y, int side_w, int side_h, float*out) {

	int i,j;
	int m = x - floor(((float)side_w)/2);
	int n = y - floor(((float)side_h)/2);
	int p,q;
	for( j=0; j<side_h; j++ ) {
		for( i=0; i<side_w; i++ ) {
			float out_val = 0;
			p = i+m;
			q = j+n;
			if( p >= 0 && q >= 0 ) {
				if( p < w && q < h ) {
					out_val = data_float[ p + q*w ];
				}
			}
			out[i+(j*side_w)] = out_val;
		}
	}

}

void MrcsReader::openMRCS(string filename, string dirname) {

	if( current_mrc_file != filename ) {

		if( in_file.is_open() )
			in_file.close();

		current_mrc_file = filename;

		struct stat buffer;
		
		if( stat (filename.c_str(),&buffer) == 0 ) {
			in_file.open(filename.c_str());
		}
		else {
			string full_filename = dirname + filename;
			if( stat (full_filename.c_str(),&buffer) == 0 ) {
				in_file.open(full_filename.c_str());
			}
			else {
				cout << "\nFile " << filename << " or " << full_filename << " couldn't be read.\n";
				exit(-1);
			}
		}

		if( header != NULL ) delete header;

		header = new MrcHdr(in_file);

		if( header->getMODE() != 2 ) {
			cout << filename << " : Only float MRCS supported (mode=2), current mode: " << header->getMODE() << "\n";
			exit(-1);
		}
			
		h = header->getNX();
		w = header->getNY();
		d = header->getNZ();
		count = 0;
		in_file.seekg(1024,ios_base::beg); /* Go to start of data */
		data_float = new float[ w*h ];
	}
}

