#ifndef MATRIX_H
#define MATRIX_H
//vector <vector <double> >GetTurnMatrix(double angle);
#include <Vec2d.h>
#include <Vec3d.h>
#include <Vertex.h>

std::vector <std::vector <double> >GetTurnMatrix(double angle);
Vec2d MultiplyWithMatrix(Vec2d vec, std::vector <std::vector <double> > matrix);
Vec2d TurnIt(Vec2d vec, double angle);
#endif // MATRIX_H
