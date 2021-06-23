#include "jl3dviewer.h"
#include "ui_jl3dviewer.h"

JL3DViewer::JL3DViewer(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::JL3DViewer)
{
    ui->setupUi(this);
}

JL3DViewer::~JL3DViewer()
{
    delete ui;
}


void JL3DViewer::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0, 0, 0, 1);
}

void JL3DViewer::resizeGL(int w, int h)
{

}

void JL3DViewer::paintGL()
{
#ifdef XH_WIN
    glClearColor(0, 0, 0, 1);
    glLoadIdentity();

    // glTranslatef(-1, -1, 0);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0.5, 1, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(1, 0.5, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 1);
    glVertex3f(2, 0, 0);
    glVertex3f(1, 0.5, 0);
    glEnd();

    glBegin(GL_POLYGON); // 显示一个矩形，就使用GL_POLYGON

    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );      // P1 是红色
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f(  0.5,  0.5, -0.5 );      // P2 是绿色
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -0.5,  0.5, -0.5 );      // P3 是蓝色
    glColor3f( 1.0, 0.0, 1.0 );
    glVertex3f( -0.5, -0.5, -0.5 );      // P4 是紫色

    glEnd();
#endif
}

