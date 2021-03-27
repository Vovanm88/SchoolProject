#include "Vertex.h"

mVertex::mVertex()
{
	x=0;
	y=0;
	z=0;
}
mVertex::mVertex(double tmp_x=0, double tmp_y=0,double tmp_z=0){
	x=tmp_x;
	y=tmp_y;
	z=tmp_z;
}


mVertex& mVertex::operator=(const mVertex& rhs)
{
	if (this == &rhs) return *this;
	this->x=rhs.x;
	this->y=rhs.y;
	this->z=rhs.z;
	return *this;
}

mVertex NormalizeToVectorPoint(mVertex &v1, mVertex &v2){
	return mVertex(v2.x-v1.x,v2.y-v1.y,v2.z-v1.z);
}
double Length(mVertex &v1, mVertex &v2){
	mVertex v3 = NormalizeToVectorPoint(v1, v2);
	return std::sqrt(v3.x*v3.x + v3.y*v3.y + v3.z*v3.z);
}
mVertex make_mVertex(double a, double b, double c){
	return mVertex(a, b, c);
}
