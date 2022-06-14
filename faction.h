#pragma once

//#define DEBUG

#include <iostream>
namespace wow {
	class Time
	{
	private:
		unsigned long long _time = 0;
	public:

		inline unsigned long long getHour()const { return _time / 60; }
		inline unsigned long long getMin()const { return _time % 60; }
		inline unsigned long long addTime() { return ++_time; }
		inline unsigned long long addTime(int n = 1) { return _time += n; }
		inline operator unsigned long long()const { return getMin(); }
		inline Time& operator++(int) { ++_time; return *this; }
		inline Time& operator++() { ++_time; return *this; }
		inline void clear() { _time = 0; }

	};

	extern Time worldTime;

	class Output
	{
	public:
		void textOut(std::string);

		std::ostream& operator<<(std::string s);
	}static output;

	class Debug
	{
	public:
		void Log(std::string s);
	}static debug;


}
