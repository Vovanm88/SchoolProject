#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Vec2d.h>
#include <MyTimer.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <cmath>
#include <chrono>
#include <thread>
#include <mutex>
#include <SimulationThread.h>
#include <RenderThread.h>
#include <fstream>

const double EPS=0.0000001;
Vec2d inputFile(){
	double X, Y;
	std::ifstream in("config.dat");
    if (in.is_open())
    {
		in>>X>>Y;
    }
    in.close();
    return Vec2d(X, Y);
}

void basicInput(Vec2d &p, Vec2d &v, double &k, double &g, double &m, Vec2d brd){
	double x, y;
	double bx, by;
	bx=brd.getX();
	by=brd.getY();
	int fX=bx/100;
	int fY=by/100;
	std::setlocale(LC_ALL, "Russian");
	std::cout<<"Введите начальное положение мячика"<<'\n'<<"по оси x(от 0 до "<<fX<<" м): ";
	std::cin>>x;
	if(x<0) x=0;
	if(x>fX) x=fX-0.02;
	std::cout<<"по оси y(от 0(пол) до "<<fY<<" м): ";
	std::cin>>y;
	y=fY-y;
	if(y<0) y=0;
	if(y>fY) y=fY-0.02;
	p.setXY(x, y);
	std::cout<<'\n'<<"Начальную скорость мячика по осям, м/с:"<<'\n'<<"по оси x: ";
	std::cin>>x;
	std::cout<<"по оси y: ";
	std::cin>>y;
	y=-y;
	v.setXY(x, y);
	std::cout<<'\n'<<"Коэффициент упругости (от 1 - абсолютно упрогий до 0 - абсолютно неупругий): ";
	std::cin>>k;
	if(k>1) k=1;
	if(k<0) k=0;
	std::cout<<'\n'<<"Значение универсальной гравитационной постоянной, м/с^2: ";
	std::cin>>g;
	std::cout<<'\n'<<"Масса, кг: ";
	std::cin>>m;
	if(m<0) m=-m;
	if(m<0.001) m=0.001;
	std::cout<<'\n'<<"Нажмите пробел для старта"<<'\n';
}

int main(){
	Vec2d brd=inputFile();
	Vec2d pos, velocity;
	double g, m, k;
	basicInput(pos, velocity, k, g, m, brd);
	ObjInfo bll;
	bll.pos=pos;
	bll.velocity=velocity;
	bll.k=k;
	bll.m=m;
	bll.g=g;
	std::mutex mtx;
	pos=pos*100;
	//pos.setXY(pos.getX()*100, brd.getY()-pos.getY()*100);
	sf::RenderWindow w1(sf::VideoMode(brd.getX(), brd.getY()), "Ball's kinematic sim");
	w1.setActive(false);
	int enb=2;
	std::thread threadSimulation(&simThread, std::ref(pos), std::ref(bll), std::ref(enb), std::ref(brd));

	std::thread threadRender(&renderingThread, std::ref(w1), std::ref(pos), std::ref(enb));

	MyTimer t1;
	double spacePressed=t1.elapsed();
	bool pause=true;
	while(w1.isOpen()){
		sf::Event ev;
		while(w1.pollEvent(ev)){
			if(ev.type ==  sf::Event::Closed){
				enb=0;
				w1.close();
			}
			if (ev.key.code == sf::Keyboard::Escape){
				enb=0;
				w1.close();
			}
			if (ev.key.code == sf::Keyboard::Space){
				if(t1.elapsed()-spacePressed>=500){
					pause=!pause;
					if(pause){
						enb=2;
					}else{
						enb=1;
					}
					spacePressed=t1.elapsed();
					//t2.reset();
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	threadRender.join();
	threadSimulation.join();
}
