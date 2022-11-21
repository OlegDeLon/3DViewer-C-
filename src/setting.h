#ifndef SRC_SETTING_H_
#define SRC_SETTING_H_

#include <fstream>
#include <iostream>

#include "QDir"
#include "QString"

namespace s21 {

class Setting {
 private:
  Setting();
  Setting(const Setting&);
  Setting& operator=(Setting&);
  ~Setting();

  int type_vertex;
  int type_border;
  int perspective_type;
  double thickness_vertex;
  double thickness_border;
  double red_vertex, green_vertex, blue_vertex;
  double red_border, green_border, blue_border;
  double red_background, green_background, blue_background;
  QString temp = QDir::homePath() + "/.config.conf";
  QByteArray f = temp.toLocal8Bit();
  char* f_str = f.data();

 public:
  static Setting& Instance() {
    static Setting instance;
    return instance;
  }

  void configWriteFile();
  void configReadFile();
  void setDefaultOpenGLParameters();

  int& getTypeVertex() { return type_vertex; }
  int& getTypeBorder() { return type_border; }
  int& getTypePerspective() { return perspective_type; }
  double& getThicknessVertex() { return thickness_vertex; }
  double& getThicknessBorder() { return thickness_border; }

  double& getRedVertex() { return red_vertex; }
  double& getGreenVertex() { return green_vertex; }
  double& getBlueVertex() { return blue_vertex; }

  double& getRedBorder() { return red_border; }
  double& getGreenBorder() { return green_border; }
  double& getBlueBorder() { return blue_border; }

  double& getRedBackground() { return red_background; }
  double& getGreenBackground() { return green_background; }
  double& getBlueBackground() { return blue_background; }
};
}  // namespace s21

#endif  // SRC_SETTING_H_
