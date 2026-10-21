#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLFunctions>
#include <QGLShaderProgram>

#include <QPushButton>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>

#include <GL/glu.h>

class GLWidget : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget* parent = 0);
    ~GLWidget();

    void printOpenGLVersionInfo();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

protected slots:
    void onBtnClicked();

private:
    GLuint m_vao;
    GLuint m_vbo;

    QGLShaderProgram* m_shader;

    QPushButton* m_btn;

    float m_triangleColor[4];   // r, g, b, a
};

#endif // GLWIDGET_H
