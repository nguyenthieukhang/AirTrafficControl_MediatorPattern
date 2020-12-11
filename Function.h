#ifndef _FUNCTION_
#define _FUNCTION_
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <unistd.h>
using namespace std;

class Plane;

class IATCMediator {
protected:
    virtual void registerPlaneUnderGuidance(Plane* plane) = 0;
    virtual void notifyPlaneLanding(Plane* plane) = 0;
    virtual void notifyCurrentPlaneLocation(Plane* plane) = 0;
    virtual void notifyPlaneLandingFinnished(Plane* plane) = 0;
    virtual void notifyTechnicalTrouble(Plane* plane) = 0;
    virtual bool isAllowedToPlane(Plane* plane) = 0;
};

class ATCMediator : public IATCMediator {
public:
	//These functions will be called from the planes when they want to contact the mediator
	void registerPlaneUnderGuidance(Plane* plane);
	void notifyPlaneLanding(Plane* plane);
	void notifyCurrentPlaneLocation(Plane* plane);
	void notifyPlaneLandingFinnished(Plane* plane);
	void notifyTechnicalTrouble(Plane* plane);
	bool isAllowedToPlane(Plane* plane);	
private:
	const int safeDistance = 200;
	vector<Plane*> planeList;
	queue<Plane*> planeLandingQueue;
};

class Plane {
protected:
	ATCMediator* airTrafficController;
	int Altitude;
	string PlaneName;
public:
	/*****ACCESS FUNCTIONS*****/

	Plane(ATCMediator* _airTrafficController, int _altitude, string _planeName);
	string getPlaneName();
	int getAltitude();	

	/*****PLANE OPERATION FUNCTIONS*****/

	//The pilot will call these functions when he/she wants to do some of the following operations
	void registerUnderGuidance(); //Tell the nearby air tracffic controller that the plane is coming
	void changeLocation(int diff); //Fly lower or higher
	void land(); //Wants to land now
	void landingFinnished(); //Have finnished landing

	/*****COMMUNICATION FUNCTIONS*****/

	//The Air Traffic Controller giuding this plane will use these functions to communicate with the pilot
	void youCouldLandNow(); //Grants the plane landing permission
	void keepingSafeDistance(); //Tell this plane to kepp safe distance from other planes

};


#endif