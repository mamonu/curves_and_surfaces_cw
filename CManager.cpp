#include "StdAfx.h"
#include "cmanager.h"


CManager::CManager(void)
{
	m_pcurve = NULL;
}

CManager::~CManager(void)
{
	if (m_pcurve)
		delete m_pcurve;
}

//void CManager::Create(const int t_icurve)
//{
//	switch(t_icurve)
//	{
//		case BEZIER:				if (m_pcurve)
//										delete m_pcurve;
//									m_pcurve = new CBezier();
//									break;
//		case QUADRATICBSPLINE:		if (m_pcurve)
//										delete m_pcurve;
//									m_pcurve = new CBezier();
//									break;
//		case HERMITE:				if (m_pcurve)
//										delete m_pcurve;
//									m_pcurve = new CBezier();
//									break;
//	}
//
//}


