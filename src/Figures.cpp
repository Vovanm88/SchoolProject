#include <cmath>
#include <vector>
#include <Vec2d.h>
#include <Vec3d.h>
#include <Vertex.h>
#include <Matrix.h>
#include "Figures.h"

const double EPS=0.0000001;
std::vector <mVertex> RotateFg(std::vector<mVertex> Fig, double angle, Vec2d Biass){
	std::vector <mVertex> out;
	for(mVertex &el: Fig){
		Vec2d vc(el.x-Biass.getX(), el.y-Biass.getY());
		vc=TurnIt(vc, angle);
		mVertex vu(vc.getX()+Biass.getX(), vc.getY()+Biass.getY(), 0);
		out.push_back(vu);
	}
	return out;
}
Vec3d LinearFunctionByPoints(mVertex point1, mVertex point2){
	double x1=point1.x;
	double y1=point1.y;
	double x2=point2.x;
	double y2=point2.y;
	Vec3d v1(x1, y1, 1);
	Vec3d v2(x2, y2, 1);
	return CrossProduct(v1, v2);;
}
Vec2d CrossPoint(Vec3d &line1, Vec3d &line2, bool &err){
	// find cross point of lines
	Vec3d v1 = CrossProduct(line1, line2);
	if(std::abs(v1.getX())<EPS && std::abs(v1.getY())<EPS && std::abs(v1.getZ())<EPS){
		Vec2d v3(0, 0);
		err=false;
		return v3;
	}
	Vec2d v3(0, 0);
	// find point of crossing
	if(v1.getZ()!=0){
		Vec2d v2(v1.getX()/v1.getZ(), v1.getY()/v1.getZ());
		err=false;
		return v2;
	}else{
		err=false;
		return Vec2d(v1.getX(), v1.getY());
	}
	err=true;
	return Vec2d(0,0);
}
bool IsLineCrosses(mVertex v1p1, mVertex v1p2, mVertex v2p1, mVertex v2p2){
	Vec3d l1 = LinearFunctionByPoints(v1p1, v1p2);
	Vec3d l2 = LinearFunctionByPoints(v2p1, v2p2);
	bool err=false;
	Vec2d vtmp = CrossPoint(l1, l2, err);
	mVertex point(vtmp.getX(), vtmp.getY(), 0);

	bool inF, inS;
	if(!err){
		mVertex v1l1=NormalizeToVectorPoint(point, v1p1);
		mVertex v2l1=NormalizeToVectorPoint(point, v1p2);
		Vec2d v2d1(v1l1.x, v1l1.y);
		Vec2d v2d2(v2l1.x, v2l1.y);
		double a1 = scalar(v2d1, v2d2);
		if(a1<=EPS){
			inF=true;
		}else{
			inF=false;
		}
		mVertex v1l2=NormalizeToVectorPoint(point, v2p1);
		mVertex v2l2=NormalizeToVectorPoint(point, v2p2);
		Vec2d v2d3(v1l2.x, v1l2.y);
		Vec2d v2d4(v2l2.x, v2l2.y);
		double a2 = scalar(v2d3, v2d4);
		if(a2<=EPS){
			inS=true;
		}else{
			inS=false;
		}
		if(inF && inS) return true;
	}
	return false;
}
bool Collision(std::vector <mVertex> &a1, std::vector <mVertex> &a2){
	for(std::vector<mVertex>::iterator el1=a1.begin(); el1!=a1.end(); ++el1){
		std::vector<mVertex>::iterator nextEl1=el1;
		++nextEl1;
		if(nextEl1 == a1.end()){
			nextEl1=a1.begin();
		}
		for(std::vector<mVertex>::iterator el2=a2.begin(); el2!=a2.end(); ++el2){
			std::vector<mVertex>::iterator nextEl2=el2;
			++nextEl2;
			if(nextEl2 == a2.end()){
				nextEl2=a2.begin();
			}
			if(IsLineCrosses(*el2, *nextEl2, *el1, *nextEl1)){
				return true;
			}
		}
	}
	return false;
}

/*
Vec2d borderTest(Vec2d tested, Vec2d border){
	double xc = border.getX();
	double yc = border.getY();
	double x0 = 0;
	double y0 = 0;

	double xt=tested.getX();
	double yt=tested.getY();

	double xr=0;
	double yr=0;
	if(xt>xc){
		xr=xc-xt;
	}
	if(xt<x0){
		xr=x0-xt;
	}
	if(yt>yc){
		yr=yc-yt;
	}
	if(yt<y0){
		yr=y0-yt;
	}
	return Vec2d(xr, yr);
}
*/
