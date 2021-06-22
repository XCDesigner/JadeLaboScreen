#include "jl3dviewer.h"
#include "ui_jl3dviewer.h"

JL3DViewer::JL3DViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JL3DViewer)
{
    ui->setupUi(this);
}

JL3DViewer::~JL3DViewer()
{
    delete ui;
}
