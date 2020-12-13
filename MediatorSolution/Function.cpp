#include "Function.h"

void ATCMediator::registerPlaneUnderGuidance(Plane* plane) {
	cout << "Air Traffic Controller: Recieved message.\n";
	planeList.push_back(plane);
	cout << "Air Traffic Controller: Plane " << plane->getPlaneName() << " sucessfully registered under guidance of the Air Traffic Controller.\n";
}

void ATCMediator::notifyPlaneLanding(Plane* plane) {
	cout << "Air Traffic Controller: Recieved message.\n";
	cout << "Air Traffic Controller: Plane " << plane->getPlaneName()  << " is landing now.\n";
}

bool ATCMediator::isAllowedToPlane(Plane* plane) {
	cout << "Air Traffic Controller: Recieved message.\n";
	bool allow = planeLandingQueue.empty();
	if(!allow) {
		cout << "Air Traffic Controller: Plane " << plane->getPlaneName() << " must wait, there are "<< (int)planeLandingQueue.size() <<" other planes which need to land first.\n";
	}
	else cout << "Air Traffic Controller: Plane " << plane->getPlaneName()  << " could land now.\n";
	planeLandingQueue.push(plane);
	return allow;
}

void ATCMediator::notifyCurrentPlaneLocation(Plane* plane) {
	cout << "Air Traffic Controller: Recieved message.\n";
	for(auto nearbyPlane:planeList) 
		if(abs(plane->getAltitude()-nearbyPlane->getAltitude())<safeDistance and plane!=nearbyPlane) nearbyPlane->keepingSafeDistance();
}

void ATCMediator::notifyPlaneLandingFinished(Plane* plane) {
	cout << "Air Traffic Controller: Recieved message.\n";
	vector<Plane*> newList;
	for(auto planeUnderGuidance:planeList) if(planeUnderGuidance!=plane) newList.push_back(planeUnderGuidance);
	planeList = newList;
	planeLandingQueue.pop();
	cout << "Air Traffic Controller: Plane " << plane->getPlaneName() << " sucessfully removed from guidance list of the Air Traffic Controller.\n";
	if(!planeLandingQueue.empty()) planeLandingQueue.front()->youCouldLandNow();

}
void ATCMediator::notifyTechnicalTrouble(Plane* plane) {
	cout << "Air Traffic Controller: Recieved message.\n";
	cout << "Air Traffic Controller: Plane " << plane->getPlaneName() << " is having techinical issue and is directed to our Help Center.\n";
}

//Access to planes' private members
Plane::Plane(ATCMediator* _airTrafficController, int _altitude, string _planeName) {
	airTrafficController = _airTrafficController;
	Altitude = _altitude;
	PlaneName = _planeName;
}

string Plane::getPlaneName() {
	return PlaneName;
}

int Plane::getAltitude() {
	return Altitude;
}

//Plane's operations
void Plane::registerUnderGuidance() {
	cout << "Plane " << PlaneName << " wants to register for guidance of the Air Traffic Controller.\n";
	airTrafficController->registerPlaneUnderGuidance(this);
}

void Plane::land() {
	cout << "Plane " << PlaneName << " wants to land.\n";
	bool isAllowedToPlane = airTrafficController->isAllowedToPlane(this);
	if(isAllowedToPlane) airTrafficController->notifyPlaneLanding(this);
}

void Plane::changeLocation(int diff) {
	cout << "Plane " << PlaneName << " is changing location.\n";
	Altitude+=diff;
	airTrafficController->notifyCurrentPlaneLocation(this);
}

void Plane::landingFinished() {
	cout << "Plane " << PlaneName << " has finnisehd landing\n";
	airTrafficController->notifyPlaneLandingFinnished(this);
}

//Plane's communication
void Plane::youCouldLandNow() {
	cout << "Plane " << PlaneName << " recieved message.\n";
	land();
}

void Plane::keepingSafeDistance() {
	cout << "Air Traffic Controller: Plane " << PlaneName << " should keep safe distance. There are other planes in a range of dangerous distance\n";
	cout << "Plane " << PlaneName << " recieved message.\n";
	cout << "Plane " << PlaneName << " will fly carefully.\n";
}

