#include "Vec3d.h"

Vec3d::Vec3d()
{
	x = 0;
	y = 0;
	z = 0;
	changes=true;
}

Vec3d::Vec3d(double tmp_x=0, double tmp_y=0,double tmp_z=0){
	x=tmp_x;
	y=tmp_y;
	z=tmp_z;
	changes=true;
}

Vec3d& Vec3d::operator=(const Vec3d& rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	//assignment operator
	this->changes=rhs.changes;
	this->hX=rhs.hX;
	this->hY=rhs.hY;
	this->hZ=rhs.hZ;
	this->len=rhs.len;
	this->x=rhs.x;
	this->y=rhs.y;
	this->z=rhs.z;
	return *this;
}
double Vec3d::length(){
	if(changes){
		len=std::sqrt(x*x+y*y+z*z);
		changes=false;
	}
	return len;
}

void Vec3d::setX(double x1){
	x = x1;
	changes=true;
}
void Vec3d::setY(double y1){
	y = y1;
	changes=true;
}
void Vec3d::setZ(double z1){
	z = z1;
	changes=true;
}
double Vec3d::getX(){
	return x;
}
double Vec3d::getY(){
	return y;
}
double Vec3d::getZ(){
	return z;
}

void Vec3d::setXYZ(double x1, double y1, double z1){
	x = x1;
	y = y1;
	z = z1;
	changes=true;
}
Vec3d Vec3d::operator-() const{
	return Vec3d(-x, -y, -z);
}
Vec3d Vec3d::operator+() const{
	return Vec3d(x, y, -z);
}
//___________________CONSTRUCTER___________________
Vec3d make_Vec3d(double a, double b, double c){
	return Vec3d(a, b, c);
}
//____________________MULTIPLY____________________
Vec3d operator*(const Vec3d &f, const double k){
	return Vec3d(f.x * k , f.y * k, f.z * k);
}
Vec3d operator*(const double k, const Vec3d &f){
	return Vec3d(f.x * k , f.y * k, f.z * k);
}
Vec3d operator*=(const Vec3d &f, const double k){
	return Vec3d(f.x * k , f.y * k, f.z * k);
}
//_____________________ADDING_____________________
Vec3d operator+(const Vec3d &f, const Vec3d &s){
	return Vec3d(f.x + s.x, f.y + s.y, f.z + s.z);
}
Vec3d operator+=(const Vec3d &f, const Vec3d &s){
	return Vec3d(f.x + s.x, f.y + s.y, f.z + s.z);
}
//__________________SUBSTRACTING__________________
Vec3d operator-(const Vec3d &f, const Vec3d &s){
	return Vec3d(f.x - s.x, f.y - s.y, f.z - s.z);
}
Vec3d operator-=(const Vec3d &f, const Vec3d &s){
	return Vec3d(f.x - s.x, f.y - s.y, f.z - s.z);
}
//_____________________SCALAR_____________________
double scalar(const Vec3d &f, const Vec3d &s){
	return (f.x * s.x + f.y * s.y+ f.z * s.z);
}
//_____________________COS&SIN_____________________
double cos_Vec3d(Vec3d &f, Vec3d &s){
	return scalar(f, s)/(f.length()*s.length());
}
//__________________CROSS_PRODUCT__________________
Vec3d CrossProduct(Vec3d &a, Vec3d &b){
	Vec3d c(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	return c;
}
