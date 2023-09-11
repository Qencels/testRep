#include <string>
#include "Driver.h"
#include "Engine.h"

class Car {
public:
	Driver surname;
	Engine number;

	std::string color;
	std::string mark;

	bool status;

	std::string checkStatus() {
		return status ? "In autopark!" : "On the way!";
	}

	void setAutoparkStatus() {
		status = 1;
	}

	void setWayStatus() {
		status = 0;
	}
};