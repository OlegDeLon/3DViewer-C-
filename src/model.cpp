#include "model.h"

#include <cmath>

namespace s21 {
/*______________________parser______________________*/
void Model::load_obj_model(const char *filename) {
    vertices.clear();
    index.clear();
    vertices_count = 0;
    index_count = 0;
    std::ifstream ifs(filename, std::ios::in);
    if (!ifs.bad()) {
        std::string line;
        while (ifs >> line) {
            if (line[0] == 'v' && line.size() == 1) {
                double x, y, z;
                ifs >> x >> y >> z;
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                ++vertices_count;
            }
            while (line[0] == 'f' && line.size() == 1) {
                ifs >> line;
                double first_index;
                first_index = std::stod(line);
                index.push_back(first_index - 1);
                ifs >> line;
                ++index_count;
                while (line[0] != 'f' && isdigit(line[0])) {
                    double tmp_index = std::stod(line);
                    index.push_back((int)tmp_index - 1);
                    index.push_back((int)tmp_index - 1);
                    if (ifs.eof()) break;
                    ifs >> line;
                    ++index_count;
                }
                index.push_back((int)first_index - 1);
            }
        }
        ifs.close();
    }
}
/*___________________affine_transformations___________________*/
void Model::scale(double zoom) {
    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i] = vertices[i] * zoom;
    }
}

void Model::move_x(double xMov) {
    for (size_t i = 0; i < vertices.size(); i += 3) {
        vertices[i] = vertices[i] + xMov;
    }
}

void Model::move_y(double yMov) {
    for (size_t i = 1; i < vertices.size(); i += 3) {
        vertices[i] = vertices[i] + yMov;
    }
}

void Model::move_z(double zMov) {
    for (size_t i = 2; i < vertices.size(); i += 3) {
        vertices[i] = vertices[i] + zMov;
    }
}

void Model::rotation_x(double xRot) {
    for (size_t i = 1; i < vertices.size(); i += 3) {
        double temp_y = vertices[i];
        double temp_z = vertices[i + 1];
        vertices[i] = cos(xRot) * temp_y - sin(xRot) * temp_z;
        vertices[i + 1] = sin(xRot) * temp_y + cos(xRot) * temp_z;
    }
}

void Model::rotation_y(double yRot) {
    for (size_t i = 0; i < vertices.size(); i += 3) {
        double temp_x = vertices[i];
        double temp_z = vertices[i + 2];
        vertices[i] = cos(yRot) * temp_x + sin(yRot) * temp_z;
        vertices[i + 2] = (-1) * sin(yRot) * temp_x + cos(yRot) * temp_z;
    }
}

void Model::rotation_z(double zRot) {
    for (size_t i = 0; i < vertices.size(); i += 3) {
        double temp_x = vertices[i];
        double temp_y = vertices[i + 1];
        vertices[i] = cos(zRot) * temp_x - sin(zRot) * temp_y;
        vertices[i + 1] = sin(zRot) * temp_x + cos(zRot) * temp_y;
    }
}

}  // namespace s21
