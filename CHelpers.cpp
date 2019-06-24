#include "StdAfx.h"
#include "chelpers.h"

//uses singleton patteren
CHelpers * CHelpers::m_pinstanceof = NULL;

CHelpers * CHelpers::Initialise()
{
	if (m_pinstanceof)
		return m_pinstanceof;
	return m_pinstanceof = new CHelpers;
}


void CHelpers::Destroy()
{
	if(m_pinstanceof)
		delete m_pinstanceof;
	m_pinstanceof = NULL;
}


CHelpers * CHelpers::Instance()
{
	return m_pinstanceof;
}


CHelpers::CHelpers(void)
{
}

CHelpers::~CHelpers(void)
{
}

//calculates the factorial
long double CHelpers::Factorial(const int & t_in)
{
	if (t_in == 0)
		return 1.0;
	long double t_ldfactorial = 1.0;
	for(int i=t_in; i>1; i--)
		t_ldfactorial *= i;
	return t_ldfactorial;
		
}

//calculates the power
long double CHelpers::Power(const double  t_dtime,const int & t_ipower)
{
	if (t_ipower == 0)
		return 1.0;
	if (t_dtime == 0.0)
		return 0.0;
	long double t_ldresult = t_dtime;
	for(int i=1; i<t_ipower; i++)
		t_ldresult *= t_dtime;
	return t_ldresult;
}