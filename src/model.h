#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace s21 {

class Model {
 public:
    Model() : vertices_count(0), index_count(0) {}

    /*_________________________parser___________________________*/
    void load_obj_model(const char *filename);

    /*__________________________getters__________________________*/
    int getVerticesCount() { return vertices_count; }
    int getIndexCount() { return index_count; }
    std::vector<double> getVertices() { return vertices; }
    std::vector<unsigned int> getIndex() { return index; }

    /*___________________affine_transformations__________________*/
    void scale(double zoom);
    void move_x(double xMov);
    void move_y(double yMov);
    void move_z(double zMov);
    void rotation_x(double xRot);
    void rotation_y(double yRot);
    void rotation_z(double zRot);

 private:
    int vertices_count;
    int index_count;
    std::vector<double> vertices;     // v
    std::vector<unsigned int> index;  // f
};
}  // namespace s21

#endif  // SRC_MODEL_H_
