#ifndef FIGURES_H_INCLUDED
#define FIGURES_H_INCLUDED

std::vector <mVertex> RotateFg(std::vector<mVertex> Fig, double angle, Vec2d Biass);
Vec3d LinearFunctionByPoints(mVertex point1, mVertex point2);
bool IsLineCrosses(mVertex v1p1, mVertex v1p2, mVertex v2p1, mVertex v2p2);
bool IsLineCrosses(mVertex v1p1, mVertex v1p2, mVertex v2p1, mVertex v2p2);
bool Collision(std::vector <mVertex> &a1, std::vector <mVertex> &a2);
//Vec2d borderTest(Vec2d tested, Vec2d border);


#endif // FIGURES_H_INCLUDED
