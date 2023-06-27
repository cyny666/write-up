# include <iostream>
using namespace std;
int main() {
    char word[1000];
    int upper_number = 0, lower_number = 0;
    cin>>word;
    for(int i=0; i <=1000 ; i++)
        {if (word[i] >= 65 && word[i] <= 90)
            { upper_number++;
                continue;}
         if (word[i] >= 97 && word[i] <= 122)
         {lower_number++;
             continue;}
        else break;
        }
    if (upper_number <= lower_number)
        {for (int i = 0; i <= upper_number + lower_number ; i++)
            {if (word[i] >= 65 && word[i] <= 90)
                word[i] -= 'A' - 'a';
            else continue;
            }
        }
    if (upper_number > lower_number)
        {
        for (int i = 0; i <= upper_number + lower_number ;i++)
            {
             if (word[i] >= 97 && word[i] <= 122)
             word[i] += 'A' - 'a';
             else continue;
            }
        }

    cout<<word;
    return 0;
}
