#ifndef GUARD_cost2_h
#define GUARD_cost2_h


double logfunc(double x) { return 1.0/(1+std::exp(-1.*x)) ;}
double diflogfunc(double x) { return std::exp(x)/((1+std::exp(x))*(1+std::exp(x))) ;}

double cost (const std::vector<std::vector<double> >& SLN, const double& SLNavg,const double& SLNvar,
			const std::vector<std::vector<double> >& SLNpred, const double& SLNpredavg, const double& SLNpredvar,
			const std::vector<std::vector<double> >& FLN,
			const std::vector<double>& h, const double& N,double mu)
{
	double temp = 0.0;
	double temp2 = 0.0;
	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++) if(FLN[i][j]!=0) {
			temp += log(FLN[i][j])*SLN[i][j]*(SLNpred[i][j]-SLNpredavg);
		}
		if(i!=0) temp2 -= std::log(h[i]);
	}

	return (temp/((N*N-1)*SLNvar*SLNpredvar)) - mu*temp2;
}


double difcost (const std::vector<std::vector<double> >& SLN, const double& SLNavg,const double& SLNvar,
			const std::vector<std::vector<double> >& SLNpred, const double& SLNpredavg, const double& SLNpredvar,
			const std::vector<std::vector<double> >& FLN,
			const std::vector<double>& h, const double& N, int k,double mu)
{
	double temp1 = 0.0;
	double temp2 = 0.0;
	double temp3 = 0.0;
	double temp4 = 0.0;
	double temp5 = 0.0;
	double temp6 = 0.0;
	for(int i=0;i<N;i++) {
		temp1 += diflogfunc(h[k]-h[i]);
		if(i!=0) temp6 += -1.*mu/h[i];
		temp3 = 0.0;
		for(int j=0;j<N;j++) {
			if(FLN[i][j] !=0 ){
				temp2 += log(FLN[i][j])*SLN[i][j]*(SLNpred[i][j]-SLNpredavg);
				for(int n=0;n<N;n++) {
					temp3 += log(FLN[i][j])*SLN[i][j]*diflogfunc(h[k]-h[n]);
				}
			}
		}
		if(FLN[k][i] != 0 && FLN[k][i]!=0) temp4 += ((log(FLN[k][i])*SLN[k][i]-log(FLN[k][i])*SLN[i][k])*diflogfunc(h[k]-h[i])-2.*temp3/(N*N));
	}
	temp5 = 1./((N*N-1)*SLNpredvar*SLNpredvar);
	temp2 = temp2*temp1*(1.+2*SLNpredavg)/(2*N*N*SLNpredvar*SLNpredvar);


	return temp5*(temp4+temp2)-temp6;
}

double mean_mat(const std::vector<std::vector<double> >& mat, int N)
{
	double temp = 0.0;
	for(int i=0; i<N;i++) for(int j=0;j<N;j++){
		temp += mat[i][j];
	}
	return temp/(N*N);
	
}

double var_mat(const std::vector<std::vector<double> >& mat, int N, double a=0.0)
{
	if(a!=0.0) a = mean_mat(mat,N);
	double temp = 0.0;
	double var = 0.0;
	for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
		temp = mat[i][j]-a;
		var += temp*temp;
	}
	return sqrt(var/(N*N));
}


#endif

