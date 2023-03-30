#include <iostream>
#include <math.h>
using namespace std;
class Sphere {

public:
	double xcord;
	double ycord;
	double zcord;
	double radius;
	Sphere(double x, double y, double z, double rad) {
		xcord = x;
		ycord = y;
		zcord = z;
		radius = rad;
	}
	//check if collission happened
	bool iscollision(Sphere other) {
		float distance = sqrt(
			(this->xcord - other.xcord) * (this->xcord - other.xcord) +
			(this->ycord - other.ycord) * (this->ycord - other.ycord) +
			(this->zcord - other.zcord) * (this->zcord - other.zcord)
		);
		return distance < (this->radius + other.radius);
	}
	//extra credit 2, normalize spheres
	void getnormal(Sphere other) {
		double distx = this->xcord - other.xcord;
		double disty = other.ycord - this->ycord;
		double distz = other.zcord - this->zcord;
		double distance = sqrt(distx * distx + disty * disty + distz * distz);
		double nx = distx / distance;
		double ny = disty / distance;
		double nz = distz / distance;
		cout << "Unit normal vector at the point of contact: (" << nx << ", " << ny << ", " << nz << ")" << endl;
	}
	
};
int main(int argc, const char* argv[]) {
	//checking to see if correct number of arguments is inputted, 1 for help and 8 for the actual project 
	string wrongInput = "wrong input entered, try again or press -h or -help for help.";
	if (argc == 1) {
		cout << "no argument entered, please enter again with the proper arguments. for help, run the code with -h or -help";
		return 0;
	}
	else if (argc == 2) {
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "--h") == 0) {//if help is the argument
			cout << "this program will check if 2 speres collide. enter the x, y, and z coordinates and then the radius of your first sphere, and then do the same with the second. all as seperate arguments.";
		}
		else {
			cout << wrongInput;
		}
		return 0;
	}
	else if (argc == 9) {//if the correct number of arguments are given run the actual project
		Sphere s1 = { atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]) };
		Sphere s2 = { atof(argv[5]), atof(argv[6]), atof(argv[7]), atof(argv[8]) };

		if (s1.iscollision(s2)) {


			cout << "yes, the two spheres enter collide";
			s1.getnormal(s2);
		}
		else
			cout << "no, the two spheres entered don't collide";
		s1.getnormal(s2);
		return 0;
	}
	else {
		cout << wrongInput;
		return 1;
	}
}