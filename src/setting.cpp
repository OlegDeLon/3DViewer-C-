#include "setting.h"

s21::Setting::Setting() {
  setDefaultOpenGLParameters();
  configReadFile();
}

s21::Setting::~Setting() { configWriteFile(); }

void s21::Setting::setDefaultOpenGLParameters() {
  type_vertex = 0, thickness_vertex = 1.0;
  red_vertex = 1.0, green_vertex = 0.0, blue_vertex = 0.0;
  type_border = 0, thickness_border = 3.0;
  red_border = 0.0, green_border = 0.0, blue_border = 1.0;
  red_background = 0.7, green_background = 1.0, blue_background = 1.0;
  perspective_type = 1;
}

void s21::Setting::configWriteFile() {
  std::ofstream fout;
  fout.open(f_str, std::ios_base::out | std::ios_base::trunc);
  if (fout.is_open()) {
    fout << type_vertex << " " << thickness_vertex << " " << red_vertex << " "
         << green_vertex << " " << blue_vertex << " ";
    fout << type_border << " " << thickness_border << " " << red_border << " "
         << green_border << " " << blue_border << " ";
    fout << red_background << " " << green_background << " " << blue_background
         << " " << perspective_type;
    fout.close();
  }
}

void s21::Setting::configReadFile() {
  std::ifstream fout;
  fout.open(f_str, std::ios_base::in);
  if (fout.is_open()) {
    fout >> type_vertex >> thickness_vertex >> red_vertex >> green_vertex >>
        blue_vertex;
    fout >> type_border >> thickness_border >> red_border >> green_border >>
        blue_border;
    fout >> red_background >> green_background >> blue_background >>
        perspective_type;
    fout.close();
  }
}
