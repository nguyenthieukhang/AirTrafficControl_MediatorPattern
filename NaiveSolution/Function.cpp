#include "Function1.h"

Plane::Plane(int _altitude, string _planeName) {
	Altitude = _altitude;
	PlaneName = _planeName;
}

string Plane::getPlaneName() {
	return PlaneName;
}

int Plane::getAltitude() {
	return Altitude;
}

bool Plane::getIsLanding() {
	return IsLanding;
}

void Plane::acknowledge(Plane* plane) {
	cout << "Plane " << PlaneName << " acknowledges plane " << plane->getPlaneName() << ".\n";
	otherPlanes.push_back(plane);
}

void Plane::changeLocation(int diff) {
	cout << "Plane " << PlaneName << " is changing location.\n";
	Altitude+=diff;
	for(auto nearbyPlane:otherPlanes) if(abs(nearbyPlane->getAltitude()-Altitude)<safeDistance) nearbyPlane->keepingSafeDistance(this);
}

void Plane::keepingSafeDistance(Plane* plane) {
	cout << "Plane " << PlaneName << " should keep safe distance. Plane " << plane->getPlaneName() << " is in a range of dangerous distance\n";
	cout << "Plane " << PlaneName << " recieved message.\n";
	cout << "Plane " << PlaneName << " will fly carefully.\n";
}

void Plane::land() {
	cout << "Plane " << PlaneName << " wants to land.\n";
	IsLanding = 1;
	bool couldLand = 1;
	for(auto nearbyPlane:otherPlanes) {
		couldLand = nearbyPlane->notifyLanding(this);
	}
	if(couldLand) cout << "Plane " << PlaneName << " is landing now.\n"; 
}

void Plane::landingFinished() {
	cout << "Plane " << PlaneName << " has finished landing\n";
	cout << "Notifying all other planes...\n";
	for(auto nearbyPlane:otherPlanes) {
		nearbyPlane->notifyLandingFinished();
	}	
}

bool Plane::notifyLanding(Plane* plane) {
	return !IsLanding;
}

void Plane::notifyLandingFinished() {
	if(IsLanding) land();
}