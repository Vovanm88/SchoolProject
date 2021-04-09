#include "Vec2d.h"

Vec2d::Vec2d()
{
	//ctor
	x = 0;
	y = 0;
}

Vec2d::Vec2d(double tmp_x=0, double tmp_y=0){
	x=tmp_x;
	y=tmp_y;
}

Vec2d& Vec2d::operator=(const Vec2d& rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	//assignment operator
	this->changes=rhs.changes;
	this->hX=rhs.hX;
	this->hY=rhs.hY;
	this->len=rhs.len;
	this->x=rhs.x;
	this->y=rhs.y;
	return *this;
}

double Vec2d::length(){
	if(changes){
		len=std::sqrt(x*x+y*y);
		changes=0;
	}
	return len;
}

void Vec2d::setX(double x1){
	x = x1;
	changes=1;
}
void Vec2d::setY(double y1){
	y = y1;
	changes=1;
}
double Vec2d::getX(){
	return x;
}
double Vec2d::getY(){
	return y;
}

void Vec2d::setXY(double x1, double y1){
	x = x1;
	y = y1;
	changes=1;
}
Vec2d Vec2d::operator-() const{
	return Vec2d(-x, -y);
}
Vec2d Vec2d::operator+() const{
	return Vec2d(x, y);
}

//___________________CONSTRUCTER___________________
Vec2d make_Vec2d(double a, double b){
	return Vec2d(a, b);
}
//____________________MULTIPLY____________________
Vec2d operator*(const Vec2d &f, const double k){
	return Vec2d(f.x * k , f.y * k);
}
Vec2d operator*=(const Vec2d &f, const double k){
	return Vec2d(f.x * k , f.y * k);
}
//_____________________ADDING_____________________
Vec2d operator+(const Vec2d &f, const Vec2d &s){
	return Vec2d(f.x + s.x, f.y + s.y);
}
Vec2d operator+=(const Vec2d &f, const Vec2d &s){
	return Vec2d(f.x + s.x, f.y + s.y);
}
//__________________SUBSTRACTING__________________
Vec2d operator-(const Vec2d &f, const Vec2d &s){
	return Vec2d(f.x - s.x, f.y - s.y);
}
Vec2d operator-=(const Vec2d &f, const Vec2d &s){
	return Vec2d(f.x - s.x, f.y - s.y);
}
//_____________________SCALAR_____________________
double scalar(const Vec2d &f, const Vec2d &s){
	return (f.x * s.x + f.y * s.y);
}
//_____________________COS&SIN_____________________
double cos_Vec2d(Vec2d &f, Vec2d &s){
	return scalar(f, s)/(f.length()*s.length());
}
double sin_Vec2d(Vec2d &f, Vec2d &s){
	return ((f.x*s.y)-(f.y*s.x))/(f.length()*s.length());
}
//____________________ANGLE of OX____________________
double angle_Vec2d(Vec2d &f){
	double s,c;
	Vec2d Ox(1, 0);
	s = sin_Vec2d(f, Ox);
	c = cos_Vec2d(f, Ox);
	double radAngle=0;
	if(s>=0 && c>=0){
		radAngle=std::acos(c);
	}
	if(s>=0 && c<0){
		radAngle=std::acos(c);
	}
	if(s<0 && c<0){
		radAngle=std::acos(c)+(3.1415926535/2);
	}
	if(s<0 && c>0){
		radAngle=std::acos(c)+(3*3.1415926535/2);
	}
	return radAngle;
}
