// Copyright (C) 2002-2006 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_LINE_2D_H_INCLUDED__
#define __IRR_LINE_2D_H_INCLUDED__

#include "irrTypes.h"
#include "vector2d.h"

namespace irr
{
namespace core
{

//! 2D line between two points with intersection methods.
template <class T>
class line2d
{
	public:

		line2d() : start(0,0), end(1,1) {};
		line2d(T xa, T ya, T xb, T yb) : start(xa, ya), end(xb, yb) {};
		line2d(const vector2d<T>& start, const vector2d<T>& end) : start(start), end(end) {};
		line2d(const line2d<T>& other) : start(other.start), end(other.end) {};

		// operators

		line2d<T> operator+(const vector2d<T>& point) const { return line2d<T>(start + point, end + point); };
		line2d<T>& operator+=(const vector2d<T>& point) { start += point; end += point; return *this; };

		line2d<T> operator-(const vector2d<T>& point) const { return line2d<T>(start - point, end - point); };
		line2d<T>& operator-=(const vector2d<T>& point) { start -= point; end -= point; return *this; };

		bool operator==(const line2d<T>& other) const { return (start==other.start && end==other.end) || (end==other.start && start==other.end);};
		bool operator!=(const line2d<T>& other) const { return !(start==other.start && end==other.end) || (end==other.start && start==other.end);};

		// functions

		void setLine(const T& xa, const T& ya, const T& xb, const T& yb){start.set(xa, ya); end.set(xb, yb);}
		void setLine(const vector2d<T>& nstart, const vector2d<T>& nend){start.set(nstart); end.set(nend);}
		void setLine(const line2d<T>& line){start.set(line.start); end.set(line.end);}

		//! Returns length of line
		//! \return Returns length of line.
		f64 getLength() const { return start.getDistanceFrom(end); };

		//! Returns the vector of the line.
		//! \return Returns the vector of the line.
		vector2d<T> getVector() const { return vector2d<T>(start.X - end.X, start.Y - end.Y); };

		//! Tests if this line intersects with an other line.
		//! \param l: Other line to test intersection with.
		//! \param out: If there is an intersection, the location of the intersection will
		//! be stored in this vector.
		//! \return Returns true if there is an intersection, false if not.
		bool intersectWith(const line2d<T>& l, vector2d<T>& out) const
		{
			bool found=false;

			f32 a1,a2,b1,b2;

			// calculate slopes, deal with infinity
			if (end.X-start.X == 0)
				b1 = (f32)1e+10;
			else
				b1 = (end.Y-start.Y)/(end.X-start.X);
			if (l.end.X-l.start.X == 0)
				b2 = (f32)1e+10;
			else
				b2 = (l.end.Y-l.start.Y)/(l.end.X-l.start.X);

			// calculate position
			a1 = start.Y   - b1 *  start.X;
			a2 = l.start.Y - b2 * l.start.X;
			out.X = - (a1-a2)/(b1-b2);
			out.Y = a1 + b1*out.X;

			// did the lines cross?
			if ( (start.X-out.X) *(out.X-end.X)  >=0 &&
				(l.start.X-out.X)*(out.X-l.end.X)>=0 &&
				(start.Y-out.Y)  *(out.Y-end.Y)  >=0 &&
				(l.start.Y-out.Y)*(out.Y-l.end.Y)>=0 )
			{
				found = true;
			}
			return found;
		}

		//! Returns unit vector of the line.
		//! \return Returns unit vector of this line.
		vector2d<T> getUnitVector()
		{
			T len = (T)(1.0 / getLength());
			return vector2d<T>((end.X - start.X) * len, (end.Y - start.Y) * len);
		}

		f64 getAngleWith(const line2d<T>& l)
		{
			vector2d<T> vect = getVector();
			vector2d<T> vect2 = l.getVector();
			return vect.getAngleWith(vect2);
		}

		// member variables

		vector2d<T> start;
		vector2d<T> end;
};

	//! Typedef for a f32 line.
	typedef line2d<f32> line2df;
	//! Typedef for an integer line.
	typedef line2d<s32> line2di;

} // end namespace core
} // end namespace irr

#endif

