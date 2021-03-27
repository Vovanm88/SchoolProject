#include "MyTimer.h"
#ifdef _WIN32
MyTimer::MyTimer(){
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
}
double MyTimer::elapsed(){
	QueryPerformanceCounter(&nowTmp);
	return (nowTmp.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
}
void MyTimer::reset(){
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
}
double MyTimer::now(){
	QueryPerformanceCounter(&nowTmp);
	return (nowTmp.QuadPart) * 1000.0 / frequency.QuadPart;
}

#else
MyTimer::MyTimer(){
	m_beg=std::chrono::high_resolution_clock::now();
}
double MyTimer::elapsed(){
	return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000> > >(std::chrono::high_resolution_clock::now() - m_beg).count();
}
void MyTimer::reset(){
	m_beg = clock_t::now();
}
double MyTimer::now(){
	return std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000> > >(std::chrono::high_resolution_clock::now()).count();
}
#endif // _WIN32

