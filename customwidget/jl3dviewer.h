#ifndef JL3DVIEWER_H
#define JL3DVIEWER_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QtOpenGL/qgl.h>

namespace Ui {
class JL3DViewer;
}

class JL3DViewer : public QWidget
{
    Q_OBJECT

public:
    explicit JL3DViewer(QWidget *parent = nullptr);
    ~JL3DViewer();

private:
    Ui::JL3DViewer *ui;
};

#endif // JL3DVIEWER_H
