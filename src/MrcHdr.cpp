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

#include "MrcHdr.h"

MrcHdr::MrcHdr() {
	memset(internal_header.raw,0,1024);
	internal_header.data.mapc = 1;
	internal_header.data.mapr = 2;
	internal_header.data.maps = 3;
}

MrcHdr::MrcHdr(u_int8_t*raw_header) {
	memcpy(internal_header.raw,raw_header,1024);
}

MrcHdr::MrcHdr(ifstream&in_file) {
	read(in_file);
}

void MrcHdr::read(ifstream&in_file) {
	if( in_file.is_open() && in_file.good() ) {
		streampos current_pos = in_file.tellg();
		in_file.seekg(0);
		in_file.read((char*)(internal_header.raw),1024);
		in_file.seekg(current_pos);
	}
}

void MrcHdr::write(ofstream&out_file) {
	if( out_file.is_open() && out_file.good() ) {
		streampos current_pos = out_file.tellp();
		out_file.seekp(0);
		out_file.write((char*)(internal_header.raw),1024);
		out_file.seekp(current_pos);
	}
}

int MrcHdr::getNX() {
	return internal_header.data.nx;
}

int MrcHdr::getNY() {
	return internal_header.data.ny;
}

int MrcHdr::getNZ() {
	return internal_header.data.nz;
}

int MrcHdr::getMODE() {
	return internal_header.data.mode;
}

float MrcHdr::getAMIN() {
	return internal_header.data.amin;
}

float MrcHdr::getAMAX() {
	return internal_header.data.amax;
}

float MrcHdr::getAMEAN() {
	return internal_header.data.amean;
}

void MrcHdr::setNX(int val) {
	internal_header.data.nx = val;
}

void MrcHdr::setNY(int val) {
	internal_header.data.ny = val;
}

void MrcHdr::setNZ(int val) {
	internal_header.data.nz = val;
}

void MrcHdr::setMODE(int val) {
	internal_header.data.mode = val;
}

void MrcHdr::setAMIN(float val) {
	internal_header.data.amin = val;
}

void MrcHdr::setAMAX(float val) {
	internal_header.data.amax = val;
}

void MrcHdr::setAMEAN(float val) {
	internal_header.data.amean = val;
}

void MrcHdr::addLABEL(string lbl) {
	addLABEL(lbl.c_str());
}

void MrcHdr::addLABEL(char*lbl) {
	if( internal_header.data.nlabl < 10 ) {
		strncpy(internal_header.data.labels[internal_header.data.nlabl],lbl,80);
		internal_header.data.nlabl++;
	}
}



