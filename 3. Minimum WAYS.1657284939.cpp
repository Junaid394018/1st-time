#include<iostream>
using namespace std;
int flip(int number);
int main()
{  	 do{int number, fliped, count = 11;  bool ok, FLIPED = true;
		do{ cout<<"Enter the number (between 1 and 100): "; 
		    cin >> number;} while(number < 0 || number >100);
		int numbersays[number];
		if(number < 9){for(int i = 0; i<number; ++i) numbersays[i]=i+1;	}
		else {for(int i = 0; i<11; ++i) numbersays[i]=i+1;	}
			for(int i = 11; i < number; ++i, count++)
			   { numbersays[i] = numbersays[i-1]+1;
			     for(int k = 12, j = 2; k < 20; ++k, ++j)
			         if(FLIPED){if(number >= j*10 && number <= (j+1)*10)
					              {for(int x=12; x<k; ++x,++i)
					                  numbersays[i]=x;
								   numbersays[i]=k; FLIPED = false;}}
	            fliped = flip(numbersays[i]);
		        if(fliped > numbersays[i] && fliped < number)
				  {numbersays[i+1] = fliped;  ++i;  count++; }}
		  for(int i = 0; i < count+1; ++i)
		    {  cout<<numbersays[i]<<" "; if(numbersays[i]==number) break;}
				 cout<<endl;}while(true);                                         return 0;}  

int flip(int number)
{  int x,y,z;   x = number / 10;  y = number % 10;    z = y*10+x;    return z;}

