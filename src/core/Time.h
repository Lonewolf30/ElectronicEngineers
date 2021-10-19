#ifndef ELECTRONICENGINEERS_TIME_H
#define ELECTRONICENGINEERS_TIME_H

#include <chrono>

using namespace std::chrono;

inline high_resolution_clock::time_point NanoTime() {
	return high_resolution_clock::now();
}

template<class T> inline T GetDuration(high_resolution_clock::time_point now, high_resolution_clock::time_point past){
	return duration_cast<duration<T>>(now - past).count();
}

#endif