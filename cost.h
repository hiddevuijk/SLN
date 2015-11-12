#ifndef GUARD_cost_h
#define GUARD_cost_h

/// put in FLN weight



double logfunc(double x) { return 1.0/(1+std::exp(-1.*x)); }
double diflogfunc(double x) { return std::exp(-1.*x)/((1+std::exp(-1.*x))*(1+std::exp(-1.*x))); }

double cost(const std::vector<std::vector<double> > &SLN, const std::vector<std::vector<double> > &FLN, const std::vector<double> &vec) {
	double out = 0.0;
	double temp =0;
	for(int i=0; i<SLN.size();i++) {
		for(int j=0;j<SLN[i].size();j++) {
			if(FLN[i][j]!=0){
				temp = SLN[i][j] - logfunc(vec[i]-vec[j]);
				out += temp*temp*FLN[i][j];
			}
		}
	}
	return out;
}

double difcost(const std::vector<std::vector<double> > &SLN, const std::vector<std::vector<double> > &FLN, const std::vector<double> &vec, int k) {
	double out = 0.0;
	for(int i=0;i<SLN.size();i++) {
		if(FLN[i][k]!=0) {
			out += 2*(SLN[i][k]-logfunc(vec[i]-vec[k]))*diflogfunc(vec[i]-vec[k])*FLN[i][k];
		}
		if(FLN[k][i]!=0){	
			out -= 2*(SLN[k][i]-logfunc(vec[k]-vec[i]))*diflogfunc(vec[k]-vec[i])*FLN[k][i];
		}
	}
	return out;
}

double costl(const std::vector<std::vector<double> > &SLN, const std::vector<std::vector<double> > &FLN, const std::vector<double> &vec, double mu) {
	double out = 0.0;
	double temp =0;
	for(int i=0; i<SLN.size();i++) {
		for(int j=0;j<SLN[i].size();j++) {
			if(FLN[i][j]!=0){
				temp = SLN[i][j] - logfunc(vec[i]-vec[j]);
				out += temp*temp*FLN[i][j];
			}
		}
		if(i!=0) out -= mu*std::log(vec[i]);
	}
	return out;
}

double difcostl(const std::vector<std::vector<double> > &SLN, const std::vector<std::vector<double> > &FLN, const std::vector<double> &vec, int k, double mu) {
	double out = 0.0;
	for(int i=0;i<SLN.size();i++) {
		if(FLN[i][k]!=0) {
			out += 2*(SLN[i][k]-logfunc(vec[i]-vec[k]))*diflogfunc(vec[i]-vec[k])*FLN[i][k];
		}
		if(FLN[k][i]!=0){	
			out -= 2*(SLN[k][i]-logfunc(vec[k]-vec[i]))*diflogfunc(vec[k]-vec[i])*FLN[i][k];
		}
	}
	out -= mu/(vec[k]);
	return out;
}





#endif

