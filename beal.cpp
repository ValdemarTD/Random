#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int in, out, root;
	float result;

	while(true)
	{	
		cout << "Enter number to take the roots of." << endl; 
		cin >> in;
		
		root = 0;
 		while(result > 2)
		{
			 root = root + 1;
