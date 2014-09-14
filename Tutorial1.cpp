#include <iostream> // files or headers that contain things you may reference

using namespace std;
/*
int main()
{
	cout << "Hello world!" << endl;    // output << string << end line /n
	return 0; 						   // because the main function returns a 0
}


// compile with g++ Tutorial1.cpp -Wall -o tut


int add(int a, int b) 
{
	int c = a + b;
	return c;
	// return a + b;
}


int main()
{
	// straightforward math
	int a = 1;
	int b = 2;
	int ab = a + b;
	cout << "1 + 2 = " << ab << endl;
	ab = a - b;
	cout << "1 - 2 = " << ab << endl;
	ab = b * (a + b);
	cout << "2(1 + 2) = " << ab << endl;
	
	// difference between int and float (rounding)
	ab = a / b;
	cout << "1 / 2 = " << ab << endl;
	
	float c = 1;
	float d = 2;
	float cd = c / d;
	cout << "1 / 2 = " << cd << endl;	
	
	// double rounds to more decimal places
	double e = 20;
	double f = 7;
	double ef = e / f;
	cout << "20 / 7 = " << ef << endl;
	
	cout << add(a, b) << endl;
	
	return 0;
}
*/

int main()
{
	double a, b;
	string input_1 = "What is your first number?";
	string input_2 = "What is your second number?";
	cout << input_1 << endl;
	cin >> a;
	cout << "a = " << a << endl;
	cout << input_2 << endl;
	cin >> b;
	cout << "b = " << b << endl;
	cout << "a + b = " << a + b << endl;
	
	return 0;
}

// Create a function that calculates the distance between two points (a, b) and (x, y)
// Think about the return type, and the number of inputs. 
// You can use the math functions from the standard library (math.h)
