#include <chrono>
class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;
	std::chrono::time_point<clock_t> m_beg;
public:
	Timer() : m_beg(clock_t::now())
	{
	}
	void reset()
	{
		m_beg = clock_t::now();
	}
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

double benchFloatSimpleOperations(float hm){
	float pi, halfPi, a, b, c, d;
	a=2; b=1; halfPi=1; pi=0; c=-1;
	for(float i = 0; i<hm; i++){
		b+=2;
		halfPi+=-1*c+(a/b);
		c*=-1;
	}
	pi=halfPi*4;
}

double
