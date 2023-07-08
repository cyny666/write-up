#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int main() {
  string cases_number;
    getline(cin,cases_number);
   int obj_number = stoi(cases_number);
  string cases;
  int question_number = 0;
  int target = 0;
  for(int i = 0; i < obj_number; i++)
  {getline(cin,cases); target = 0;
      for(int j = 0; j < cases.length(); j++)
      {if (cases[j] == '?')
          question_number++;}
    if(cases[0] == '0' )
    {cout<<0<<"\n";question_number=0;}
    else if(question_number == 0)
    {cout<<1<<"\n";question_number=0;}
   else{   if (cases[0] == '?') {target = 9;
          for (int i = 0; i < question_number - 1; i++)
          {  target *= 10;  }
          cout<<target<<"\n";
      }
      else {target = 1 ;
          for (int i = 0; i < question_number; i++)
          { target *= 10;}
          cout<<target<<"\n";
      }
    question_number = 0;


  }}}