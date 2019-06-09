#include<iostream>
#include<cstring>
#include<string>
using namespace std;

const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  //Array of alphabets for reference
const char rot_r[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";  //Right rotor wiring
const char rot_m[] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";  //Middle rotor wiring
const char rot_l[] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";  //Left rotor wiring
const char plugs[] = "CXAGLMDHNJUEFISVQROYKPZBTW";  //Plug board settings                       #Default Settings
const char refl[]  = "MCBYTOQVIJKLAPFNGWUESHRZDX";  //Reflector settings                        #Default Settings
int key[] = {1, 2, 4};                              //Rotor initial position [L,M,R] = [1,2,3]  #Default Values

int mod(int x)                                      //Modulus function
{
    return (x%26+26)%26;
}

char plugboard(char x)                              //Plug board swapping
{
    return plugs[x - 65];
}

char reflect(char x)                                //Reflector swapping
{
    return refl[x - 65];
}

int find_index(const char* arr, char x)             //Returns index of a character in an array
{
    return strchr(arr, x) - arr;
}

void rotate_()                                      //Function for rotating the rotors
{
    if (key[2] >= 25)
    {
        key[2] = 0;
        if (key[1] >= 25)
        {
            key[1] = 0;
            if (key[0] >= 25) key[0] = 0;
            else key[0]++;
        }
        else key[1]++;
    }
    else key[2]++;
}

char enigma(char x)
{
    x = plugboard(x);
    //cout<<"\n"<<x;                               //Input is passed through plug board
    x = rot_r[mod(find_index(alpha, x)+key[2])];    //After plug board, it passes through right rotor
    //cout<<"\n"<<x;
    x = rot_m[mod(find_index(alpha, x)+key[1])];    //After right rotor, it passes through middle rotor
    //cout<<"\n"<<x;
    x = rot_l[mod(find_index(alpha, x)+key[0])];    //After middle rotor, it passes through left rotor
    //cout<<"\n"<<x;
    x = reflect(x);                                 //After middle rotor, it goes to reflector
    //cout<<"\n"<<x;
    x = alpha[mod(find_index(rot_l, x)-key[0])];    //Reflector sends it back to the left rotor
    //cout<<"\n"<<x;
    x = alpha[mod(find_index(rot_m, x)-key[1])];    //
    //cout<<"\n"<<x;
    x = alpha[mod(find_index(rot_r, x)-key[2])];
    //cout<<"\n"<<x;
    x = plugboard(x);
    //cout<<"\n"<<x;

    rotate_();
    return x;
}

int main()                                          //Main() function
{
    string input;
    for (int j=0; j<3; j++)
    {
        cout<<"\n ENTER KEY "<<j<<" : ";
        cin>>*(key+j);
    }
    cout<<"\n USE UPPERCASE ONLY\n\n INPUT  : ";
    cin>>input;
    int len = input.length();
    cout<<"\n OUTPUT : ";
    for (int i=0; i<len; i++)
        cout<<enigma(input[i]);
    cout<<"\n ";cin>>input;
    return 0;
}
