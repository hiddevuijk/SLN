#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "delimiter_position.h"
#include "str_in_vec.h"
#include "where_in_vec.h"

using namespace::std;

int main()
{


	vector<string> order = {"V1","V2","V4","DP","MT","8m",
		"5","8l","TEO","2","F1","STPc","7A","46d","10",
		"9/46v","9/46d","F5","TEpd","PBr","7m","7B","F2",
		"STPi","ProM","F7","8B","STPr","24c"};

	ifstream infile;
	infile.open("data.csv");
	if(!infile) cout << "Could not read file!!!" << endl;

	vector<vector<string> > table(1602);
	vector<string> sources;
	vector<string> targets;
	string line;
	vector<int> del_pos;
	vector<string> head;
	getline(infile,line,'\n');
	del_pos = find_char(line,',');

	head.push_back(line.substr(0,del_pos[0]));
	head.push_back(line.substr(del_pos[0]+1,del_pos[1]-del_pos[0]-1));
	head.push_back(line.substr(del_pos[1]+1,del_pos[2]-del_pos[1]-1));
	head.push_back(line.substr(del_pos[2]+1,del_pos[3]-del_pos[2]-1));

	for(int i=0; i<table.size();i++) {
		getline(infile,line,'\n');
		del_pos = find_char(line,',');

		table[i].push_back(line.substr(0,del_pos[0]));
		table[i].push_back(line.substr(del_pos[0]+1,del_pos[1]-del_pos[0]-1));
		table[i].push_back(line.substr(del_pos[1]+1,del_pos[2]-del_pos[1]-1));
		table[i].push_back(line.substr(del_pos[2]+1,del_pos[3]-del_pos[2]-1));

	}
	infile.close();


//	for(int i=0;i<table.size();i++){
//		if(str_in_vec(table[i][1],sources)==false) {
//			sources.push_back(table[i][1]);
//		}
//		if(str_in_vec(table[i][0],targets)==false) {
//			targets.push_back(table[i][0]);
//		}
//	}
//

	vector<double> doubvec(29,0.0);
	vector<vector<double> > SLN(29,doubvec);

	string ss,st;
	int count = 0;
	for(int i=0;i<table.size();i++) {
		if(str_in_vec(table[i][0],order)&&str_in_vec(table[i][1],order) ) {
			count++;			
			ss = table[i][1];
			st = table[i][0];

			int ns = where_in_vec(ss,order);
			int nt = where_in_vec(st,order);
			SLN[nt][ns] += stod(table[i][3]);
		}
	}
	cout << count << endl;

	
	ofstream SLN_out("SLN.csv");
	for(int i=0;i<SLN.size();i++) {
		for(int j=0;j<SLN[i].size();j++) {
			SLN_out << SLN[i][j];
			if(j<SLN[i].size()-1) SLN_out <<';';
		}
		SLN_out << '\n';
	}	

	ofstream order_out("order.txt");
	for(int i=0;i<order.size();i++) order_out << order[i] << '\n';

	return 0;

}




