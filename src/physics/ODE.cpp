/*
 *  ODE.cpp
 *  SpaceWars3D
 *
 *  Created by Josh Cogliati
 *  $Id: ODE.cpp,v 1.6 2003/05/05 21:10:54 jjc Exp $
 */

#include "ODE.h"

void rk2(const float *y0,const int y0_length,
	 const float time_0, const float dt, 
	 deriv_func func, float *y_ret)
{
	float *y_star = new float[y0_length];
	float *f = new float[y0_length];
	func(y0, y0_length, time_0, f);
	for(int i = 0; i < y0_length; i++)
	{
		y_star[i] = y0[i]+0.5f*dt*f[i];
	}
	float *f2 = new float[y0_length];
	func(y_star, y0_length, time_0+0.5f*dt, f2);
	for(int i = 0; i < y0_length; i++)
	{
		y_ret[i] = y0[i]+dt*f2[i];
	}
	delete[] y_star;
	delete[] f;
	delete[] f2;
}

void rk2v(const Vector3D *y0,const int y0_length,
	  const float time_0, const float dt, 
	  deriv_func_vec func, Vector3D *y_ret)
{
	Vector3D *y_star = new Vector3D[y0_length];
	Vector3D *f = new Vector3D[y0_length];
	func(y0, y0_length, time_0, f);
	for(int i = 0; i < y0_length; i++)
	{
		y_star[i] = y0[i]+0.5f*dt*f[i];
	}
	Vector3D *f2 = new Vector3D[y0_length];
	func(y_star, y0_length, time_0+0.5f*dt, f2);
	for(int i = 0; i < y0_length; i++)
	{
		y_ret[i] = y0[i]+dt*f2[i];
	}
	delete[] y_star;
	delete[] f;
	delete[] f2;
}


void rk4(const float *y0,const int y0_length,
	 const float time_0, const float dt, 
	 deriv_func func, float *y_ret)
{
	float *f1 = new float[y0_length];
	func(y0, y0_length, time_0, f1);
	
	float *y2 = new float[y0_length];
	for(int i = 0; i < y0_length; i++)
	{
		y2[i] = y0[i] + 0.5*dt*f1[i];
	}
	float *f2 = new float[y0_length];
	func(y2, y0_length, time_0+0.5*dt, f2);
	
	float *y3 = new float[y0_length];
	for(int i = 0; i < y0_length; i++)
	{
		y3[i] = y0[i] + 0.5*dt*f2[i];
	}
	float *f3 = new float[y0_length];
	func(y3, y0_length, time_0+0.5*dt, f3);

	float *y4 = new float[y0_length];
	for(int i = 0; i < y0_length; i++)
	{
		y4[i] = y0[i] + dt*f3[i];
	}
	float *f4 = new float[y0_length];
	func(y4, y0_length, time_0+dt, f4);

	for(int i = 0; i < y0_length; i++)
	{
		y_ret[i] = y0[i] + (dt/6.0)*(f1[i]+2.0*f2[i]+2.0*f3[i]+f4[i]);
	}
	delete[] f1;
	delete[] y2;
	delete[] f2;
	delete[] y3;
	delete[] f3;
	delete[] y4;
	delete[] f4;
}

void rk4v(const Vector3D *y0,const int y0_length,
	  const float time_0, const float dt, 
	  deriv_func_vec func, Vector3D *y_ret)
{
	Vector3D *f1 = new Vector3D[y0_length];
	func(y0, y0_length, time_0, f1);
	
	Vector3D *y2 = new Vector3D[y0_length];
	for(int i = 0; i < y0_length; i++)
	{
		y2[i] = y0[i] + 0.5*dt*f1[i];
	}
	Vector3D *f2 = new Vector3D[y0_length];
	func(y2, y0_length, time_0+0.5*dt, f2);
	
	Vector3D *y3 = new Vector3D[y0_length];
	for(int i = 0; i < y0_length; i++)
	{
		y3[i] = y0[i] + 0.5*dt*f2[i];
	}
	Vector3D *f3 = new Vector3D[y0_length];
	func(y3, y0_length, time_0+0.5*dt, f3);

	Vector3D *y4 = new Vector3D[y0_length];
	for(int i = 0; i < y0_length; i++)
	{
		y4[i] = y0[i] + dt*f3[i];
	}
	Vector3D *f4 = new Vector3D[y0_length];
	func(y4, y0_length, time_0+dt, f4);

	for(int i = 0; i < y0_length; i++)
	{
		y_ret[i] = y0[i] + (dt/6.0)*(f1[i]+2.0*f2[i]+2.0*f3[i]+f4[i]);
	}
	delete[] f1;
	delete[] y2;
	delete[] f2;
	delete[] y3;
	delete[] f3;
	delete[] y4;
	delete[] f4;
}

void rk4vector(const vector<Vector3D> * y0,
	       const float time_0, const float dt,
	       deriv_func_vector func, vector<Vector3D> *y_ret,
	       void * extra)
{
    int y0_length = y0->size();
    vector<Vector3D> f1;
    f1.resize(y0_length);
    func(y0, time_0, &f1,extra);
	
    vector<Vector3D> yt;
    yt.resize(y0_length);
    for(int i = 0; i < y0_length; i++)
    {
	yt[i] = (*y0)[i] + 0.5*dt*f1[i];
    }
    vector<Vector3D> f2;
    f2.resize(y0_length);
    func(&yt, time_0+0.5*dt, &f2,extra);
	
    for(int i = 0; i < y0_length; i++)
    {
	yt[i] = (*y0)[i] + 0.5*dt*f2[i];
    }
    vector<Vector3D> f3;
    f3.resize(y0_length);
    func(&yt, time_0+0.5*dt, &f3,extra);

    for(int i = 0; i < y0_length; i++)
    {
	yt[i] = (*y0)[i] + dt*f3[i];
    }
    vector<Vector3D> f4;
    f4.resize(y0_length);
    func(&yt, time_0+dt, &f4,extra);

    for(int i = 0; i < y0_length; i++)
    {
	(*y_ret)[i] = (*y0)[i] + (dt/6.0)*(f1[i]+2.0*f2[i]+2.0*f3[i]+f4[i]);
    }
}

