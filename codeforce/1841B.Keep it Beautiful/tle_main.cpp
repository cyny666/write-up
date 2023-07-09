#include <iostream>
#include <string>
using namespace std;
bool check(int obj_copy[], int obj_length)
{obj_length++;
    if (obj_length <= 1)
        return 1;
    for(int i = 0; i <= obj_length ; i++)
    {   int flag = 1;
        // 把obj_copy移位过去
     if(i != 0)
        {obj_copy[obj_length+i-1] = obj_copy[i-1]; }
        for(int k = i ; k < obj_length+i-1; k++)
        {if (obj_copy[k] > obj_copy[k+1])
            {flag = 0;
                break;}}
        if (flag == 1 )
            return 1;
    }
    return 0;

}
int main() {
    string test_number;
    int number_test;
    int obj_copy[100000] = {0};
    int obj[100000] = {0};
    int obj_length = 0;
    int arry_length;
    getline(cin,test_number);
    number_test = stoi(test_number);
    for(int i = 0; i < number_test; i++) {
        cin >> arry_length;
        for (int j = 0; j < arry_length; j++)
        {cin>>obj_copy[j];obj_length=0;}
        //obj_copy是所有数组
        //对于每个数字进行检验并判定
        for(int k = 0; k <  arry_length; k++)
        { obj[obj_length] = obj_copy[k];
            if(check(obj,obj_length))
            {cout<<1;obj_length++;}
            else {cout<<0;}

        }
        cout<<"\n";}
  }