#include <iostream>
#include <stdio.h>
using namespace std;

int main(){
    double x;
    cin >> x;
    int y = 65536-11059200*x/12;
    printf("%x\n",y);
}
