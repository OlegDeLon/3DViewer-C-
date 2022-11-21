#ifndef SRC_VERTEX_H_
#define SRC_VERTEX_H_

#include <QColorDialog>
#include <QDialog>
#include <QPalette>

namespace Ui {
class Vertex;
}

class Vertex : public QDialog {
  Q_OBJECT

 public:
  explicit Vertex(QWidget *parent = nullptr);
  void setVertexType(int value);
  void setVertexThickness(double value);
  void setVertexColor(double red, double green, double blue);
  ~Vertex();

 private slots:

  void on_apply_vertex_clicked();
  void on_color_vertex_clicked();
  void on_thickness_vertex_valueChanged(double arg1);
  void on_type_vertex_currentIndexChanged(int index);

 private:
  float red;
  float green;
  float blue;
  double thickness_vertex;
  int type_vertex;
  QColor color_vertex;
  Ui::Vertex *ui;

 signals:
  void signalVertexColor(double red, double green, double blue);
  void signalVertexThickness(double thickness_vertex);
  void signalVertexType(int type_vertex);
};

#endif  // SRC_VERTEX_H_
