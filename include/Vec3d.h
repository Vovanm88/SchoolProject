#ifndef VEC3D_H
#define VEC3D_H
#include <cmath>

class Vec3d
{
	public:
		Vec3d();
		Vec3d(double tmp_x, double tmp_y,double tmp_z);
		Vec3d& operator=(const Vec3d& rhs);
		double length();
		void setX(double x1);
		void setY(double y1);
		void setZ(double z1);
		double getX();
		double getY();
		double getZ();
		void setXYZ(double x1, double y1, double z1);
		Vec3d operator-() const;
		Vec3d operator+() const;
		friend Vec3d make_Vec3d(double a, double b, double c);
		friend Vec3d operator*(const Vec3d &f, const double k);
		friend Vec3d operator*(const double k, const Vec3d &f);
		friend Vec3d operator*=(const Vec3d &f, const double k);
		friend Vec3d operator+(const Vec3d &f, const Vec3d &s);
		friend Vec3d operator+=(const Vec3d &f, const Vec3d &s);
		friend Vec3d operator-(const Vec3d &f, const Vec3d &s);
		friend Vec3d operator-=(const Vec3d &f, const Vec3d &s);
		friend double scalar(const Vec3d &f, const Vec3d &s);
		friend double cos_Vec3d(Vec3d &f, Vec3d &s);
		friend Vec3d CrossProduct(Vec3d &a, Vec3d &b);
	private:
		double x, y, z;
		double len=0;
		double hX=0;
		double hY=0;
		double hZ=0;
		bool changes=true;
};

#endif // VEC3D_H
