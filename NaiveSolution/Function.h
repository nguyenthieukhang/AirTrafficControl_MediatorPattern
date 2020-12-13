#ifndef _FUNCTION1_
#define _FUNCTION1_ 
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unistd.h> //mac only
using namespace std;

class Plane {
private:
	int Altitude;
	string PlaneName;
	vector<Plane*> otherPlanes;
	const int safeDistance = 200;
	bool IsLanding = 0; //Answer if this plane is waiting to land now
public:

	Plane(int _altitude, string _planeName);

	/*****ACCESS FUNCTIONS*****/

	string getPlaneName();
	int getAltitude();	
	bool getIsLanding();

	/*****PLANE OPERATION FUNCTIONS*****/

	void changeLocation(int diff); //Fly lower or higher
	void land(); //Wants to land now
	void landingFinished(); //Have finished landing

	/*****COMMUNICATION FUNCTIONS*****/

	void acknowledge(Plane* plane);
	void youCouldLandNow(); //Grants the plane landing permission
	void keepingSafeDistance(Plane* plane); //Tell this plane to keep safe distance from other planes
	bool notifyLanding(Plane* plane); //Tell other planes that this plane wants to land
	void notifyLandingFinished(); //Some other planes has finished landing

};

#endif