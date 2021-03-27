#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Vec2d.h>
#include <Vec3d.h>
#include <Vertex.h>
#include <Figures.h>
#include <MyTimer.h>


#include <iostream>
#include <vector>
#include <windows.h>
#include <sstream>
#include <cmath>

#include <chrono>
#include <thread>
#include <mutex>

#include <string>
#include <fstream>
#include <sstream>
#include <string>

void renderingThread(sf::RenderWindow &window, std::mutex &mtx, Vec2d &pos){
	// activate the window's context
	window.setActive(true);
	// the rendering loop
	while (window.isOpen()){
		// draw...
		mtx.lock();
		sf::CircleShape ball(10.f);
		ball.setPosition(sf::Vector2f(pos.getX(), pos.getY()));
		ball.setFillColor(sf::Color(240, 240, 240));
		window.clear(sf::Color::Black);
		window.draw(ball);
		// end the current frame
		std::cout<<"render"<<'\n';
		window.display();
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void NrenderingThread(sf::RenderWindow &window, std::mutex &mtx, Vec2d &pos){
	// activate the window's context
	window.setActive(true);
	// the rendering loop
		// draw...
		mtx.lock();
		sf::CircleShape ball(10.f);
		ball.setPosition(sf::Vector2f(pos.getX(), pos.getY()));
		ball.setFillColor(sf::Color(240, 240, 240));
		window.clear(sf::Color::Black);
		window.draw(ball);
		// end the current frame
		//std::cout<<"render"<<'\n';
		window.display();
		mtx.unlock();
}
/*
void simThread(sf::RenderWindow &window, std::mutex &mtx, Vec2d &pos){
	Vec2d pos, velocity, acceleration, P, F, N;
	double g, m, k;
	basicInput(pos, velocity, k, g, m);
	P.setY(g*m);
	sf::RenderWindow w1(sf::VideoMode(1000, 600), "Ball's kinematic sim");

	std::mutex mtx;


	bool pause=false;
	MyTimer t1;
	clearfile();
	double spacePressed=t1.elapsed();
	double FrameTime=0;
	double FrameStart=t1.now();
	MyTimer t2;
	w1.setActive(false);
	std::thread threadRender(&renderingThread, std::ref(w1), std::ref(mtx), std::ref(pos));
	threadRender.join();
	std::thread threadSimulation(&renderingThread, std::ref(w1), std::ref(mtx), std::ref(pos));
	threadSimulation.join();
	while(w1.isOpen()){
		std::cout<<"calc"<<'\n';
		FrameTime=t1.now()-FrameStart;
		FrameStart=t1.now();
		//std::cout<<t1.elapsed();
		sf::Event ev;

		while(w1.pollEvent(ev)){
			if(ev.type ==  sf::Event::Closed){
				w1.close();
			}
			if (ev.key.code == sf::Keyboard::Escape){
				w1.close();
			}
			if (ev.key.code == sf::Keyboard::Space){
				if(t1.elapsed()-spacePressed>=500){
					pause=!pause;
					spacePressed=t1.elapsed();
					t2.reset();
				}
			}
		}

		if(!pause){
			N.setY(0);
			if(testCollision(pos, 10.f, Vec2d(1000, 600), (velocity*(FrameTime/1000.0)))){
				if(XColl(pos, 10.f, Vec2d(1000, 600), (velocity*(FrameTime/1000.0)))){
					F.setX(-velocity.getX()*((k+1)*m));

				}else{
					F.setX(0);
				}
				if(YColl(pos, 10.f, Vec2d(1000, 600), (velocity*(FrameTime/1000.0)))){
					F.setY(-velocity.getY()*((k+1)*m));
					//std::cout<<F.getY()<<'\n';
				}else{
					F.setY(0);
				}
				if(YCollN(pos, 10.f, Vec2d(1000, 600), (velocity*(FrameTime/1000.0)))){
					N.setY(-g*m);
					//std::cout<<P.getY()<<'\n';
				}else{
					N.setY(0);
				}
			}else{
				F.setXY(0,0);
			}
			acceleration=(F+N+P)*(1/m);
			velocity=velocity+(acceleration);

			pos=pos+(velocity*(FrameTime/1000.0));
			double fst, tst, vst, nst, ast, Ek, Ep;
			Ek=m*(velocity.length()/100)*(velocity.length()/100)*0.5;
			Ep=m*g*(600-(pos.getY()-10))/100;
			tst=t2.elapsed();
			nst=N.getY();
			fst=F.getY();
			ast=acceleration.getY();
			vst=velocity.getY();
			std::stringstream fl;
			fl<<tst<<" "<<vst/100<<" "<<ast<<" "<<fst<<" "<<nst<<" "<<Ek<<" "<<Ep;
			WriteDataToFile(fl);
		}
	}
}
*/

//Vec2d RotateVec2d(Vec2d)
const double EPS=0.0000001;
/*
double FrameTimeCorrection(double time){

}
*/
void WriteDataToFile(std::stringstream &s){
	std::ofstream flout;
	std::string filename;
	std::stringstream fname;
	std::string rep=s.str();
	fname<<"C:/C++/Pitone/Data"<<".txt";
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
	fname<<"C:/C++/Pitone/Data"<<".txt";
	filename = fname.str();
	flout.open(filename, std::ios_base::trunc);
	if(!flout.is_open()){
		std::cout<<"ERROR";
	}
	flout.close();
	return;
}

void basicInput(Vec2d &p, Vec2d &v, double &k, double &g, double &m){
	double x, y;
	std::setlocale(LC_ALL, "Russian");
	std::cout<<"Введите начальное положение мячика"<<'\n'<<"по оси x(от 0 до 10 м): ";
	std::cin>>x;
	if(x<0) x=0;
	if(x>10) x=10;
	x=x*100;
	std::cout<<"по оси y(от 0(пол) до 6м): ";
	std::cin>>y;
	y=6-y;
	if(y<0) y=0;
	if(y>6) y=6;
	y=y*100;
	p.setXY(x, y);
	std::cout<<'\n'<<"Начальную скорость мячика по осям, м/с:"<<'\n'<<"по оси x: ";
	std::cin>>x;
	std::cout<<"по оси y: ";
	std::cin>>y;
	y=-y;
	x=x*(100.0);
	y=y*(100.0);
	v.setXY(x, y);
	std::cout<<'\n'<<"Коэффициент упругости (от 1 - абсолютно упрогий до 0 - абсолютно неупругий): ";
	std::cin>>k;
	if(k>1) k=1;
	if(k<0) k=0;
	std::cout<<'\n'<<"Значение универсальной гравитационной постоянной, м/с^2: ";
	std::cin>>g;
	g=g*(100.0);
	std::cout<<'\n'<<"Масса, кг: ";
	std::cin>>m;
	if(m<0) m=-m;
	if(m<0.001) m=0.001;
	std::cout<<'\n'<<"Нажмите пробел для старта";
}
bool testCollision(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed){
	double x1=pos.getX();
	double y1=pos.getY();
	double x2=pos.getX()+sz*2;
	double y2=pos.getY()+sz*2;
	if(x2+speed.getX()>=bordersize.getX()){
		return true;
	}
	if(y2+speed.getX()>=bordersize.getY()){
		return true;
	}
	if(x1+speed.getY()<=0){
		return true;
	}
	if(y1+speed.getY()<=0){
		return true;
	}
	return false;
}
bool XColl(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed){
	double x1=pos.getX();
	double x2=pos.getX()+sz*2;
	if(x2+speed.getX()>=bordersize.getX()){
		return true;
	}
	if(x1+speed.getX()<=0){
		return true;
	}
	return false;
}
bool YColl(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed){
	double y1=pos.getY();
	double y2=pos.getY()+sz*2;
	if(y2+speed.getY()>=bordersize.getY()){
		return true;
	}
	if(y1+speed.getY()<=0){
		return true;
	}
	return false;
}
bool YCollN(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed){
	double y2=pos.getY()+sz*2;
	if(y2+speed.getY()>=bordersize.getY()){
		return true;
	}
	return false;
}
int collisionTest(Vec2d pos, double sz, Vec2d bordersize, Vec2d speed){
	double x1=pos.getX()+speed.getX();
	double y1=pos.getY()+speed.getY();
	double x2=pos.getX()+speed.getX()+sz*2;
	double y2=pos.getY()+speed.getY()+sz*2;
	int ret=0;
	if(x2>=bordersize.getX()){
		ret=2;
	}
	if(y2>=bordersize.getY()){
		ret=3;
	}
	if(x1+speed.getY()<=0){
		ret = 9;
	}
	if(y1+speed.getY()<=0){
		ret = 4;
	}
	return ret;
}
int main(){
	Vec2d pos, velocity, acceleration, P, F, N;
	double g, m, k;
	basicInput(pos, velocity, k, g, m);
	P.setY(g*m);
	sf::RenderWindow w1(sf::VideoMode(1000, 600), "Ball's kinematic sim");

	std::mutex mtx;


	bool pause=false;
	MyTimer t1;
	clearfile();
	double spacePressed=t1.elapsed();
	double FrameTime=0;
	double FrameStart=t1.now();
	MyTimer t2;
	w1.setActive(false);
	std::thread threadRender(&renderingThread, std::ref(w1), std::ref(mtx), std::ref(pos));
	threadRender.join();
	//std::thread threadSimulation(&renderingThread, std::ref(w1), std::ref(mtx), std::ref(pos));
//	threadSimulation.join();
	while(w1.isOpen()){
		std::cout<<"calc"<<'\n';
		FrameTime=t1.now()-FrameStart;
		FrameStart=t1.now();
		//std::cout<<t1.elapsed();
		sf::Event ev;

		while(w1.pollEvent(ev)){
			if(ev.type ==  sf::Event::Closed){
				w1.close();
			}
			if (ev.key.code == sf::Keyboard::Escape){
				w1.close();
			}
			if (ev.key.code == sf::Keyboard::Space){
				if(t1.elapsed()-spacePressed>=500){
					pause=!pause;
					spacePressed=t1.elapsed();
					t2.reset();
				}
			}
		}

		if(!pause){
			N.setY(0);
			if(testCollision(pos, 10.f, Vec2d(1000, 600), (velocity*(FrameTime/1000.0)))){
				if(XColl(pos, 10.f, Vec2d(1000, 600), (velocity*(FrameTime/1000.0)))){
					F.setX(-velocity.getX()*((k+1)*m));

				}else{
					F.setX(0);
				}
				if(YColl(pos, 10.f, Vec2d(1000, 600), (velocity*(FrameTime/1000.0)))){
					F.setY(-velocity.getY()*((k+1)*m));
					//std::cout<<F.getY()<<'\n';
				}else{
					F.setY(0);
				}
				if(YCollN(pos, 10.f, Vec2d(1000, 600), (velocity*(FrameTime/1000.0)))){
					N.setY(-g*m);
					//std::cout<<P.getY()<<'\n';
				}else{
					N.setY(0);
				}
			}else{
				F.setXY(0,0);
			}
			acceleration=(F+N+P)*(1/m);
			velocity=velocity+(acceleration);

			pos=pos+(velocity*(FrameTime/1000.0));
			double fst, tst, vst, nst, ast, Ek, Ep;
			Ek=m*(velocity.length()/100)*(velocity.length()/100)*0.5;
			Ep=m*g*(600-(pos.getY()-10))/100;
			tst=t2.elapsed();
			nst=N.getY();
			fst=F.getY();
			ast=acceleration.getY();
			vst=velocity.getY();
			std::stringstream fl;
			fl<<tst<<" "<<vst/100<<" "<<ast<<" "<<fst<<" "<<nst<<" "<<Ek<<" "<<Ep;
			WriteDataToFile(fl);
		}
	}

}
