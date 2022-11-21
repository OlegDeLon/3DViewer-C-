#include "vertex.h"

#include "ui_vertex.h"

Vertex::Vertex(QWidget *parent) : QDialog(parent), ui(new Ui::Vertex) { ui->setupUi(this); }

Vertex::~Vertex() { delete ui; }

void Vertex::on_apply_vertex_clicked() { close(); }

void Vertex::on_color_vertex_clicked() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
    if (color.isValid()) {
        red = color.redF();
        green = color.greenF();
        blue = color.blueF();
        ui->color_vertex->setStyleSheet(
            QString("background-color: %1;\nborder: 1px solid gray;\nborder-radius: 5px;").arg(color.name()));
    }
    emit signalVertexColor(red, green, blue);
}

void Vertex::on_thickness_vertex_valueChanged(double arg1) {
    thickness_vertex = arg1;
    emit signalVertexThickness(thickness_vertex);
}

void Vertex::on_type_vertex_currentIndexChanged(int index) {
    type_vertex = index;
    emit signalVertexType(type_vertex);
}

void Vertex::setVertexType(int value) {
    type_vertex = value;
    ui->type_vertex->setCurrentIndex(type_vertex);
}

void Vertex::setVertexThickness(double value) {
    thickness_vertex = value;
    ui->thickness_vertex->setValue(thickness_vertex);
}

void Vertex::setVertexColor(double red, double green, double blue) {
    color_vertex.setRedF(red);
    color_vertex.setGreenF(green);
    color_vertex.setBlueF(blue);
    ui->color_vertex->setStyleSheet(
        QString("background-color: %1;\nborder: 1px solid gray;\nborder-radius: 5px;")
            .arg(color_vertex.name()));
}
