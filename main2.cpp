//#include "nr_headers/nr3.h"
//#include "nr_headers/ran.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

#include "cost2.h"
#include "read_FLN.h"

using namespace::std;


int main()
{

	double alpha = 1e-4;
	double mu = 5e-4;
	int MAXSTEP = 1;

	vector<double> vec_doub(29,0.0);
	vector<vector<double> > SLN(29,vec_doub);
	read_mat(SLN,"SLN.csv");

	vector<vector<double> > FLN(29,vec_doub);
	read_mat(FLN,"FLN.csv");

	vector<vector<double> > SLNpred(29,vec_doub);

	vector<double> h(29,0.0);	


	vector<double> costsl;
	vector<double> costs;
	int N =29;
	ifstream h_in;
	double hmax = 0.0;
	h_in.open("ha.csv");
	for(int i=0;i<h.size();i++){
		h_in >> h[i];
		if(h[i] > hmax ) hmax = h[i];
	}
	for(int i=0;i<h.size();i++) h[i] /= hmax;

	double SLNavg = mean_mat(SLN,N);
	double SLNvar = var_mat(SLN,N,SLNavg);
	double SLNpredavg = 0.0;
	double SLNpredvar = 0.0;
	double hm = 0.0;
	vector<double> htemp = h;
	for(int step=0;step<MAXSTEP;step++) {
		
		for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
			SLNpred[i][j] = logfunc(h[i]-h[j]);
		}
		SLNpredavg = mean_mat(SLNpred,N);
		SLNpredvar = var_mat(SLNpred,N,SLNpredavg);

		for(int j=1;j<h.size();j++) {
			htemp[j] = h[j] + alpha*difcost(SLN,SLNavg,SLNvar,SLNpred,SLNpredavg,SLNpredvar,FLN,h,N,j,mu);
//			htemp[j] = h[j]-alpha*difcostl(SLN,FLN,h,j,mu);

		}
//		hm= 0.0;
//		for(int i=0;i<h.size();i++)
//			if(hm > h[i]) hm = h[i];
//		for(int i=0;i<h.size();i++)
//			h[i] /= hm;
		h=htemp;
		costs.push_back(cost(SLN,SLNavg,SLNvar,SLNpred,SLNpredavg,SLNpredvar,FLN,h,N,mu));
		costsl.push_back(costs[step]);
	}


	ofstream SLNpred_out("SLNpredicted.csv");
	ofstream SLN_out("SLN.csv");	
	for(int i=0;i<SLNpred.size();i++) {
		for(int j=0;j<SLNpred[i].size();j++) {
			SLNpred[i][j] = logfunc(h[i]-h[j]);
			SLNpred_out <<SLNpred[i][j] ;
			SLN_out << SLN[i][j];
			if(j<(SLNpred[i].size()-1)){
				SLNpred_out <<';'; 
				SLN_out <<';';
			}
		}
		SLNpred_out << '\n';
		SLN_out << '\n';
	}

	ofstream cost_out("cost.csv");
	ofstream costl_out("costl.csv");
	for(int i=0;i<costs.size();i++) {
		cost_out << costs[i] <<'\n';
		costl_out<<costsl[i] <<'\n';
	}
	ofstream h_out("h.csv");
	for(int i=0;i<h.size();i++) {
		h_out << h[i] << '\n';
	}
	

	return 0;
}






