#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include "model.h"

namespace s21 {
class Controller {
 private:
    Model model_;

 public:
    //  explicit Controller(model *model) : model_(model) {}
    //  explicit Controller() {}
    //  ~Controller() {}
    /*_________________________parser___________________________*/
    void load_object_model(const char *filename);
    /*__________________________getters__________________________*/
    int get_vertices_count();
    int get_index_count();
    std::vector<double> get_vertices();
    std::vector<unsigned int> get_index();
    /*___________________affine_transformations__________________*/
    void scale_(double zoom);
    void move_x_(double xMov);
    void move_y_(double yMov);
    void move_z_(double zMov);
    void rotation_x_(double xRot);
    void rotation_y_(double yRot);
    void rotation_z_(double zRot);
};
};  // namespace s21

#endif  // SRC_CONTROLLER_H_
