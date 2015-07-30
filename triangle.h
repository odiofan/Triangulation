#include <iostream>
#include <math.h>


template<class T>
class Triangle{


    private:
    vertex<T> vertex0,vertex1,vertex2;
    int indexNo, noOfAttributes;
    T circumcenterX,circumcenterY,circumRadius;

    T length0,length1,length2;

    public:

    vector<T> attributes;

    Triangle(vertex<T> vert0, vertex<T> vert1, vertex<T> vert2, int indexNo, int attributeNo);

    T getlength(vertex<T>& vert1, vertex<T>& vert2);

    int getTriangleID(void)const{return indexNo;};
    int getVertex0ID(void)const{return vertex0.getIndexNo();};
    int getVertex1ID(void)const{return vertex1.getIndexNo();};
    int getVertex2ID(void)const{return vertex2.getIndexNo();};
    T getLength0(void)const{return length0;};
    T getLength1(void)const{return length1;};
    T getLength2(void)const{return length2;};
    T getArea(void)const;
    T getAtts(int i)const{return attributes[i];};
    vertex<T> getVert0(void)const{return vertex0;};
    vertex<T> getVert1(void)const{return vertex1;};
    vertex<T> getVert2(void)const{return vertex2;};
    T getcircumX(void)const{return circumcenterX;};
    T getcircumY(void)const{return circumcenterY;};
    T getcircumR(void)const{return circumRadius;};

    //vertex<T> getVert2(void)const{return vertex2;};

    void setlengths(vertex<T> vert0,vertex<T> vert1,vertex<T> vert2);

    void addNewAttribute(T attribute){attributes.push_back(attribute);};

    void setCircumcenter(void);

    bool pointTest(vertex<T> point);   //takes xy coordinate and returns bool true if point is in triangle

    template<typename U>
    friend ostream& operator<<(ostream& os, const Triangle<U>& tri);
};

template<typename T> Triangle<T>::Triangle(vertex<T> vert0, vertex<T> vert1, vertex<T> vert2, int noIndex, int noAttributes)
    :vertex0(vert0),
     vertex1(vert1),
     vertex2(vert2),
     indexNo(noIndex),
     noOfAttributes(noAttributes){

     attributes.reserve(noOfAttributes);
     this->setlengths(vertex0,vertex1,vertex2);

     }

template<typename U> ostream& operator<<(ostream& os, const Triangle<U>& tri)
{
    os <<tri.getArea()<<" "<<tri.getcircumX()<<" "<<tri.getcircumY()<<" "<<tri.getcircumR()<<"\n";
    return os;
}

template<typename T> T Triangle<T>::getlength(vertex<T>& vert1, vertex<T>& vert2){

    //cout<<vert1<<vert2;

    T x1 = vert1.getXValue();
    T x2 = vert2.getXValue();
    T y1 = vert1.getYValue();
    T y2 = vert2.getYValue();

    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));

}

template<typename T> void Triangle<T>::setlengths(vertex<T> vert0,vertex<T> vert1,vertex<T> vert2){   //sets lengths of each side

    this->length0 = getlength(vert0,vert1);
    this->length1 = getlength(vert1,vert2);
    this->length2 = getlength(vert2,vert0);

}

template<typename T> T Triangle<T>::getArea(void)const{

    vertex<T> tempV = this->getVert2();

    T height = tempV.getYValue();

    return height*(this->getLength0())/2;

}

template<typename T> void Triangle<T>::setCircumcenter(void){   //uses cramers rule implementation to determine circcumcenter and circumradius

    vertex<T> tempV0 = this->getVert0(),tempV1=this->getVert1(),tempV2=this->getVert2();

    T a1,a2,a3,b1,b2,b3,d1,d2,d3,det,detX,detY,detR,circumX,circumY,circumR;
    a1 = tempV0.getXValue();
    a2 = tempV1.getXValue();
    a3 = tempV2.getXValue();
    b1 = tempV0.getYValue();
    b2 = tempV1.getYValue();
    b3 = tempV2.getYValue();
    d1 = a1*a1 + b1*b1;
    d2 = a2*a2 + b2*b2;
    d3 = a3*a3 + b3*b3;

    //cout<<a1<<" "<<b1<<" "<<a2<<" "<<b2<<" "<<a3<<" "<<b3<<"\n";

    det = a1*b2 + b1*a3 + a2*b3 - b2*a3 - b1*a2 - a1*b3;

    detX = d1*b2 + b1*d3 + d2*b3 - b2*d3 - b1*d2 - d1*b3;
    detY = a1*d2 + d1*a3 + a2*d3 - d2*a3 - d1*a2 - a1*d3;
    detR = a1*b2*d3 + b1*d2*a3 + d1*a2*b3 - d1*b2*a3 - b1*a2*d3 - a1*d2*b3;

    circumX = (detX/det)/2;
    circumY = (detY/det)/2;
    circumR = sqrt((detR/det) + circumX*circumX + circumY*circumY);

    this->circumcenterX = circumX;
    this->circumcenterY = circumY;
    this->circumRadius = circumR;

}

template<typename T> bool Triangle<T>::pointTest(vertex<T> point){   //test point in triangle, return bool if it is in triangle

    T x,y,Ox,Oy,R,distance;
    x = point.getXValue();
    y = point.getYValue();
    Ox = this->getcircumX();
    Oy = this->getcircumY();
    R = this->getcircumR();

    distance = sqrt((x-Ox)*(x-Ox)+(y-Oy)*(y-Oy));

    //cout<<Ox<<" "<<Oy<<" "<<R<<" "<<distance<<"\n";

    if(distance<R){
        return true;
    }
    else{
        return false;
    }
}



