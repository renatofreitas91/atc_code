

#include "calc.h"
#include "stdafx.h"


double gerrorc(double q){
	double result = 0;
	result = boost::math::erfc(q);
	return result;
}

double gerrorcinv(double a){
	double result = 0;
	if (a <= 2 && a >= 0){
		if (a == 0){ result = pow(2.0, 2000); return result; }
		result = boost::math::erfc_inv(a);
	}
	else{
		result = 0;
	}
	return result;
}

double gerror(double q){
	double result = 0;
	result = boost::math::erf(q);
	return result;
}

double gerrorinv(double e){
	double result = 0;
	if (e <= 1 && e >= -1){
		if (e == 1){ result = pow(2.0, 2000); return result; }
		if (e == -1){ result = -pow(2.0, 2000); return result; }
		result = boost::math::erf_inv(e);
	}
	else{
		result = 0;
	}
	return result;
}

double qfunc(double x){
	double result = 0, y = 0;
	y = x / sqrt(2.0);
	result = 0.5*gerrorc(y);
	return result;
}

double qfuncinv(double p){
	double result = 0, d = 0;
	d = p / 0.5;
	result = sqrt(2.0)*gerrorcinv(d);
	return result;
}
