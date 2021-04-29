#include "updateprogrebar.h"
#include "ui_updateprogrebar.h"

updateProgreBar::updateProgreBar(QWidget *parent) :
    JLWidget(parent),
    ui(new Ui::updateProgreBar)
{
    ui->setupUi(this);

    ui->quickWidget->setSource(QUrl("qrc:/qml/CircleProgressBar.qml"));
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    ui->quickWidget->setClearColor(QColor("#202023"));
}

updateProgreBar::~updateProgreBar()
{
    delete ui;
}

void updateProgreBar::show()
{
    QWidget::show();
}

void updateProgreBar::change(int Percent)
{
    ui->quickWidget->rootObject()->setProperty("currentPercent", Percent);
}
