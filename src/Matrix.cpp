#include <vector>
#include <cmath>
#include "Matrix.h"


std::vector <std::vector <double> >GetTurnMatrix(double angle){
	std::vector <std::vector <double> > Mtx(2, std::vector<double>(2, 0));
	Mtx[0][0]=std::cos(angle); Mtx[1][0]=-std::sin(angle);
	Mtx[0][1]=std::sin(angle); Mtx[1][1]= std::cos(angle);

	return Mtx;
}
Vec2d MultiplyWithMatrix(Vec2d vec, std::vector <std::vector <double> > matrix){
	return Vec2d(vec.getX()*matrix[0][0]+vec.getY()*matrix[1][0], vec.getX()*matrix[0][1]+vec.getY()*matrix[1][1]);
}
Vec2d TurnIt(Vec2d vec, double angle){
	std::vector <std::vector <double> > Matrix=GetTurnMatrix(angle);

	Vec2d ret=MultiplyWithMatrix(vec, Matrix);

	return ret;
}
