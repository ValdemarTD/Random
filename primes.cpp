#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;

int main()
{
  unsigned long long int num;
  int mult = 3, oldMult = 3;
  bool isPrime;

  isPrime = true;

//  cout << "Which prime would you like to start at?" << endl;
//  cin >> num;

  num = 3;

  while(num < 9223372036854775807 and num > 0)
  {
    isPrime = true;
    num = num * mult -2;
    for (int a = 1; a < sqrt(num); a = a + 1)
    {
      if(num % a == 0 and a != 1 and num % 5 != 0 and a != num)
      {
        cout << num << " is not prime." << endl;
        cout << "Its first factor is " << a << endl;
        isPrime = false;
        num = (num + 2)/mult;
        mult = mult * oldMult - 2;
        if(mult > 1459 and oldMult == 3)
        {
          oldMult = 7;
          mult = 3;
        }
      }
    }
    if(isPrime==true and num % 5 != 0)
      cout << num << " is prime." << endl;
  }
}
