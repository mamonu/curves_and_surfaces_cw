#pragma once

class CBSplineHelpers
{
private:
	static CBSplineHelpers * m_pinstanceof; 
public:
	static CBSplineHelpers * Initialise();
	static CBSplineHelpers * Instance();
	static void Destroy();
public:
	CBSplineHelpers(void);
	~CBSplineHelpers(void);
	void CreateStandardKnots(const int &t_inumpoints,const int &t_iorder,int **t_piknot);
	double Weight(const int & t_ik,const int & t_iorder,const double & t_dtime,int *t_piknot);
};
