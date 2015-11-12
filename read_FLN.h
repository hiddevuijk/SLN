#ifndef GUARD_read_FLN_h
#define GUARD_read_FLN_h

#include "find_char.h"

#include <string>
#include <fstream>


void read_mat(std::vector<std::vector<double> > &mat, std::string fname){
	std::ifstream infile;
	infile.open(fname);
	
	std::string line;
	std::vector<int> del_pos;
	for(int i=0;i<mat.size();i++) {
		getline(infile,line,'\n');
		line = ';'+line;
		del_pos = find_char(line,';');
		for(int j=0;j<mat[i].size()-1;j++) {
			mat[i][j] = stod(line.substr(del_pos[j]+1,del_pos[j+1]-del_pos[j]-1));
		}
	}
}
#endif

