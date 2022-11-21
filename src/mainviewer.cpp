#include "mainviewer.h"

#include <QDebug>
#include <fstream>
#include <iostream>

#include "ui_mainviewer.h"
#include "widget.h"

MainViewer::MainViewer(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainViewer) {
  ui->setupUi(this);
  ui->openGLWidget->setBackgroundColor(
      s21::Setting::Instance().getRedBackground(),
      s21::Setting::Instance().getGreenBackground(),
      s21::Setting::Instance().getBlueBackground());
}

MainViewer::~MainViewer() { delete ui; }

void MainViewer::on_file_open_clicked() {
  QString FileName = QFileDialog::getOpenFileName(
      this, "Open a file", QDir::homePath(), "Object (*.obj)");
  if (FileName.size() != 0) {
    QByteArray f = FileName.toLocal8Bit();
    char* f_str = f.data();
    object.load_object_model(f_str);
    printInfoAboutFile(FileName);
    setOpenGLParameters();
    setSlidersPosition();
    ui->openGLWidget->getModelObject(object);
  }
}

void MainViewer::printInfoAboutFile(QString FileName) {
  QString result_vertex = QString::fromLocal8Bit(
      std::to_string(object.get_vertices_count()).c_str());
  QString result_edge =
      QString::fromLocal8Bit(std::to_string(object.get_index_count()).c_str());
  QStringList parts = FileName.split("/");
  QString lastBit = parts.at(parts.size() - 1);
  ui->count_vertex->setText(result_vertex);
  ui->count_border->setText(result_edge);
  ui->file_name->setText(lastBit);
}

void MainViewer::setOpenGLParameters() {
  ui->openGLWidget->rotation_x(0);
  ui->openGLWidget->rotation_y(0);
  ui->openGLWidget->rotation_z(0);
  ui->openGLWidget->shift_x(0);
  ui->openGLWidget->shift_y(0);
  ui->openGLWidget->shift_z(0);
  ui->openGLWidget->scaling(1);
  ui->openGLWidget->setLineWidth(s21::Setting::Instance().getThicknessBorder());
  ui->openGLWidget->setLineType(s21::Setting::Instance().getTypeBorder());
  ui->openGLWidget->setEdgeColor(s21::Setting::Instance().getRedBorder(),
                                 s21::Setting::Instance().getGreenBorder(),
                                 s21::Setting::Instance().getBlueBorder());
  ui->openGLWidget->setPointSize(s21::Setting::Instance().getThicknessVertex());
  ui->openGLWidget->setPointType(s21::Setting::Instance().getTypeVertex());
  ui->openGLWidget->setVertexColor(s21::Setting::Instance().getRedVertex(),
                                   s21::Setting::Instance().getGreenVertex(),
                                   s21::Setting::Instance().getBlueVertex());
  ui->openGLWidget->setProjectionType(
      s21::Setting::Instance().getTypePerspective());
  ui->openGLWidget->setBackgroundColor(
      s21::Setting::Instance().getRedBackground(),
      s21::Setting::Instance().getGreenBackground(),
      s21::Setting::Instance().getBlueBackground());
}

void MainViewer::setSlidersPosition() {
  ui->shift_x_box->setValue(0);
  ui->shift_y_box->setValue(0);
  ui->shift_z_box->setValue(0);
  ui->scale->setValue(1);
  ui->rotate_x_box->setValue(0);
  ui->rotate_y_box->setValue(0);
  ui->rotate_z_box->setValue(0);
}

void MainViewer::on_edit_background_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color.isValid()) {
    s21::Setting::Instance().getRedBackground() = color.redF();
    s21::Setting::Instance().getGreenBackground() = color.greenF();
    s21::Setting::Instance().getBlueBackground() = color.blueF();
    ui->openGLWidget->setBackgroundColor(
        s21::Setting::Instance().getRedBackground(),
        s21::Setting::Instance().getGreenBackground(),
        s21::Setting::Instance().getBlueBackground());
  }
}

void MainViewer::on_edit_perspective_clicked() {
  window_persp = new Perspective(this);

  window_persp->setGeometry(this->x() + 685, this->y() + 670,
                            window_persp->width(), window_persp->height());
  window_persp->setModal(true);
  connect(window_persp, &Perspective::signalPerspectiveType, this,
          &MainViewer::slotPerspectiveType);
  window_persp->exec();
}

void MainViewer::on_edit_vertex_clicked() {
  window_vertex = new Vertex(this);
  window_vertex->setGeometry(this->x() + 228, this->y() + 585,
                             window_vertex->width(), window_vertex->height());
  window_vertex->setModal(true);
  window_vertex->setVertexType(s21::Setting::Instance().getTypeVertex());
  window_vertex->setVertexThickness(
      s21::Setting::Instance().getThicknessVertex());
  window_vertex->setVertexColor(s21::Setting::Instance().getRedVertex(),
                                s21::Setting::Instance().getGreenVertex(),
                                s21::Setting::Instance().getBlueVertex());
  connect(window_vertex, &Vertex::signalVertexColor, this,
          &MainViewer::slotVertexColor);
  connect(window_vertex, &Vertex::signalVertexThickness, this,
          &MainViewer::slotVertexThickness);
  connect(window_vertex, &Vertex::signalVertexType, this,
          &MainViewer::slotVertexType);
  window_vertex->exec();
}

void MainViewer::on_edit_border_clicked() {
  window_border = new Border(this);
  window_border->setGeometry(this->x() + 0, this->y() + 585,
                             window_border->width(), window_border->height());
  window_border->setModal(true);
  window_border->setBorderThickness(
      s21::Setting::Instance().getThicknessBorder());
  window_border->setBorderType(s21::Setting::Instance().getTypeBorder());
  window_border->setBorderColor(s21::Setting::Instance().getRedBorder(),
                                s21::Setting::Instance().getGreenBorder(),
                                s21::Setting::Instance().getBlueBorder());
  connect(window_border, &Border::signalBorderColor, this,
          &MainViewer::slotBorderColor);
  connect(window_border, &Border::signalBorderThickness, this,
          &MainViewer::slotBorderThickness);
  connect(window_border, &Border::signalBorderType, this,
          &MainViewer::slotBorderType);
  window_border->exec();
}

void MainViewer::on_rotate_x_box_valueChanged(int value) {
  ui->openGLWidget->rotation_x(value);
  ui->openGLWidget->update();
}

void MainViewer::on_rotate_y_box_valueChanged(int value) {
  ui->openGLWidget->rotation_y(value);
  ui->openGLWidget->update();
}

void MainViewer::on_rotate_z_box_valueChanged(int value) {
  ui->openGLWidget->rotation_z(value);
  ui->openGLWidget->update();
}

void MainViewer::on_scale_valueChanged(double value) {
  ui->openGLWidget->scaling(value);
  ui->openGLWidget->update();
}

void MainViewer::on_shift_x_box_valueChanged(int value) {
  ui->openGLWidget->shift_x(value);
  ui->openGLWidget->update();
}

void MainViewer::on_shift_y_box_valueChanged(int value) {
  ui->openGLWidget->shift_y(value);
  ui->openGLWidget->update();
}

void MainViewer::on_shift_z_box_valueChanged(int value) {
  ui->openGLWidget->shift_z(value);
  ui->openGLWidget->update();
}

void MainViewer::slotVertexColor(double red, double green, double blue) {
  s21::Setting::Instance().getRedVertex() = red;
  s21::Setting::Instance().getGreenVertex() = green;
  s21::Setting::Instance().getBlueVertex() = blue;
  ui->openGLWidget->setVertexColor(red, green, blue);
}

void MainViewer::slotBorderColor(double red, double green, double blue) {
  s21::Setting::Instance().getRedBorder() = red;
  s21::Setting::Instance().getGreenBorder() = green;
  s21::Setting::Instance().getBlueBorder() = blue;
  ui->openGLWidget->setEdgeColor(red, green, blue);
}

void MainViewer::slotBorderThickness(double value) {
  s21::Setting::Instance().getThicknessBorder() = value;
  ui->openGLWidget->setLineWidth(value);
}

void MainViewer::slotVertexThickness(double value) {
  s21::Setting::Instance().getThicknessVertex() = value;
  ui->openGLWidget->setPointSize(value);
}

void MainViewer::slotVertexType(int value) {
  s21::Setting::Instance().getTypeVertex() = value;
  ui->openGLWidget->setPointType(value);
}

void MainViewer::slotBorderType(int value) {
  s21::Setting::Instance().getTypeBorder() = value;
  ui->openGLWidget->setLineType(value);
}

void MainViewer::slotPerspectiveType(int value) {
  s21::Setting::Instance().getTypePerspective() = value;
  ui->openGLWidget->setProjectionType(value);
}

void MainViewer::slotSaveType(int type_save) {
  if (type_save == 0) {
    QImage image = ui->openGLWidget->grabFramebuffer();
    QString FileName = QFileDialog::getSaveFileName(
        this, "Open a file", QDir::homePath(), "BMP (*.bmp);; JPEG(*.jpeg)");
    if (!FileName.isNull() && !FileName.isEmpty()) {
      image.save(FileName);
    }
  } else {
    gif = new QGifImage(QSize(640, 480));
    gif->setDefaultDelay(100);
    timer = new QTimer(this);
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(gif_slot()));
  }
}

void MainViewer::gif_slot() {
  if (gif->frameCount() < 50) {
    QImage image;
    image = ui->openGLWidget->grabFramebuffer();
    image =
        image.scaled(640, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    gif->addFrame(image);
  } else {
    QString dir = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), "/home",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString FileName = ui->file_name->text();
    FileName.resize(FileName.count() - 4);
    gif->save(dir + "/" + FileName + ".gif");
    timer->stop();
    delete gif;
  }
}

void MainViewer::on_save_file_clicked() {
  window_save = new Save(this);
  window_save->setGeometry(this->x() + 915, this->y() + 630,
                           window_save->width(), window_save->height());
  window_save->setModal(true);
  connect(window_save, &Save::signalSaveType, this, &MainViewer::slotSaveType);
  window_save->exec();
}
