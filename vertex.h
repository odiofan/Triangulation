#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class vertex{

private:
    T xValue, yValue, zValue;     //x y z values
    int indexNumber, noAttributes;

    vector<T> attributes;   //vector to hold attributes

public:

    //get functions

    vertex(const vertex& vtx);  //copy constructor

    T getXValue(void)const{return xValue;};
    T getYValue(void)const{return yValue;};
    T getZValue(void)const{return zValue;};
    int getIndexNo(void)const{return indexNumber;};

    //set functions

    void setXValue(T valueX){xValue = valueX;};
    void setYValue(T valueY){yValue = valueY;};
    void setZValue(T valueZ){zValue = valueZ;};


    vertex(T xVal, T yVal, T zVal, int indexNo, int attributeNo);   // constructor

    template<typename U>
    friend ostream& operator<<(ostream& os, const vertex<U>& vert);

};

template<typename T> vertex<T>::vertex(T xVal, T yVal, T zVal, int indexNo, int attributeNo):
    xValue(xVal),
    yValue(yVal),
    zValue(zVal),
    indexNumber(indexNo),
    noAttributes(attributeNo){   //constructor

    attributes.reserve(attributeNo);

    }

template<typename T> vertex<T>::vertex(const vertex& vtx):xValue(vtx.xValue),yValue(vtx.yValue),zValue(vtx.zValue){};

template<typename U> ostream& operator<<(ostream& os, const vertex<U>& vert){   //overload output operator

    os<<vert.getXValue()<<"  "<<vert.getYValue()<<"\n";
    return os;


}



