#include "Function.h"

int main() {
	ATCMediator AirTrafficController;
	Plane A(&AirTrafficController, 1000, "Airbus370");
	//usleep(1000000);
	A.registerUnderGuidance();
	//usleep(1000000);
	Plane B(&AirTrafficController, 1500, "MH370");
	//usleep(1000000);
	B.registerUnderGuidance();
	//usleep(1000000);
	B.changeLocation(-400);

	return 0;
}