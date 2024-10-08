//
// Created by perha on 09.05.2024.
//
#include <fstream>
#include <iostream>
#include <string>
#include "BuildingMap.h"
using namespace std ;
int main()
{
    BuildingMap bm("HW4/test.txt") ;
        cout << endl;
        bm.displayAllCubicles();
        /*cout << endl;
        bm.displayAdjacentCubicles(1,1);
        cout << endl;
        bm.displayAdjacentCubicles(2,2);
        cout << endl;
        bm.displayAdjacentCubicles(3,5);
        cout << endl;
        bm.displayBuildingMap();
        cout << endl;
        bm.findPaths(0,0,4,0);
        cout << endl;
        bm.findPaths(0,0,4,0,1,3);
        cout << endl;
        bm.findPaths(0,0,4,0,2,1);
        cout<<endl;
        bm.findPaths(3,1,2,4);*/
    return 0 ;
}