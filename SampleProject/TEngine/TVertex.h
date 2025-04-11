#pragma once
#include "TVector.h"
struct P_VERTEX
{
	TVector2 v;
};
struct PC_VERTEX
{
	TVector2 v;
	TVector4 c;
};
struct PCT_VERTEX
{
	TVector2 v;
	TVector4 c;
	TVector2 t;
};
struct PNCT_VERTEX
{
	TVector3 p;
	TVector3 n;
	TVector4 c;
	TVector2 t;
	PNCT_VERTEX() {}
	PNCT_VERTEX(TVector3 p, TVector3 n, TVector4 c,
		TVector2 t)
	{
		this->p = p;
		this->n = n;
		this->c = c;
		this->t = t;
	}
};
struct IW_Vertex
{
	float	w0[4];// W0, fW1, fW2, fW3;
	float	i0[4];	// I0, I1, I2, I3
	float	w1[4];// W4, fW5, fW6, fNumWeight;	
	float	i1[4];	// I4, I5, I6, I7
	IW_Vertex()
	{
		i0[3] = i0[2] = i0[1] = i0[0] = 0.0f;
		w0[3] = w0[2] = w0[1] = w0[0] = 0.0f;
		i1[3] = i1[2] = i1[1] = i1[0] = 0.0f;
		w1[3] = w1[2] = w1[1] = w1[0] = 0.0f;
	}
};
