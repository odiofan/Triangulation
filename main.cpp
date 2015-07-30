#include <iostream>
#include <fstream>
#include "triangulation.h"
#include <sys/time.h>
using namespace std;

int main()
{

    //code used to test that the program is fully functional

    ifstream fin("triangulation#4.tri");

    Triangulation<double> tri(fin);                     //create triangulation object from input data

    vertex<double> vert1(98.297,2.39778,995,0,0);        //vertices of triangle 8
    vertex<double> vert2(96.3014,3.56223,995,1,0);
    vertex<double> vert3(98.8337,4.90205,995,2,0);

    Triangle<double> midTri(vert1,vert2,vert3,1,0);

    midTri.setCircumcenter();

    cout<<midTri;

    double x,y,r;
    x=midTri.getcircumX()+0.00001;
    y=midTri.getcircumY()+0.00002;       //create point known to be in triangle 8
    r=midTri.getcircumR();

    vertex<double> test(x,y,955,4,0);


    tri.findPointLocation(test);    //test for point found


    ofstream output("output.tri");   //used to prove file output capability
    output << tri;
    output << flush;
    output.close();



}
