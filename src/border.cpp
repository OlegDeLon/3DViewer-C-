#include "border.h"

#include <QDebug>

#include "ui_border.h"

Border::Border(QWidget *parent) : QDialog(parent), ui(new Ui::Border) {
  ui->setupUi(this);
}

Border::~Border() { delete ui; }

void Border::on_apply_border_clicked() { hide(); }

void Border::on_color_border_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color.isValid()) {
    red = color.redF();
    green = color.greenF();
    blue = color.blueF();
    ui->color_border->setStyleSheet(
        QString("background-color: %1;\nborder: 1px solid "
                "gray;\nborder-radius: 5px;")
            .arg(color.name()));
  }
  emit signalBorderColor(red, green, blue);
}

void Border::on_thickness_border_valueChanged(double arg1) {
  thickness_border = arg1;
  emit signalBorderThickness(thickness_border);
}

void Border::on_type_border_currentIndexChanged(int index) {
  type_border = index;
  emit signalBorderType(type_border);
}

void Border::setBorderType(int value) {
  type_border = value;
  ui->type_border->setCurrentIndex(type_border);
}

void Border::setBorderThickness(double value) {
  thickness_border = value;
  ui->thickness_border->setValue(thickness_border);
}

void Border::setBorderColor(double red, double green, double blue) {
  color_border.setRedF(red);
  color_border.setGreenF(green);
  color_border.setBlueF(blue);
  ui->color_border->setStyleSheet(
      QString(
          "background-color: %1;\nborder: 1px solid gray;\nborder-radius: 5px;")
          .arg(color_border.name()));
}
