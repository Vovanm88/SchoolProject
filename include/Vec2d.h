#ifndef VEC2D_H
#define VEC2D_H
#include <cmath>
class Vec2d{
	public:
		Vec2d(double tmp_x, double tmp_y);
		Vec2d();
		Vec2d& operator=(const Vec2d& rhs);
		double length();
		void setX(double x1);
		void setY(double y1);
		double getX();
		double getY();
		void setXY(double x1, double y1);
		Vec2d operator-() const;
		Vec2d operator+() const;

		friend Vec2d operator*(const Vec2d &f, const double k);
		friend Vec2d operator*=(const Vec2d &f, const double k);

		friend Vec2d operator+(const Vec2d &f, const Vec2d &s);
		friend Vec2d operator+=(const Vec2d &f, const Vec2d &s);

		friend Vec2d operator-(const Vec2d &f, const Vec2d &s);
		friend Vec2d operator-=(const Vec2d &f, const Vec2d &s);

		friend double scalar(const Vec2d &f, const Vec2d &s);
		friend double angle_Vec2d(Vec2d &f);
		friend double cos_Vec2d(Vec2d &f, Vec2d &s);
		friend double sin_Vec2d(Vec2d &f, Vec2d &s);
		friend Vec2d make_Vec2d(double a, double b);
	private:
		double x, y;
		double len=0;
		double hX=0;
		double hY=0;
		bool changes=true;
};


#endif // VEC2D_H
