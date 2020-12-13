#include "Function1.h"

int main() {
	Plane A(1000, "MH370");
	Plane B(1500, "Airbus730");

	A.acknowledge(&B);
	B.acknowledge(&A);

	A.land();
	B.land();

	A.landingFinished();
	B.landingFinished();
	return 0;
}