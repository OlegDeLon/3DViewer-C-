#include "widget.h"

namespace s21 {
widget::widget(QWidget* parent) : QOpenGLWidget(parent), indexBuf(QOpenGLBuffer::IndexBuffer) {
    initParametrs();
}

widget::~widget() {
    makeCurrent();
    doneCurrent();
    arrayBuf.destroy();
    indexBuf.destroy();
}

void widget::initializeGL() {
    initializeOpenGLFunctions();
    initParametrs();
    glLineStipple(1, 0x00F0);
    initShaders();
    arrayBuf.create();
    indexBuf.create();
}

void widget::initParametrs() {
    prev_scale = 1;
    prev_move_x = 0;
    prev_move_y = 0;
    prev_move_z = 0;
    prev_rotate_x = 0;
    prev_rotate_y = 0;
    prev_rotate_z = 0;
    projection_ortho = 0;
    aspect = 0;
    lineType = 0;
    pointType = 0;
    line_width = 0;
}

void widget::initShaders() {
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh")) close();
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh")) close();
    if (!program.link()) close();
    if (!program.bind()) close();
}

void widget::resizeGL(int w, int h) {
    aspect = qreal(w) / qreal(h ? h : 1);
    setGLProjection();
}

void widget::setGLProjection() {
    projection.setToIdentity();
    if (this->projection_ortho == 1) {
        projection.ortho(-8, 8, -6, 6, -10, 10);
    } else {
        projection.perspective(40, aspect, 0.1f, 20.0f);
    }
}

void widget::paintGL() {
    glClearColor(backgroundRed, backgroundGreen, backgroundBlue, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 matrix;
    matrix.translate(-0.1, -0.1, -5.0);
    matrix.rotate(60, 0, 0, 0);
    matrix.scale(0.7);
    program.bind();
    program.setUniformValue("qt_ModelViewProjectionMatrix", projection * matrix);
    initObject();
    Draw();
    program.release();
}

void widget::initObject() {
    QVector<QVector3D> vertices1;
    std::vector<double> vertices = object.get_vertices();
    std::vector<GLuint> indices = object.get_index();
    for (int i = 0; i < vertices.size(); i += 3) {
        vertices1.push_back(QVector3D(vertices[i], vertices[i + 1], vertices[i + 2]));
    }
    arrayBuf.bind();
    arrayBuf.allocate(vertices1.data(), sizeof(QVector3D) * vertices1.size());
    arrayBuf.release();

    indexBuf.bind();
    indexBuf.allocate(indices.data(), sizeof(GLuint) * indices.size());
    indexBuf.release();
    lines = indices.size();
}

void widget::Draw() {
    arrayBuf.bind();
    program.bind();
    int offset = 0;
    int vertexLocation = program.attributeLocation("qt_Vertex");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(QVector3D));

    offset += sizeof(QVector3D);

    int texcoordLocation = program.attributeLocation("qt_MultiTexCoord0");
    program.enableAttributeArray(texcoordLocation);
    program.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(QVector3D));

    initVer();
    indexBuf.bind();
    glDrawElements(GL_POINTS, lines, GL_UNSIGNED_INT, 0);

    initLine();
    glDrawElements(GL_LINES, lines, GL_UNSIGNED_INT, 0);
    arrayBuf.release();
    indexBuf.release();
}

void widget::initVer() {
    program.setUniformValue("result_color", QVector4D(vertexRed, vertexGreen, vertexBlue, 1));
    if ((pointType != 0)) {
        glPointSize(pointSize * 2);
        if (pointType == 1) {
            glEnable(GL_POINT_SMOOTH);
        } else if (pointType == 2) {
            glDisable(GL_POINT_SMOOTH);
        }
    } else {
        glPointSize(0.01);
    }
}

void widget::initLine() {
    program.setUniformValue("result_color", QVector4D(edgeRed, edgeGreen, edgeBlue, 1));
    glLineWidth(line_width);
    if (lineType == 1) {
        glEnable(GL_LINE_STIPPLE);
    } else {
        glDisable(GL_LINE_STIPPLE);
    }
}

void widget::setBackgroundColor(float red, float green, float blue) {
    backgroundRed = (GLclampf)red;
    backgroundGreen = (GLclampf)green;
    backgroundBlue = (GLclampf)blue;

    update();
}

void widget::setVertexColor(float red, float green, float blue) {
    vertexRed = (GLclampf)red;
    vertexGreen = (GLclampf)green;
    vertexBlue = (GLclampf)blue;

    update();
}

void widget::setEdgeColor(float red, float green, float blue) {
    edgeRed = (GLclampf)red;
    edgeGreen = (GLclampf)green;
    edgeBlue = (GLclampf)blue;

    update();
}

void widget::getModelObject(s21::Controller const& _object) {
    object = _object;
    update();
}

void widget::setProjectionType(int projection_type) {
    projection_ortho = projection_type;
    setGLProjection();
    update();
}
void widget::setLineWidth(int thickness_border) {
    line_width = thickness_border;
    update();
}

void widget::setLineType(int type_border) {
    lineType = type_border;
    update();
}

void widget::setPointType(int type_vertex) {
    pointType = type_vertex;
    update();
}

void widget::setPointSize(double thickness_vertex) {
    pointSize = thickness_vertex;
    update();
}

void widget::scaling(double value) {
    if (value != 0.0) {
        object.scale_(value / prev_scale);
        prev_scale = value;
    }
}

void widget::shift_x(int value) {
    object.move_x_((value - prev_move_x) / 10);
    prev_move_x = value;
}

void widget::shift_y(int value) {
    object.move_y_((value - prev_move_y) / 10);
    prev_move_y = value;
}

void widget::shift_z(int value) {
    object.move_z_((value - prev_move_z) / 10);
    prev_move_z = value;
}

void widget::rotation_x(int value) {
    object.rotation_x_((value - prev_rotate_x) / 57);
    prev_rotate_x = value;
}

void widget::rotation_y(int value) {
    object.rotation_y_((value - prev_rotate_y) / 57);
    prev_rotate_y = value;
}

void widget::rotation_z(int value) {
    object.rotation_z_((value - prev_rotate_z) / 57);
    prev_rotate_z = value;
}

}  // namespace s21
