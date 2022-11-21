#ifndef SRC_WIDGET_H_
#define SRC_WIDGET_H_

#include <QMainWindow>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QQuaternion>

#include "controller.h"

namespace s21 {
class widget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

 public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();
    using QOpenGLWidget::QOpenGLWidget;

    void setBackgroundColor(float red, float green, float blue);
    void setVertexColor(float red, float green, float blue);
    void setEdgeColor(float red, float green, float blue);
    void getModelObject(s21::Controller const &_object);
    void setProjectionType(int projection_type);
    void setLineWidth(int thickness_border);
    void setLineType(int type_border);
    void setPointType(int type_vertex);
    void setPointSize(double thickness_vertex);
    void scaling(double value);
    void shift_x(int value);
    void shift_y(int value);
    void shift_z(int value);
    void rotation_x(int value);
    void rotation_y(int value);
    void rotation_z(int value);

 protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    void initShaders();
    void initLine();
    void initVer();
    void initParametrs();
    void initObject();
    void Draw();
    void setGLProjection();
    QOpenGLShaderProgram program;

 private:
    s21::Controller object;
    QMatrix4x4 projection;
    QQuaternion rotation;
    GLsizei lines;
    GLfloat pointSize;
    QOpenGLBuffer arrayBuf, indexBuf;
    GLclampf backgroundRed, backgroundGreen, backgroundBlue;
    GLdouble edgeRed, edgeGreen, edgeBlue;
    GLdouble vertexRed, vertexGreen, vertexBlue;
    float aspect;
    int lineType, pointType, projection_ortho;
    double line_width;
    double prev_scale;
    double prev_move_x, prev_move_y, prev_move_z;
    double prev_rotate_x, prev_rotate_y, prev_rotate_z;
};
}  // namespace s21
#endif  // SRC_WIDGET_H_
