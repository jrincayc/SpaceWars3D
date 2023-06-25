#ifndef __ODE__
#define __ODE__

#include <vector>
#include "Vector3D.h"

using namespace std;

typedef void (*deriv_func) (const float*,const int,const float, float *);
typedef void (*deriv_func_vec) (const Vector3D*,const int,const float, 
				Vector3D *);
typedef void (*deriv_func_vector) (const vector<Vector3D>*,const float,
				   vector<Vector3D>*,void *);

void rk2(const float *y0,const int y0_length,
	 const float time_0, const float dt, 
	 deriv_func func, float *y_ret);

void rk2v(const Vector3D *y0, const int y0_length,
	  const float time_0, const float dt,
	  deriv_func_vec func, Vector3D *y_ret);

void rk4(const float *y0,const int y0_length,
	 const float time_0, const float dt, 
	 deriv_func func, float *y_ret);

void rk4v(const Vector3D *y0, const int y0_length,
	  const float time_0, const float dt,
	  deriv_func_vec func, Vector3D *y_ret);

void rk4vector(const vector<Vector3D> * y0,
	       const float time_0, const float dt,
	       deriv_func_vector func, vector<Vector3D> *y_ret,
	       void * extra);


#endif //ifndef __ODE__
