#ifndef MYTIMER_H
#define MYTIMER_H
///////////////THIS PART ONLY FOR WINDOWS
#ifdef _WIN32
	#include <windows.h> //for win32 api
	class MyTimer{
		private:
			LARGE_INTEGER frequency;
			LARGE_INTEGER start, nowTmp;
		public:
			MyTimer();
			double elapsed();
			void reset();
			double now();
	};
/*  FOR LINUX AND OTHERS */
	#else
	#include <chrono>
	class MyTimer{
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_beg;
		public:
			double elapsed() const;
			void reset();
			double now() const;
	};
	#endif
#endif // MYTIMER_H
