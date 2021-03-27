#ifndef SIMULATIONTHREAD_H_INCLUDED
#define SIMULATIONTHREAD_H_INCLUDED
#include <Vec2d.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <MyTimer.h>
#include <chrono>
#include <thread>
#include <SimulationThread.h>
#include <RenderThread.h>
const double EPSs=0.0000001;

struct ObjInfo{
	Vec2d pos;
	Vec2d velocity;
	double k;
	double g;
	double m;
};
void WriteDataToFile(std::stringstream &s);
void clearfile();
double MyMax(double m1, double m2);
double MyMin(double m1, double m2);
double MyAbs(double m1);
double Est(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed);
int collisionTest(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed);
void simThread(Vec2d &pos, ObjInfo ball, int &isEnabled, Vec2d &brd);

#endif // SIMULATIONTHREAD_H_INCLUDED
