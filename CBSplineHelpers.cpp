#include "StdAfx.h"
#include "cbsplinehelpers.h"


//uses sinleton pattern
CBSplineHelpers * CBSplineHelpers::m_pinstanceof = NULL;

CBSplineHelpers * CBSplineHelpers::Initialise()
{
	if (m_pinstanceof)
		return m_pinstanceof;
	return m_pinstanceof = new CBSplineHelpers;
}


void CBSplineHelpers::Destroy()
{
	if(m_pinstanceof)
		delete m_pinstanceof;
	m_pinstanceof = NULL;
}


CBSplineHelpers * CBSplineHelpers::Instance()
{
	return m_pinstanceof;
}

CBSplineHelpers::CBSplineHelpers(void)
{
}

CBSplineHelpers::~CBSplineHelpers(void)
{
}

//creates standard knots
void CBSplineHelpers::CreateStandardKnots(const int &t_inumpoints,const int &t_iorder,int **t_piknot)
{
	if (t_inumpoints < t_iorder)
		return;
	int t_inumknots = t_inumpoints + t_iorder;
	if(*t_piknot)
		delete [] *t_piknot;
	*t_piknot = new int[t_inumknots];
	int *t_ptr = *t_piknot;
	
	for (int i=0; i< t_inumknots; i++)
	{
		if (i< t_iorder)
			*t_ptr = 0;
		else if (i < t_inumpoints)
			*t_ptr = i - t_iorder + 1;
		else 
            *t_ptr = t_inumpoints - t_iorder + 1;
		t_ptr++;
	}
}

//claculate the weight for bspline
double CBSplineHelpers::Weight(const int & t_ik,const int & t_iorder,const double & t_dtime,int *t_piknot)
{
	double t_dweight=0.0;
	if (t_iorder == 1)
		return ( t_dtime >= t_piknot[t_ik] &&  t_dtime < t_piknot[t_ik + 1]);
	double t_ddenominator =  t_piknot[t_ik + t_iorder -1] - t_piknot[t_ik];
	if (t_ddenominator != 0.0)
		t_dweight = (t_dtime - t_piknot[t_ik]) * Weight(t_ik,t_iorder-1,t_dtime,t_piknot)/t_ddenominator;
	t_ddenominator = t_piknot[t_ik + t_iorder] - t_piknot[t_ik + 1];
	if (t_ddenominator != 0.0)
		t_dweight += (t_piknot[t_ik + t_iorder]- t_dtime) * Weight(t_ik+1,t_iorder-1,t_dtime,t_piknot)/t_ddenominator;
	return t_dweight;


}