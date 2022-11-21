#include "controller.h"

namespace s21 {

/*_________________________parser___________________________*/
void Controller::load_object_model(const char *filename) { model_.load_obj_model(filename); }
/*__________________________getters__________________________*/
int Controller::get_vertices_count() { return model_.getVerticesCount(); }
int Controller::get_index_count() { return model_.getIndexCount(); }
std::vector<double> Controller::get_vertices() {
    std::vector<double> k = model_.getVertices();
    return k;
}
std::vector<unsigned int> Controller::get_index() { return model_.getIndex(); }

/*___________________affine_transformations__________________*/
void Controller::scale_(double zoom) { model_.scale(zoom); }
void Controller::move_x_(double zoom) { model_.move_x(zoom); }
void Controller::move_y_(double zoom) { model_.move_y(zoom); }
void Controller::move_z_(double zoom) { model_.move_z(zoom); }
void Controller::rotation_x_(double zoom) { model_.rotation_x(zoom); }
void Controller::rotation_y_(double zoom) { model_.rotation_y(zoom); }
void Controller::rotation_z_(double zoom) { model_.rotation_z(zoom); }

};  // namespace s21
