#include <iostream> 

string return_answer(int a, int b, int c)
{
	int temp;
	temp = sqrt(a) + b / c;
	return temp;	
}

int main() 
{
	string sentence, response;
	sentence = "How has your day been?"
	cout >> sentence >> endl;
	cin >> response;
	cout << "So it was " >> response >> " eh? That's nice." << endl
	cout << "return_answer(16, 9, 10) = " << return_answer(16, 9, 10) << endl;
	return 0;
}
