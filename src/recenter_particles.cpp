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

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

#include <stdio.h>
#include <time.h>

#include <getopt.h>

#include <linux/limits.h>

#include "StringUtils.h"

#include "ParamsReader.h"
#include "ParamsWriter.h"

#include "StarReader.h"
#include "StarWriter.h"

#include "ParReader.h"
#include "ParWriter.h"

#include "MrcHdr.h"
#include "MrcsReader.h"
#include "MrcsWriter.h"

#include "SymEngine.h"

class ArgsParser {
  
public:
	ArgsParser(int ac, char**av);
	static void print_usage(int ac, char**av);
	void print_args();
	void print_disclaimer();

public:
	string	input_desc_file;	// STAR or PAR filename
	string	input_desc_path;
	string	output_desc_file;
	string	output_mrcs_file;
	string	output_mrcs_path;
	int		crop_length;
	float	dx;
	float	dy;
	float	dz;
	string	sym_type;
	
	/// FREEALIGN PARAMS:
	bool	freealign;
	string	input_mrcs_file;
	float	apix;
	
};

void add_label(MrcsWriter&mrcs_writer,ArgsParser&args);
void calculate_offset(float&off_x, float&off_y, float ang_rot, float ang_tlt, float ang_psi, float dx, float dy, float dz);

using namespace std;

int main(int ac, char**av) {

	ArgsParser args(ac,av);
  
	args.print_disclaimer();
  
	args.print_args();
	
	ParamsReader *desc_reader = NULL;
	ParamsWriter *desc_writer = NULL;
	
	if( args.freealign )
		desc_reader = new ParReader( args.input_desc_file, args.input_mrcs_file, args.apix );
	else
		desc_reader = new StarReader( args.input_desc_file );
	
	if( desc_reader->isValid() ) {
		
		if( args.freealign )
			desc_writer = new ParWriter( args.output_desc_file, args.apix );
		else 
			desc_writer = new StarWriter( args.output_desc_file, ((StarReader*)desc_reader)->header );
	
		SymEngine sym(args.sym_type, args.dx, args.dy, args.dz);
		
		MrcsReader mrcs_reader;
		MrcsWriter mrcs_writer(args.output_mrcs_path + args.output_mrcs_file, args.crop_length);
		mrcs_writer.do_normalize = false;
		add_label(mrcs_writer,args);

		int counter_read = 1;
		int counter_write = 1;

		for( desc_reader->readStart(); desc_reader->dataAvailable(); desc_reader->readNext() ) {
			
			if( desc_reader->isDescriptor() ) {
				
				if( mrcs_reader.readFrame( desc_reader->ImgNam, args.input_desc_path, desc_reader->ImgIdx) ) {
			 
					for( sym.start(); sym.should_continue(); sym.next() ) {

						float off_x, off_y;

						float ang_rot = desc_reader->AngRot;
						float ang_tlt = desc_reader->AngTlt;
						float ang_psi = desc_reader->AngPsi;

						sym.apply_sym(off_x,off_y,ang_rot,ang_tlt,ang_psi);

						off_x = (mrcs_reader.w/2) + off_x - desc_reader->ShiftX;
						off_y = (mrcs_reader.h/2) + off_y - desc_reader->ShiftY;

						mrcs_reader.getRegion( floor(off_x), floor(off_y), args.crop_length, args.crop_length, mrcs_writer.buffer_float);
						mrcs_writer.writeCurrentFrame();

						desc_writer->setData(desc_reader->current_data);

						string	ImgNam;
						int		ImgIdx;
						float	AngRot;
						float	AngTlt;
						float	AngPsi;
						float	ShiftX;
						float	ShiftY;

						desc_writer->ImgNam = args.output_mrcs_file;
						desc_writer->ImgIdx = counter_write;
						desc_writer->AngRot = ang_rot;
						desc_writer->AngTlt = ang_tlt;
						desc_writer->AngPsi = ang_psi;
						desc_writer->ShiftX = off_x-floor(off_x);
						desc_writer->ShiftY = off_y-floor(off_y);
						desc_writer->writeCurrentData();
					  
						counter_write++;
					}
					
					cout << "Processed " << counter_read << " particles.\r";
					counter_read++;
				  
				}
				
			}
			else {
				
				desc_writer->write( desc_reader->line_buffer );
				
			}
			
		}
		cout << "\nDone!\n";
	}
	
	
	if( desc_reader != NULL )
		delete desc_reader;
	if( desc_writer != NULL )
		delete desc_writer;

	return 0;
}


/** ArgsParser Implementation: **/
ArgsParser::ArgsParser(int ac, char**av) {

	/**************************************/
	/* Validate number of input arguments */
	if( ac < 2 ) {
		print_usage(ac,av);
		exit(-1);
	}

	/**********************/
	/* Set Default Values */
	crop_length = 0;
	dx = 0.0f;
	dy = 0.0f;
	dz = 0.0f;
	sym_type = "C1";	
	freealign = false;
	apix = 1.0f;

	/*************************/
	/* Parse input arguments */
	static struct option long_options[] =
	{
		{"in_desc"  ,required_argument, 0, 'i'},
		{"in_mrcs"  ,required_argument, 0, 'm'},
		{"in_apix"  ,required_argument, 0, 'a'},
		{"out_base" ,required_argument, 0, 'o'},
		{"out_mrcs" ,required_argument, 0, 'O'},
		{"crop_len" ,required_argument, 0, 'l'},
		{"delta_x"  ,required_argument, 0, 'x'},
		{"delta_y"  ,required_argument, 0, 'y'},
		{"delta_z"  ,required_argument, 0, 'z'},
		{"symmetry" ,required_argument, 0, 's'},
		{"help"     ,no_argument,       0, 'h'},
		{0, 0, 0, 0}
	};
	int c;
	string::size_type ix;

	while( (c=getopt_long(ac,av,"i:m:a:o:O:l:x:y:z:s:h",long_options,NULL)) > -1 ) {
		switch(c) {
		case 'i':
			input_desc_file = optarg;
			input_desc_path = get_file_path(input_desc_file);
			break;
		case 'm':
			input_mrcs_file = optarg;
			break;
		case 'a':
			apix = atof(optarg);
			break;
		case 'o':
			output_desc_file = optarg;
			break;
		case 'O':
			output_mrcs_file = optarg;
			output_mrcs_path = get_file_path(output_mrcs_file);
			if( (!check_file_ext(output_mrcs_file,".mrc")) && (!check_file_ext(output_mrcs_file,".mrcs") ) ) {
				output_mrcs_file = set_file_ext(output_mrcs_file,".mrcs");
			}
			output_mrcs_file = output_mrcs_file.substr(output_mrcs_path.length(),output_mrcs_file.length());
			break;
		case 'l':
			crop_length = atoi(optarg);
			break;
		case 'x':
			dx = atof(optarg);
			break;
		case 'y':
			dy = atof(optarg);
			break;
		case 'z':
			dz = atof(optarg);
			break;
		case 's':
			sym_type = optarg;
			break;
		case 'f':
			freealign = true;
			break;
		case 'h':
			print_usage(ac,av);
			exit(-1);
			break;
		default:
			print_usage(ac,av);
			exit(-1);
			break;
		}
	}

	/****************************/
	/* Validate input arguments */
	bool should_continue = true;

	if( input_desc_file.empty() ) {
		should_continue = false;
		cerr << "Input STAR/PAR file is required.\n";
	}

	if( output_desc_file.empty() ) {
		should_continue = false;
		cerr << "Output base name is required.\n";
	}

	if( crop_length < 1 ) {
		should_continue = false;
		cerr << "Invalid crop length. It must be an integer greater than 0.\n";
	}

	if( check_file_ext(input_desc_file,".star") ) {
		output_desc_file = set_file_ext(output_desc_file,".star");
		if( output_mrcs_file.empty() ) {
			output_mrcs_file = swap_file_ext(output_desc_file,".star",".mrcs");
			output_mrcs_path = get_file_path(output_mrcs_file);
			output_mrcs_file = output_mrcs_file.substr(output_mrcs_path.length(),output_mrcs_file.length());
		}
	}
	else
	if( check_file_ext(input_desc_file,".par") ) {
		if( apix > 0.0 ) {
			if( !input_mrcs_file.empty() ) {
				freealign = true;
				output_desc_file = set_file_ext(output_desc_file,".par");
				if( output_mrcs_file.empty() ) {
				  output_mrcs_file = swap_file_ext(output_desc_file,".par",".mrc");
				  output_mrcs_path = get_file_path(output_mrcs_file);
				  output_mrcs_file = output_mrcs_file.substr(output_mrcs_path.length(),output_mrcs_file.length());
				}
			}
			else {
				cerr << "Input MRC/MRCS file must be specified.\n";
				should_continue = false;
			}
		}
		else {
			cerr << "Invalid pixel size: " << apix << "\n";
			should_continue = false;
		}
	}
	else {
		cerr << "Invalid input file. Only STAR or PAR files are supported\n";
		should_continue = false;
	}

	if( !should_continue )
		exit(-1);
}

void ArgsParser::print_usage(int ac, char**av) {
	if( ac > 0 )
		printf("Usage: %s [OPTION]...\n",av[0]);
	else
		printf("Usage: recenter_particles [OPTION]...\n");

	printf("Create a new MRC/MRCS with cropped (and recentered) particles.\n");
	printf("OPTIONS:\n");
	printf(" -i, --in_desc     Input STAR (RELION) or PAR (FREEALIGN) file.\n");
	printf("                   Note: Output file will have the same format.\n");
	printf(" -o, --out_base    Base name for the output files. The following\n");
	printf("                   files will be created:\n");
	printf("                   STAR file as input (RELION): '.star' and '.mrcs'.\n");
	printf("                   PAR file as input (FREEALIGN): '.par' and '.mrc'.\n");
	printf(" -l, --crop_len    Desired size of the cropped particle (in pixels).\n");
	printf(" -x, --delta_x     New center of the particle, X coordinate.\n");
	printf(" -y, --delta_y     New center of the particle, Y coordinate.\n");
	printf(" -z, --delta_z     New center of the particle, Z coordinate.\n");
	printf("                   Note: the new center is measured in pixels\n");
	printf("                   from the center of the current box size and,\n");
	printf("                   it can be a real number (not only integers).\n");
	printf(" -s, --symmetry    Apply symmetry among particle's Z axis.\n");
	printf("                   Cyclic symmetry implemented. C1 by default.\n");
	printf("                   Partial Dihedral symmetry support.\n");
	printf(" -h, --help        Displays this help.\n");
	printf("\n");
	printf(" -m, --in_mrcs     [FREEALIGN ONLY] Input MRC/MRCS file.\n");
	printf(" -a, --in_apix     [FREEALIGN ONLY] Pixel size in Angstroms.\n");
	printf("\n");
	printf(" -O, --out_mrcs    (OPTIONAL) Sets the MRC/MRCS output filename.\n");
	
}

void ArgsParser::print_args() {
	if( freealign ) {
	printf("  Format:      FREEALIGN\n");
	printf("  Input PAR:   %s\n",input_desc_file.c_str());
	printf("  Input MRC:   %s\n",input_mrcs_file.c_str());
	printf("  Output PAR:  %s\n",output_desc_file.c_str());
	printf("  Output MRC:  %s\n",(output_mrcs_path+output_mrcs_file).c_str());
	printf("  Pixel size:  %.3f angstroms\n",apix);
	}
	else {
	printf("  Format:      RELION\n");
	printf("  Input STAR:  %s\n",input_desc_file.c_str());
	printf("  Output STAR: %s\n",output_desc_file.c_str());
	printf("  Output MRCS: %s\n",(output_mrcs_path+output_mrcs_file).c_str());
	}
	printf("  Crop length: %d pixels\n",crop_length);
	printf("  New center:  %4.2f,%4.2f,%4.2f (pixels)\n",dx,dy,dz);
	printf("  Symmetry:    %s\n",sym_type.c_str());
}

void ArgsParser::print_disclaimer() {

	printf("************************************************************************\n");
	printf("***************** ALPHA VERSION FOR INTERNAL TEST ONLY *****************\n");
	printf("******** Developed by Ricardo Sanchez (risanche@biophys.mpg.de) ********\n");
	printf("*****  Commissioned by Edoardo D'Imprima (eddimpri@biophys.mpg.de) *****\n");
	printf("************************************************************************\n");
	printf("\n");
	
}

void add_label(MrcsWriter&mrcs_writer,ArgsParser&args) {
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	
	string input = args.input_desc_file.substr(args.input_desc_path.length(),args.input_desc_file.length());
	char command_description[80+20];
	sprintf(command_description,"%04d/%02d/%02d %02d:%02d REP(%s): l=%d d=(%.1f,%.1f,%.1f) s=%s",
			tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,tm->tm_hour,tm->tm_min,
			input.c_str(),args.crop_length,args.dx,args.dy,args.dz,args.sym_type.c_str());
	mrcs_writer.header.addLABEL(command_description);
}

