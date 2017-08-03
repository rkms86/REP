#include "SymEngine.h"

SymEngine::SymEngine(string sym_str, float x, float y, float z) {

	if( sym_str[0] == 'c' || sym_str[0] == 'C' ) {
		sym_group = SYM_CYCLIC;
		string tmp = sym_str.substr(1,sym_str.length());
		sym_num = atoi( tmp.c_str() );
	}
	else if( sym_str[0] == 'd' || sym_str[0] == 'D' ) {
		sym_group = SYM_DIHEDRAL;
		string tmp = sym_str.substr(1,sym_str.length());
		sym_num = 2*atoi( tmp.c_str() );
	}
	else {
		cerr << "Invalid symmetry group\n";
		exit(-1);
	}

	dx = x;
	dy = y;
	dz = z;
}

SymEngine::~SymEngine() {

	

}

void SymEngine::start() {

	sym_counter = 0;

}

bool SymEngine::should_continue() {

	return (sym_counter < sym_num);

}

void SymEngine::next() {

	sym_counter++;

}

void SymEngine::apply_sym(float&out_x,float&out_y,float&ang_rot,float&ang_tlt,float&ang_psi) {

	if( sym_group == SYM_CYCLIC ) {
		
		float ang_off = 360.0f*float(sym_counter)/float(sym_num);
		ang_rot = ang_rot + ang_off;
		
		eZYZ_2_M(-ang_psi,-ang_tlt,-ang_rot);
		calculate_offset(out_x, out_y);
	}

	else
	
	if( sym_group == SYM_DIHEDRAL ) {
		
		float NUM = sym_num/2;
		
		int d = sym_counter/NUM;
		float c = sym_counter - sym_num*d;
		
		float ang_off = 360.0f*c/NUM;
		ang_rot = ang_rot + ang_off;
		if( d > 0 ) {
			ang_psi = ang_psi + 180.0f;
		}
		eZYZ_2_M(-ang_psi,-ang_tlt,-ang_rot);
		calculate_offset(out_x, out_y);
	}

}

void SymEngine::calculate_offset(float&off_x, float&off_y) {

	off_x = 0.0f;
	off_y = 0.0f;

	off_x = Rx[0]*dx + Rx[1]*dy + Rx[2]*dz;
	off_y = Ry[0]*dx + Ry[1]*dy + Ry[2]*dz;
}

void SymEngine::calculate_offset(float&off_x, float&off_y, float ang_rot, float ang_tlt, float ang_psi) {

	off_x = 0.0f;
	off_y = 0.0f;

	float eu0 = -ang_psi * M_PI / 180.0f;
	float eu1 = -ang_tlt * M_PI / 180.0f;
	float eu2 = -ang_rot * M_PI / 180.0f;

	float cz0 = cos(eu0);
	float cy  = cos(eu1);
	float cz1 = cos(eu2);
	float sz0 = sin(eu0);
	float sy  = sin(eu1);
	float sz1 = sin(eu2);

	float R00 = cy*cz0*cz1-sz0*sz1;
	float R01 = -cz1*sz0-cy*cz0*sz1;
	float R02 = sy*cz0;
	float R10 = cy*cz1*sz0+cz0*sz1;
	float R11 = cz0*cz1-cy*sz0*sz1;
	float R12 = sy*sz0;
	//float R20 = -sy*cz1;
	//float R21 = sy*sz1;
	//float R22 = cy;

	off_x = R00*dx + R01*dy + R02*dz;
	off_y = R10*dx + R11*dy + R12*dz;
}

void SymEngine::eZYZ_2_M(float ang_rot,float ang_tlt,float ang_psi) {
	
	float eu0 = ang_rot * M_PI / 180.0f;
	float eu1 = ang_tlt * M_PI / 180.0f;
	float eu2 = ang_psi * M_PI / 180.0f;

	float cz0 = cos(eu0);
	float cy  = cos(eu1);
	float cz1 = cos(eu2);
	float sz0 = sin(eu0);
	float sy  = sin(eu1);
	float sz1 = sin(eu2);
	
	Rx[0] = cy*cz0*cz1-sz0*sz1;
	Rx[1] = -cz1*sz0-cy*cz0*sz1;
	Rx[2] = sy*cz0;
	Ry[0] = cy*cz1*sz0+cz0*sz1;
	Ry[1] = cz0*cz1-cy*sz0*sz1;
	Ry[2] = sy*sz0;
	Rz[0] = -sy*cz1;
	Rz[1] = sy*sz1;
	Rz[2] = cy;
	
}

void SymEngine::M_2_eZYZ(float&ang_rot,float&ang_tlt,float&ang_psi) {
	
	ang_rot = 0;
	ang_tlt = 0;
	ang_psi = 0;

	if( Rz[2] < 1.0f ) {
		
		if( Rz[2] > -1.0f ) {
			
			ang_rot = atan2( Ry[2], Rx[0] ) * 180.0f / M_PI;
			ang_tlt = acos( Rz[2] ) * 180.0f / M_PI;;
			ang_psi = atan2( Rz[1], -Rz[0] ) * 180.0f / M_PI;
			
		}
		else { /// Rz[2] == -1.0f
			
			ang_rot = -atan2( Ry[0], Ry[1] ) * 180.0f / M_PI;
			ang_tlt = M_PI;
			ang_psi = 0;
			
		}
		
	}
	else { /// Rz[2] == +1.0f
		
		ang_rot = atan2( Ry[0], Ry[1] ) * 180.0f / M_PI;
		ang_tlt = 0;
		ang_psi = 0;
		
	}
	
}



