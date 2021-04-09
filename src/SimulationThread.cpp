#include "SimulationThread.h"

void configReadSim(int &key, double &kTrK, double &TickTime){
	double X, Y;
	std::ifstream in("config.dat");
    if (in.is_open())
    {
		in>>X>>Y>>key>>kTrK>>TickTime;
    }
    in.close();
}
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
	filename = fname.str();
	flout.open(filename, std::ios_base::trunc);
	if(!flout.is_open()){
		std::cout<<"ERROR";
	}
	flout.close();
	return;
}
std::string DotToComma(std::string input){
	std::string output;
	for(auto el: input){
		if(el!='.')
			output.push_back(el);
		else
			output.push_back(',');
	}
	return output;
}
void ExcelImport(){
	std::ofstream flout("ExcelData.csv", std::ios_base::trunc);
	if(!flout.is_open()){
		std::cout<<"ERROR"<<'\n';
	}

	std::ifstream in("Data.txt");
    if (!in.is_open()){
		std::cout<<"ERROR"<<'\n';
    }

	flout<<"t;v;a;Energy(K);Energy(P);X;Y"<<'\n';
	double fst, tst, vst, nst, ast, Ek, Ep, datX, datY;
	while(in>>tst>>vst>>ast>>fst>>nst>>Ek>>Ep>>datX>>datY){
		std::stringstream fl;
		fl<<tst<<";"<<vst<<";"<<ast<<";"<<Ek<<";"<<Ep<<";"<<datX<<";"<<datY;
		std::string rep=fl.str();
		flout<<DotToComma(rep)<<'\n';
		fl.clear();
	}
    in.close();
    flout.close();
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
void PrepareData(Vec2d &velocity, Vec2d &brd, Vec2d &posMetr, Vec2d &acceleration, double tst, Vec2d &F, Vec2d &N, double m, double g, double TickTime){
	double fst, nst, ast, Ek, Ep, vel, datX, datY;
	vel=velocity.length();
	Ek=m*vel*vel*0.5;
	Ep=m*g*((brd.getY()-20)/100-posMetr.getY());
	nst=N.getY();
	fst=F.length()*TickTime;
	ast=acceleration.length()*TickTime;
	datX=posMetr.getX();
	datY=6-posMetr.getY();
	datX=(double)((int)(datX*1000))/1000;
	datY=(double)((int)(datY*1000))/1000;
	std::stringstream fl;
	fl<<tst<<" "<<vel<<" "<<ast<<" "<<fst<<" "<<nst<<" "<<Ek<<" "<<Ep<<" "<<datX<<" "<<datY;
	WriteDataToFile(fl);
}

void simThread(Vec2d &pos, ObjInfo ball, int &isEnabled, Vec2d &brd){
	Vec2d posMetr, velocity, acceleration, P, F, N, K;
	double g, m, k;

	posMetr=ball.pos;
	velocity=ball.velocity;
	g=ball.g;
	m=ball.m;
	k=ball.k;
	P.setY(g*m);

	double TickTime=0.01;
	double kTr=0.1;
	int isEWrt=0;
	configReadSim(isEWrt, kTr, TickTime);

	clearfile();
	MyTimer t1;
	double FrameTime=0;
	MyTimer t2;
	MyTimer t3;
	bool pause=false;
	int CPUBusy=0;
	double T=0;
	while(isEnabled>0){
		FrameTime=t1.elapsed();
		t1.reset();
		if(isEnabled==1 && pause){
			pause=false;
			t2.reset();
		}
		if(isEnabled==2 && !pause){
			pause=true;

		}
		if(!pause){
			N.setY(0);
			int colState = collisionTest(pos, 10.0, brd, velocity*TickTime);
			if(colState!=1){
				if(colState%3==0){
					if(MyAbs(velocity.getX())>EPSs){
						F.setX(-velocity.getX()*((k+1)*m/TickTime));
						N.setX(velocity.getX()/MyAbs(velocity.getX())*-0.005);
					}
				}else{
					F.setX(0);
				}
				if(colState%2==0){
					F.setY(-velocity.getY()*((k+1)*m/TickTime));
					if(MyAbs(velocity.getX())>EPSs)
						K.setX(-m*velocity.getX()/MyAbs(velocity.getX())*kTr);
				}else{
					F.setY(0);
					K.setX(0);
				}
				if(colState%2==0 && colState%4!=0){
						N.setY(-g*m*1.01);
				}else{
					N.setY(0);
				}
			}else{
				F.setXY(0,0);
				K.setX(0);
			}
			{
				T+=TickTime;
				acceleration=(F+N+P+K)*(1/m);
				velocity=velocity+(acceleration*TickTime);
				posMetr=posMetr+(velocity*TickTime);
				pos=posMetr*100;
				PrepareData(velocity, brd, posMetr, acceleration, T, F, N, m, g, TickTime);

			}
			if(FrameTime<25 && FrameTime>8){
				CPUBusy--;
			}else{
				CPUBusy++;
				if(CPUBusy>5 && t3.elapsed()<1000){
					t3.reset();
					std::cout<<"Внимание! Высокая нагрузка на ЦПУ"<<'\n';
				}
			}
			pos=posMetr*100;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(9));
	}
	if(isEWrt!=0){
		ExcelImport();
	}
}
