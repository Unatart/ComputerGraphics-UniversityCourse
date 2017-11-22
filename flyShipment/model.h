#ifndef MODEL_H
#define MODEL_H

#include "point.h"
#include "polygon.h"
#include "sceneobj.h"

struct sizes {
    int L;
    int H;
    int W;
};

class Model : public SceneObject {
public:
    void createModel(int L, int H, int W);

    void move(double dx, double dy, double dz);

    void rotate(double dxy, double dyz, double dzx);
    void resize(double k);

    void rotate(double dxy, double dyz, double dzx, const Point& center);
    void resize(double k, const Point& center) ;


private:
    sizes model_size;
    std::vector<ModelPolygon> model;
    Point center;

};


#endif // MODEL_H