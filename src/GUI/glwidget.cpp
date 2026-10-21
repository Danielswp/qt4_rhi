#include "glwidget.h"
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

GLWidget::GLWidget(QWidget* parent)
    : QGLWidget(parent), m_vbo(0)
{
    setFocusPolicy(Qt::StrongFocus);

//    m_btn = new QPushButton("Test", this);
//    connect(m_btn, SIGNAL(clicked()), this, SLOT(onBtnClicked()));

    m_triangleColor[0] = 1.0f; m_triangleColor[1] = 0.0f;
    m_triangleColor[2] = 0.0f; m_triangleColor[3] = 1.0f;
}

GLWidget::~GLWidget()
{
    makeCurrent();
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_shader) delete m_shader;
    doneCurrent();
}

void GLWidget::onBtnClicked()
{
    qDebug() << "Btn clicked, change color";
    if (m_triangleColor[0] > 0.5f) {
        m_triangleColor[0] = 0.8f; m_triangleColor[1] = 0.0f;
    } else {
        m_triangleColor[0] = 1.0f; m_triangleColor[1] = 0.0f;
    }
    update();
}

void GLWidget::printOpenGLVersionInfo()
{
    qDebug() << "GL Version:" << (const char*)glGetString(GL_VERSION);
    qDebug() << "Vendor:" << (const char*)glGetString(GL_VENDOR);
}

void GLWidget::initializeGL()
{
    initializeGLFunctions();
    printOpenGLVersionInfo();

    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Shader (using QGLShaderProgram)
    m_shader = new QGLShaderProgram(this);

    if (!m_shader->addShaderFromSourceFile(QGLShader::Vertex, ":/resources/shaders/shader.vert.glsl"))
        qDebug() << "Vert Err:" << m_shader->log();
    if (!m_shader->addShaderFromSourceFile(QGLShader::Fragment, ":/resources/shaders/shader.frag.glsl"))
        qDebug() << "Frag Err:" << m_shader->log();
    if (!m_shader->link()) qDebug() << "Link Err:" << m_shader->log();

    // VBO only (NO VAO)
    float vertices[] = {
        -0.5f,  0.0f, 0.0f,
         0.5f,  0.0f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!m_shader) return;
    m_shader->bind();

    // Set uniform (vec4)
    m_shader->setUniformValue("uColor",
        m_triangleColor[0], m_triangleColor[1],
        m_triangleColor[2], m_triangleColor[3]);

    // Bind VBO & setup attrib manually (No VAO)
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    m_shader->enableAttributeArray(0);
    m_shader->setAttributeBuffer(0, GL_FLOAT, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_shader->disableAttributeArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_shader->release();
}

void GLWidget::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_W: qDebug() << "W"; break;
    case Qt::Key_S: qDebug() << "S"; break;
    case Qt::Key_A: qDebug() << "A"; break;
    case Qt::Key_D: qDebug() << "D"; break;
    case Qt::Key_Escape: setFocus(); break;
    default: QGLWidget::keyPressEvent(event);
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent* event)
{
    QGLWidget::keyReleaseEvent(event);
}
