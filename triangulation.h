#include <iostream>
#include "vertex.h"
#include <fstream>
#include "triangle.h"

using namespace std;


template<typename T>
class Triangulation{

private:
    int noOfVertices,noDimensions,attsPerVert,noOfCells,attsPerCell,vertsPerCell;

    vector<vertex<T> > vertices;
    vector<Triangle<T> > triangles;

public:

    int getNoVertices(void)const{return noOfVertices;};
    int getNoDimensions(void)const{return noDimensions;};
    int getNoCells(void)const{return noOfCells;};
    int getAttsPerCell(void)const{return attsPerCell;};
    int getAttsPerVert(void)const{return attsPerVert;};
    int getVertsPerCell(void)const{return vertsPerCell;};

    vertex<T> getVertex(int i)const{return vertices[i];};
    Triangle<T> getTri(int i)const{return triangles[i];};


    void setNoVertices(int no){noOfVertices=no;};
    void setNoDimensions(int dim){noDimensions=dim;};
    void setAttsPerVert(int no){attsPerVert=no;};
    void setNoCells(int no){noOfCells=no;};
    void setAttsPerCell(int no){attsPerCell=no;};
    void setVertsPerCell(int no){vertsPerCell=no;};

    Triangulation(istream& _input);

    void findPointLocation(vertex<T> findMe);

    template<typename U>
    friend ostream& operator<<(ostream& os, const Triangulation<U>& tri);

};

template<typename T> Triangulation<T>::Triangulation(istream& input){

    int noOfVertices,noDimensions, noOfCells, attsPerCell,attsPerVert,vertsPerCell;
    input>> noOfVertices >> noDimensions >> attsPerVert;

    setNoVertices(noOfVertices);
    setNoDimensions(noDimensions);
    setAttsPerVert(attsPerVert);

    vertices.reserve(noOfVertices);

    for(int i = 0; i <noOfVertices; ++i){

        int tempId;
        double tempx,tempy,tempz;
        input>>tempId>>tempx>>tempy>>tempz;
        vertex<double> tempVert(tempx,tempy,tempz,tempId,attsPerVert);
        vertices.push_back(tempVert);
        }

    input>>noOfCells>>vertsPerCell>>attsPerCell;

    setNoCells(noOfCells);
    setVertsPerCell(vertsPerCell);
    setAttsPerCell(attsPerCell);

    triangles.reserve(noOfCells);
    int triangleid,vertice0id,vertice1id,vertice2id;

    for(int i = 0; i<noOfCells;++i){

        input>>triangleid>>vertice0id>>vertice1id>>vertice2id;

        vertex<double> vertice0 = vertices[vertice0id];
        vertex<double> vertice1 = vertices[vertice1id];
        vertex<double> vertice2 = vertices[vertice2id];
        Triangle<double> tempTri(vertice0,vertice1,vertice2,triangleid,attsPerCell);

        for(int j = 0; j<attsPerCell;++j){

            float attvalue;
            input>>attvalue;
            tempTri.addNewAttribute(attvalue);
        }
        triangles.push_back(tempTri);
    }
}

template<typename T> ostream& operator<<(ostream& os, const Triangulation<T>& tri){   //output overload

    int noVert = tri.getNoVertices(), noDimensions = tri.getNoDimensions(), attsPerVert = tri.getAttsPerVert();
    int noCells = tri.getNoCells(), vertsPerCell = tri.getVertsPerCell(), attsPerCell = tri.getAttsPerCell();  //reads triangulation values into variables

    os<<noVert <<" " <<noDimensions <<" "<<attsPerVert<<endl;  //outputs vertice information

    for(int i = 0;i<noVert;++i){
        vertex<T> tempVert = tri.getVertex(i);
        os <<tempVert.getIndexNo()<<" "<<tempVert.getXValue()<<" "<<tempVert.getYValue()<<" "<<tempVert.getZValue() << endl;  //specific vertice values
    }

    os<<noCells<<" "<<vertsPerCell<<" "<<attsPerCell<<endl;  //triangle info
    for(int i = 0;i<noCells;++i){
        Triangle<T> tempTri = tri.getTri(i);
        os<<tempTri.getTriangleID()<<" "<<tempTri.getVertex0ID()<<" "<<tempTri.getVertex1ID()<<" "<<tempTri.getVertex2ID()<<" ";

        for(int j=0;j<attsPerCell;++j){
            os<<tempTri.getAtts(j)<<" ";      //takes atts from triangle class
        }
        os<<"\n";
    }

    return os;

}

template<typename T> void Triangulation<T>::findPointLocation(vertex<T> findMe){   //goes through triangulation testing each triangle for the presence of the point

    int noTris = this->getNoCells();
    bool checkpoint(false);

    for(int i = 0; i <noTris;++i){

    Triangle<T> tempTri = this->getTri(i);
    tempTri.setCircumcenter();
    cout<<tempTri.getTriangleID()<<"\n";
    checkpoint = tempTri.pointTest(findMe);
    if(checkpoint==true){
        cout<<"Point found in triangle"<<tempTri.getTriangleID()<<"\n";  //if point is found
    }

    }

}

