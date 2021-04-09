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
void configReadSim(int &key, double &kTrK);
void WriteDataToFile(std::stringstream &s);
void clearfile();
std::string DotToComma(std::string input);
void ExcelImport();
double MyMax(double m1, double m2);
double MyMin(double m1, double m2);
double MyAbs(double m1);
int collisionTest(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed);
void PrepareData(Vec2d &velocity, Vec2d &brd, Vec2d &posMetr, Vec2d &acceleration, double tst, Vec2d &F, Vec2d &N, double m, double g, double TickTime);
void simThread(Vec2d &pos, ObjInfo ball, int &isEnabled, Vec2d &brd);

#endif // SIMULATIONTHREAD_H_INCLUDED
