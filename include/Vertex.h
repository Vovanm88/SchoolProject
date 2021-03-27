#ifndef Vertex_H
#define Vertex_H
#include <cmath>


class mVertex
{
	public:
		mVertex();
		mVertex(double tmp_x, double tmp_y,double tmp_z);
		mVertex& operator=(const mVertex& other);

		double x, y, z;
		friend mVertex NormalizeToVectorPoint(mVertex &v1, mVertex &v2);
		friend double Length(mVertex &v1, mVertex &v2);
		friend mVertex make_mVertex(double a, double b, double c);
};

#endif // Vertex_H
