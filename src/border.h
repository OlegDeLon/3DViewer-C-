#ifndef SRC_BORDER_H_
#define SRC_BORDER_H_
#include <QColorDialog>
#include <QDialog>
#include <QPalette>

namespace Ui {
class Border;
}

class Border : public QDialog {
  Q_OBJECT

 public:
  explicit Border(QWidget *parent = nullptr);
  void setBorderType(int value);
  void setBorderThickness(double value);
  void setBorderColor(double red, double green, double blue);
  ~Border();

 private slots:
  void on_apply_border_clicked();
  void on_color_border_clicked();
  void on_thickness_border_valueChanged(double arg1);
  void on_type_border_currentIndexChanged(int index);

 private:
  float red;
  float green;
  float blue;
  double thickness_border;
  int type_border;
  QColor color_border;
  Ui::Border *ui;

 signals:
  void signalBorderColor(double red, double green, double blue);
  void signalBorderThickness(double thickness_border);
  void signalBorderType(int type_border);
};

#endif  // SRC_BORDER_H_
