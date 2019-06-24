#pragma once

class CHelpers
{
private:
	static CHelpers * m_pinstanceof; 
public:
	static CHelpers * Initialise();
	static CHelpers * Instance();
	static void Destroy();
	CHelpers(void);
	~CHelpers(void);
	long double Factorial(const int & t_in);
	long double Power(const double  t_dtime,const int & t_power);
};

