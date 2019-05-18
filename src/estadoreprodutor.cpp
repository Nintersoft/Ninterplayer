#include "estadoreprodutor.h"
#include "ui_estadoreprodutor.h"

estadoReprodutor::estadoReprodutor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::estadoReprodutor)
{
    ui->setupUi(this);
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::darkBlue);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    connect(ui->progresso, SIGNAL(sliderMoved(int)), this, SLOT(definirPosicao(int)));
}

estadoReprodutor::~estadoReprodutor()
{
    delete ui;
}

void estadoReprodutor::definirReprodutor(QMediaPlayer *rep){
    reprodutor = rep;

    connect(reprodutor, SIGNAL(durationChanged(qint64)), this, SLOT(atualizarMaxProg(qint64)));
    connect(reprodutor, SIGNAL(positionChanged(qint64)), this, SLOT(atualizarProg(qint64)));
}

void estadoReprodutor::atualizarProg(qint64 valor)
{
    ui->progresso->setValue(valor / 1000);
}

void estadoReprodutor::atualizarMaxProg(qint64 max)
{
    ui->progresso->setMaximum(max / 1000);
}

void estadoReprodutor::definirPosicao(int pos)
{
    reprodutor->setPosition(pos * 1000);
}
