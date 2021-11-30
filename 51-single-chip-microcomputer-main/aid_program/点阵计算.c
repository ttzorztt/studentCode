#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
using namespace std;

int main(){
    fstream file;
    file.open("点阵.txt");
    int ans = 0;
    char ret = '0';
    vector<vector<char>> t(8,vector<char>(2));
    for (int a = 0; a < 8; ++a){
        for (int c = 0; c <= 1; ++c){
            ret = '0';
            for (int b = 0; b < 4; ++b){
                file >> ans;
                ret += ans * pow(2, b);}
            t[a][c] = (ret > '9' ? char(ret - ':' + 'A') : char(ret));
        }
    }
    for(int a = 0; a <= 7; ++a){
        cout << "P0 = 0XFF; P1 = 0X0" << a << ";" << "P0 = 0X";
            cout << t[a][1] << t[a][0];
        cout << ';' << endl;
    }
    file.close();
    return 0;
}
