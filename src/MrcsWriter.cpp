#include "MrcsWriter.h"

#include <cmath>
#include <iostream>

void normalize(float*data,int len, float des_mean, float des_std, float dyn_range, bool invert) {

	float acc = 0;
	float sq_acc = 0;

	des_std = abs(des_std);
	dyn_range = abs(dyn_range);
	if( invert ) des_std = -des_std;

	for( int i=0; i<len; i++ ) {
		acc += data[i];
	}

	float mean = acc/len;

	for( int i=0; i<len; i++ ) {
		sq_acc += (data[i]-mean)*(data[i]-mean);
	}

	float std = sqrt( (sq_acc)/len );

	for( int i=0; i<len; i++ ) {
		data[i] = des_std*(data[i]-mean)/std;
		if( data[i] < -dyn_range ) data[i] = -dyn_range;
		if( data[i] >  dyn_range ) data[i] =  dyn_range;
		data[i] = data[i] + des_mean;
	}
}

void get_min_max_mean(float*data,int len,float&frame_min,float&frame_max,float&frame_mean) {
	
	frame_min = data[0];
	frame_max = data[0];
	frame_mean= 0;

	for( int i=0; i<len; i++ ) {
		if( data[i] < frame_min ) 
			frame_min = data[i];
		if( data[i] > frame_max ) 
			frame_max = data[i];
		frame_mean += data[i];
	}
	frame_mean = frame_mean / len;
}

void save_frame(ofstream&out_file,float*data,int len) {
	out_file.write((char*)(data),len*sizeof(float));
}

MrcsWriter::MrcsWriter(string filename, int in_l) {

	out_file.open(filename.c_str());
	w = in_l;	
	h = in_l;
	count = 0;

	do_normalize = true;
	normalize_mean = 0.0f;
	normalize_std = 1.0f;
	normalize_range = 3.55f;
	normalize_invert = false;

	header.write(out_file);
	out_file.seekp(1024);

	buffer_float = new float[w*h];
}

MrcsWriter::~MrcsWriter() {

	updateHeader();
	out_file.close();

	if( buffer_float != NULL )
		delete [] buffer_float;
}

void MrcsWriter::writeCurrentFrame() {

	float frame_min, frame_max, frame_mean;

	if( do_normalize )
		normalize( buffer_float, w*h, normalize_mean, normalize_std, normalize_range, normalize_invert );

	get_min_max_mean( buffer_float, w*h, frame_min, frame_max, frame_mean );
	save_frame( out_file, buffer_float, w*h );
	
	if( count > 0 ) {
		if( frame_min < curr_min )
			curr_min = frame_min;
		if( frame_max > curr_max )
			curr_max = frame_max;
		curr_mean += frame_mean;
	}
	else {
		curr_min = frame_min;
		curr_max = frame_min;
		curr_mean = frame_mean;
	}

	count++;
	//cout << count << " " << curr_min << " " << curr_max << " " << curr_mean << "\n";
}

void MrcsWriter::updateHeader() {
	header.setNX(w);
	header.setNY(h);
	header.setNZ(count);
	header.setMODE(2);
	header.setAMIN(curr_min);
	header.setAMAX(curr_max);
	header.setAMEAN(curr_mean/count);
	header.write(out_file);
}





