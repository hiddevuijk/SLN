#ifndef GUARD_cost_h
#define GUARD_cost_h

/// put in FLN weight



double logfunc(double x, double sl) { return 1.0/(1+std::exp(-1.*sl*x)); }
double diflogfunc(double xi, double sl) { return sl*std::exp(-1.*sl*x)/((1+std::exp(-1.*sl*x))*(1+std::exp(-1.*sl*x))); }
//double logfunc(double x){ return (1+std::atan(x)/(0.5*std::acos(-1)));}
//double diflogfunc(double x) { return 1./(x*x+1);}

double cost(const std::vector<std::vector<double> > &SLN, const std::vector<std::vector<double> > &FLN, const std::vector<double> &vec, double k, double sl) {
	double out = 0.0;
	double temp =0;
	for(int i=0; i<SLN.size();i++) {
		for(int j=0;j<SLN[i].size();j++) {
			if(FLN[i][j]!=0){
				temp = SLN[i][j] - logfunc(vec[i]-vec[j],sl);
				out += temp*temp;
			}
		}
	}
	return out;
}

double difcost(const std::vector<std::vector<double> > &SLN, const std::vector<std::vector<double> > &FLN, const std::vector<double> &vec, int k, double sl) {
	double out = 0.0;
	for(int i=0;i<SLN.size();i++) {
		if(FLN[i][k]!=0) {
			out += 2*(SLN[i][k]-logfunc(vec[i]-vec[k],sl))*diflogfunc(vec[i]-vec[k],sl);
		}
		if(FLN[k][i]!=0){	
			out -= 2*(SLN[k][i]-logfunc(vec[k]-vec[i],sl))*diflogfunc(vec[k]-vec[i],sl);
		}
	}
	return out;
}

double costl(const std::vector<std::vector<double> > &SLN, const std::vector<std::vector<double> > &FLN, const std::vector<double> &vec, double mu, double sl) {
	double out = 0.0;
	double temp =0;
	for(int i=0; i<SLN.size();i++) {
		for(int j=0;j<SLN[i].size();j++) {
			if(FLN[i][j]!=0){
				temp = SLN[i][j] - logfunc(vec[i]-vec[j],sl);
				out += temp*temp;
			}
		}
		if(i!=0) out -= mu*std::log(vec[i]);
	}
	return out;
}

double difcostl(const std::vector<std::vector<double> > &SLN, const std::vector<std::vector<double> > &FLN, const std::vector<double> &vec, int k, double mu, double sl) {
	double out = 0.0;
	for(int i=0;i<SLN.size();i++) {
		if(FLN[i][k]!=0) {
			out += 2*(SLN[i][k]-logfunc(vec[i]-vec[k],sl))*diflogfunc(vec[i]-vec[k],sl);
		}
		if(FLN[k][i]!=0){	
			out -= 2*(SLN[k][i]-logfunc(vec[k]-vec[i],sl))*diflogfunc(vec[k]-vec[i],sl);
		}
	}
	out -= mu/(vec[k]);
	return out;
}






#endif

