#pragma once
#include<math.h>
using namespace std;

#ifndef V3_EPSILON
#define V3_EPSILON 1.0E-8
#endif
class Vector3d
{
/*public:
	Vector3d(void);
	~Vector3d(void);
};

#include "MathCon.h"
#include <string>
#include <stdlib.h>	// rand() - ANSI compatible

using namespace std;

#ifndef V3_EPSILON
#define V3_EPSILON 1.0E-8
#endif
*/
public:
	double x;
	double y;
	double z;

public:
	//-------------------------------------------------------------------------

	Vector3d();

	Vector3d(double);

	Vector3d(const Vector3d & V);

	Vector3d(double, double, double);

	//-------------------------------------------------------------------------

	const Vector3d & operator = ( const Vector3d & );

	//-------------------------------------------------------------------------

	Vector3d operator -() const;

	Vector3d operator - ( const Vector3d & ) const;

	Vector3d operator + ( const Vector3d & ) const;

	double   operator * ( const Vector3d & ) const;

	Vector3d operator ^ ( const Vector3d & ) const;

	Vector3d operator * ( double ) const;

	Vector3d operator / ( double ) const;

	/**
	* Increment operator. The operation L+=R is equivalent to the operation
	* L=L+R. It is usually faster also, since a temporary is not returned.
	*/
	const Vector3d & operator += ( const Vector3d & );

	/**
	* Decrement operator. The operation L-=R is equivalent to the operation
	* L=L-R. It is usually faster also, since a temporary is not returned.
	*/
	const Vector3d & operator -= ( const Vector3d & );

	/**
	* Multiply by double. The operation L*=R is equivalent to the operation
	* L=L*R. It is usually faster also, since a temporary is not returned.
	*/
	const Vector3d & operator *= ( double );


	/**
	* Divide by double. The operation L/=R is equivalent to the operation
	* L=L/R. It is usually faster also, since a temporary is not returned.
	*/
	const Vector3d & operator /= ( double );

	//-------------------------------------------------------------------------

	/**
	* Exact equality. Returns true if both vectors are exactly equal. It is
	* not good practice to use this operator. Use IsEqual() instead.
	*/
	//bool operator == (const Vector3d &) const;

	/**
	* Inequality operator. Returns true if the vectors are not exactly equal.
	* It is not good practice to use this operator. Use !IsEqual() instead.
	*/
	//bool operator != (const Vector3d &) const;

	//-------------------------------------------------------------------------

	/**
	* Vector addition. The code A.Add(L,R) is equivalent to A=L+R, but faster
	* since a temporary is not returned.
	*/
	const Vector3d & Add( const Vector3d &L, const Vector3d &R );

	/**
	* Vector subtraction. The code A.Subtract(L,R) is equivalent to A=L-R, but
	* faster since a temporary is not returned.
	*/
	const Vector3d & Subtract( const Vector3d &L, const Vector3d &R );

	/**
	* Multiply by double. The code A.Multiply(L,R) is equivalent to A=L*R, but
	* faster since a temporary is not returned.
	*/
	const Vector3d & Multiply( const Vector3d &L, double R );

	/**
	* Divide by double. The code A.Divide(L,R) is equivalent to A=L/R, but
	* faster since a temporary is not returned.
	*/
	const Vector3d & Divide( const Vector3d &L, double R );

	
	//-------------------------------------------------------------------------

	/**
	* Dot product. Returns the dot product of two vectors.
	*/
	double Dot (const Vector3d &V) const;

	/**
	* Cross product. A.Cross(B) returns the cross product of A and B.
	*/
	Vector3d Cross (const Vector3d &V) const;

	/**
	* Cross product. A.Cross(L,R) replaces A with the cross product of L and
	* R. The result is also returned. This method is preferred over A.Cross(B)
	* for performance reasons (no temporary is involved).
	*/
	const Vector3d & Cross (const Vector3d &L, const Vector3d &R);

	//-------------------------------------------------------------------------

	/**
	* Distance between two vectors.
	*/
	double Distance (const Vector3d &V) const;

	/**
	* Squared distance between two vectors. When comparing distances, it is
	* generally faster to compare the squared distance to avoid the square
	* root calculation.
	*/
	double DistanceSqr (const Vector3d &V) const;

	/**
	* Length of vector. This returns the length (magnitude) of the vector.
	*/
	double Length () const;

	/**
	* Squared length of vector. This returns the squared length of the
	* vector (squared magnitude). When comparing length, it is generally
	* faster to compare the squared length to avoid the square root
	* calculation.
	*/
	double LengthSqr () const;

	//-------------------------------------------------------------------------

	/**
	* Randomise a vector. This randomises a vector (in-place) with random
	* components in the range -scaleFac to +scaleFac on each axis. The results
	* lie within a cube with linear distribution on each axis.
	*/
	//const Vector3d & Randomise( double scaleFac );

	//-------------------------------------------------------------------------

	/**
	* Zero a vector. Replaces a vector with all zeros.
	*/
	const Vector3d & Zero();

	//-------------------------------------------------------------------------

	/**
	* Normalise a vector in place. If the vector is zero magnitude, then
	* the result is a zero vector.
	*/
	const Vector3d & Normalise();

	/**
	* Normalise a vector. The operation L.Normalise(R) replaces L with
	* the normalised (unit length) version of R. It is equivalent to
	* L=R.Normalise() but with less overhead, since a temporary object
	* is not returned.
	*/
	const Vector3d & Normalise( const Vector3d &V );

	//-------------------------------------------------------------------------

	/**
	* Invert a vector in place.
	*/
	const Vector3d & Invert();

	/**
	* Invert a vector. The operation L.Invert(R) replaces L with
	* the inverted version of R. It is equivalent to
	* L=R.Normalise() but with less overhead, since a temporary object
	* is not returned.
	*/
	const Vector3d & Invert( const Vector3d &V );

	//-------------------------------------------------------------------------

	/**
	* Vector is near zero. Returns true if a vector is very close to zero.
	* The default tolerance can be overidden.
	*/
	bool IsZero  (double Tolerance = V3_EPSILON) const;

	/**
	* Vector is near unit-length. Returns true if vector is very close to
	* unit length. The default tolerance can be overidden.
	*/
	bool IsUnit  (double Tolerance = V3_EPSILON) const;

	
	/**
	* Vector this is near equal to V. Returns true if vector this and V are very close to equal.
	* The default tolerance can be overidden.
	*/
	bool IsEqual(const Vector3d &V, double Tolerance = V3_EPSILON) const;



};

//-----------------------------------------------------------------------------

inline Vector3d::Vector3d()
{
	x=0.0;
	y=0.0;
	z=0.0;
}

//-----------------------------------------------------------------------------

inline Vector3d::Vector3d(double d)
{
	x=d;
	y=d;
	z=d;
}

//-----------------------------------------------------------------------------

inline Vector3d::Vector3d(const Vector3d & V)
{
	*this=V;
}

//-----------------------------------------------------------------------------

inline Vector3d::Vector3d(double X, double Y, double Z)
{
	x=X;
	y=Y;
	z=Z;
}

//-----------------------------------------------------------------------------

inline const Vector3d & Vector3d::operator = ( const Vector3d &V )
{
	x=V.x;
	y=V.y;
	z=V.z;
	return *this;
}

//-----------------------------------------------------------------------------

inline Vector3d Vector3d::operator -() const
{
	return Vector3d(-x, -y, -z);
}

inline Vector3d Vector3d::operator - (const Vector3d &V) const
{
	return Vector3d( x-V.x, y-V.y, z-V.z );
}

inline Vector3d Vector3d::operator + (const Vector3d &V) const
{
	return Vector3d( x+V.x, y+V.y, z+V.z );
}

inline double Vector3d::operator * (const Vector3d &V) const
{
	return Dot(V);
}

inline Vector3d Vector3d::operator ^ (const Vector3d &V) const
{
	return Cross(V);
}

inline Vector3d Vector3d::operator * ( double v ) const
{
	return Vector3d( x*v, y*v, z*v );
}

inline Vector3d Vector3d::operator / ( double v ) const
{
	return Vector3d( x/v, y/v, z/v );
}

inline const Vector3d & Vector3d::operator += ( const Vector3d &V )
{
	x+=V.x;
	y+=V.y;
	z+=V.z;
	return *this;
}

inline const Vector3d & Vector3d::operator -= ( const Vector3d &V )
{
	x-=V.x;
	y-=V.y;
	z-=V.z;
	return *this;
}

inline const Vector3d & Vector3d::operator *= ( double v )
{
	x*=v;
	y*=v;
	z*=v;
	return *this;
}

inline const Vector3d & Vector3d::operator /= ( double v )
{
	x/=v;
	y/=v;
	z/=v;
	return *this;
}

//-----------------------------------------------------------------------------

/*inline bool Vector3d::operator == (const Vector3d &V) const
{
	return (x==V.x) && (y==V.y) && (z==V.z);
}*/

//-----------------------------------------------------------------------------

/*inline bool Vector3d::operator != (const Vector3d &V) const
{
	return !(*this==V);
}*/

//-----------------------------------------------------------------------------

inline const Vector3d & Vector3d::Add( const Vector3d &L, const Vector3d &R )
{
	x=L.x+R.x;
	y=L.y+R.y;
	z=L.z+R.z;
	return *this;	
}

//-----------------------------------------------------------------------------

inline const Vector3d & Vector3d::Subtract(const Vector3d &L, const Vector3d &R	) 
{
	x=L.x-R.x;
	y=L.y-R.y;
	z=L.z-R.z;
	return *this;
}

//-----------------------------------------------------------------------------

inline const Vector3d & Vector3d::Multiply( const Vector3d &L, double R )
{
	x=L.x*R;
	y=L.y*R;
	z=L.z*R;
	return *this;
}

//-----------------------------------------------------------------------------

inline const Vector3d & Vector3d::Divide( const Vector3d &L, double R )
{
	x=L.x/R;
	y=L.y/R;
	z=L.z/R;
	return *this;
}


//---- Dot Product ------------------------------------------------------------

inline double Vector3d::Dot (const Vector3d &V) const
{
	return ( x*V.x + y*V.y + z*V.z );
}

//---- Cross Product -----------------------------------------------------------

inline Vector3d Vector3d::Cross (const Vector3d &V) const
{
	return Vector3d( y*V.z - z*V.y, z*V.x - x*V.z, x*V.y - y*V.x );
}

inline const Vector3d & Vector3d::Cross (const Vector3d &L, const Vector3d &R) {
	x = L.y*R.z - L.z*R.y;
	y = L.z*R.x - L.x*R.z;
	z = L.x*R.y - L.y*R.x;
	return *this;
}

//-----------------------------------------------------------------------------

inline double Vector3d::Distance  (const Vector3d &V) const
{
	return (double)sqrt( DistanceSqr(V) );
}

inline double Vector3d::DistanceSqr (const Vector3d &V) const
{
	return (*this-V).LengthSqr();
}

//-----------------------------------------------------------------------------

inline double Vector3d::Length  () const
{
	return (double)sqrt( LengthSqr() );
}

inline double Vector3d::LengthSqr () const
{
	return (x*x + y*y + z*z);
}

//-----------------------------------------------------------------------------

/*inline const Vector3d & Vector3d::Randomise( double scaleFac )
{
	double k = scaleFac * 2.0*(double)RAND_MAX;
	x = k*(double)rand() - scaleFac;
	y = k*(double)rand() - scaleFac;
	z = k*(double)rand() - scaleFac;
	return *this;
}*/

//-----------------------------------------------------------------------------

inline const Vector3d & Vector3d::Zero()
{
	x=0.0;
	y=0.0;
	z=0.0;
	return *this;
}

//-----------------------------------------------------------------------------

inline const Vector3d & Vector3d::Invert()
{
	return Invert(*this);
}

inline const Vector3d & Vector3d::Invert( const Vector3d &v )
{
	x = -v.x;	
	y = -v.y;	
	z = -v.z;	
	return *this;
}

//-----------------------------------------------------------------------------

inline const Vector3d & Vector3d::Normalise()
{
	return Normalise(*this);
}

inline const Vector3d & Vector3d::Normalise( const Vector3d &V )
{
	double r = Length();
	if (r!=0.0)				// guard against divide by zero
		return *this/=r;	// normalise and return
	else
		return Zero();		// zero vector in place, and return
}

//-----------------------------------------------------------------------------


inline bool Vector3d::IsZero  (double Tolerance) const
{
	return (LengthSqr() <= Tolerance*Tolerance);
}

inline bool Vector3d::IsUnit (double Tolerance) const
{
	return fabs(Length() - 1.0) <= Tolerance;
}

inline bool Vector3d::IsEqual(const Vector3d &V, double Tolerance) const
{
	return Vector3d().Subtract(*this, V).IsZero();
}

//-----------------------------------------------------------------------------

inline Vector3d operator * (double d, const Vector3d &v) { return v*d; }

//-----------------------------------------------------------------------------
