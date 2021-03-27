#include "SimulationThread.h"

void WriteDataToFile(std::stringstream &s){
	std::ofstream flout;
	std::string filename;
	std::stringstream fname;
	std::string rep=s.str();
	fname<<"Data"<<".txt";
	filename = fname.str();
	flout.open(filename, std::ios_base::app);
	if(!flout.is_open()){
		std::cout<<"ERROR";
	}
	flout<<rep<<'\n';
	flout.close();
	return;
}
void clearfile(){
	std::ofstream flout;
	std::string filename;
	std::stringstream fname;
	fname<<"Data"<<".txt";
	//C:/C++/Pitone/
	filename = fname.str();
	flout.open(filename, std::ios_base::trunc);
	if(!flout.is_open()){
		std::cout<<"ERROR";
	}
	flout.close();
	return;
}
double MyMax(double m1, double m2){
	if(m1 >= m2){
		return m1;
	}else{
		return m2;
	}
}
double MyMin(double m1, double m2){
	if(m1 <= m2){
		return m1;
	}else{
		return m2;
	}
}
double MyAbs(double m1){
	if(m1 < 0){
		return -m1;
	}else{
		return m1;
	}
}
double Est(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed){
	double x1=pos.getX();
	double y1=pos.getY();
	double x2=pos.getX()+sz*2;
	double y2=pos.getY()+sz*2;
	double bx=bordersize.getX();
	double by=bordersize.getY();
	double dx=speed.getX();
	double dy=speed.getY();
	double distx1=-x1;
	double disty1=-y1;
	double distx2=bx-x2;
	double disty2=by-y2;
	double tx1=distx1/dx;
	double ty1=disty1/dy;
	double tx2=distx2/dx;
	double ty2=disty2/dy;
	return MyMin(MyMax(tx1, tx2), MyMax(ty1, ty2));
}

int collisionTest(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed){
	double x1=pos.getX()+speed.getX();
	double y1=pos.getY()+speed.getY();
	double x2=pos.getX()+speed.getX()+sz*2;
	double y2=pos.getY()+speed.getY()+sz*2;
	int ret=1;
	if(x2>=bordersize.getX()){
		ret*=3;
	}
	if(y2>=bordersize.getY()){
		ret*=2;
	}
	if(x1<=0){
		ret*= 9;
	}
	if(y1<=0){
		ret*= 4;
	}
	return ret;
}

void simThread(Vec2d &pos, ObjInfo ball, int &isEnabled, Vec2d &brd){
	Vec2d posMetr, velocity, acceleration, P, F, N, K;
	double kTr=0.1;
	double g, m, k;

	posMetr=ball.pos;
	velocity=ball.velocity;
	g=ball.g;
	m=ball.m;
	k=ball.k;
	P.setY(g*m);

	clearfile();
	MyTimer t1;
	double FrameTime=0;
	MyTimer t2;
	MyTimer t3;
	bool pause=false;
	int CPUBusy=0;
	double T=0;
	while(isEnabled>0){
		//std::cout<<"calc"<<'\n';
		FrameTime=t1.elapsed();
		t1.reset();
		//std::cout<<t1.elapsed();
		if(isEnabled==1 && pause){
			pause=false;
			t2.reset();
		}
		if(isEnabled==2 && !pause){
			pause=true;
			//t2.reset();
		}
		if(!pause){
			N.setY(0);
			double timeEst=Est(pos, 10.0, brd, velocity*0.01);
			int colState = collisionTest(pos, 10.0, brd, velocity*0.01);
			if(colState!=1){
				if(colState%3==0){
					if(MyAbs(velocity.getX())>EPSs){
						F.setX(-velocity.getX()*((k+1)*m/0.01));
						N.setX(velocity.getX()/MyAbs(velocity.getX())*-0.005);
					}
				}else{
					F.setX(0);
				}
				if(colState%2==0){
					F.setY(-velocity.getY()*((k+1)*m/0.01));
					//std::cout<<F.getY()<<'\n';
				}else{
					F.setY(0);
				}
				if(colState%2==0 && pos.getY()>100){
					N.setY(-g*m*1.05);
					//std::cout<<P.getY()<<'\n';
					if(MyAbs(velocity.getX())>EPSs)
						K.setX(-m*velocity.getX()/MyAbs(velocity.getX())*kTr);
				}else{
					N.setY(0);
					K.setX(0);
				}
			}else{
				F.setXY(0,0);
				K.setX(0);
			}

			if(FrameTime<25 && FrameTime>8){
				T+=0.01;
				acceleration=(F+N+P+K)*(1/m);
				velocity=velocity+(acceleration*0.01);
				posMetr=posMetr+(velocity*0.01);
				pos=posMetr*100;
				CPUBusy=0;
				double fst, tst, vst, nst, ast, Ek, Ep, vel;
				vel=velocity.length();
				Ek=m*vel*vel*0.5;
				Ep=m*g*(brd.getY()/100-posMetr.getY());
				tst=T;
				nst=N.getY();
				fst=F.length()*0.01;
				ast=acceleration.length()*0.01;
				vst=velocity.length();
				std::stringstream fl;
				fl<<tst<<" "<<vst<<" "<<ast<<" "<<fst<<" "<<nst<<" "<<Ek<<" "<<Ep;
				WriteDataToFile(fl);
			}else{
				CPUBusy++;
				if(CPUBusy>2 && t3.elapsed()<10000){
					t3.reset();
					std::cout<<"Внимание! Высокая нагрузка на ЦПУ"<<'\n';
				}
			}
			//pos.setXY(posMetr.getX()*100, brd.getY()-posMetr.getY()*100);
			pos=posMetr*100;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(9));
	}
}
