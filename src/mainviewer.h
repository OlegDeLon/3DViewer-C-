#ifndef SRC_MAINVIEWER_H_
#define SRC_MAINVIEWER_H_

#include <QColorDialog>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QScopedPointer>
#include <QSlider>
#include <QTimer>

#include "border.h"
#include "controller.h"
#include "perspective.h"
#include "qgifimage.h"
#include "qgifimage_p.h"
#include "save.h"
#include "setting.h"
#include "vertex.h"
#include "widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainViewer;
}
QT_END_NAMESPACE

class glView;
class MainViewer : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainViewer(QWidget *parent = nullptr);
  ~MainViewer();

 private:
  Ui::MainViewer *ui;
  s21::Controller object;
  Perspective *window_persp;
  Vertex *window_vertex;
  Border *window_border;
  QString file_name;
  glView *window_glView;
  Save *window_save;
  unsigned int edges_counter;
  unsigned int vertices_counter;
  void printInfoAboutFile(QString FileName);
  void setSlidersPosition();
  void setOpenGLParameters();
  double xMin, xMax;
  double yMin, yMax;
  double zMin, zMax;
  QTimer *timer;
  QGifImage *gif;

 private slots:
  void on_file_open_clicked();
  void on_edit_background_clicked();
  void on_edit_perspective_clicked();
  void on_edit_vertex_clicked();
  void on_edit_border_clicked();
  void on_rotate_x_box_valueChanged(int value);
  void on_rotate_y_box_valueChanged(int value);
  void on_rotate_z_box_valueChanged(int value);
  void on_scale_valueChanged(double value);
  void on_shift_x_box_valueChanged(int value);
  void on_shift_y_box_valueChanged(int value);
  void on_shift_z_box_valueChanged(int value);
  void gif_slot();
  void on_save_file_clicked();

 public slots:
  void slotVertexColor(double red, double green, double blue);
  void slotBorderColor(double red, double green, double blue);
  void slotBorderThickness(double thickness_border);
  void slotBorderType(int type_border);
  void slotVertexThickness(double value);
  void slotVertexType(int value);
  void slotPerspectiveType(int value);
  void slotSaveType(int type_save);
};
#endif  // SRC_MAINVIEWER_H_
