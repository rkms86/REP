#ifndef SYMENGINE_H
#define SYMENGINE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

#include <stdint.h>

using namespace std;

class SymEngine {

public:
	typedef enum {
		SYM_CYCLIC,
		SYM_DIHEDRAL
	} PointGroup_t;
  
public:
	SymEngine(string sym_str, float x, float y, float z);
	~SymEngine();

	void start();
	bool should_continue();
	void next();

	void apply_sym(float&out_x,float&out_y,float&ang_rot,float&ang_tlt,float&ang_psi);

public:
	PointGroup_t	sym_group;
	int				sym_num;
	
protected:
	int		sym_counter;
	
	float	dx;
	float	dy;
	float	dz;
	
	float Rx[3];
	float Ry[3];
	float Rz[3];
	
protected:
	void calculate_offset(float&out_x,float&out_y);
	void calculate_offset(float&out_x,float&out_y,float ang_rot,float ang_tlt,float ang_psi);
	
	void eZYZ_2_M(float ang_rot,float ang_tlt,float ang_psi);
	void M_2_eZYZ(float&ang_rot,float&ang_tlt,float&ang_psi);
};

#endif

