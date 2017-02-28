#include "itemlistamusica.h"
#include "ui_itemlistamusica.h"

itemListaMusica::itemListaMusica(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemListaMusica)
{
    ui->setupUi(this);
}

itemListaMusica::~itemListaMusica()
{
    delete ui;
}

void itemListaMusica::defineArtistaAlbum(const QString &artistaAlbum){
    ui->textoArtistaAlbum->setText(artistaAlbum);
}

void itemListaMusica::defineMusica(const QString &titulo){
    ui->textoTituloMusica->setText(titulo);
}

void itemListaMusica::defineArteAlbum(const QPixmap &arteAlbum){
    if (!arteAlbum.isNull()) ui->arteAlbum->setPixmap(arteAlbum);
}

void itemListaMusica::defineIndice(int indiceAtual){
    indice = indiceAtual;
}

int itemListaMusica::retornaIndice(){
    return indice;
}

void itemListaMusica::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void itemListaMusica::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) mousePressed = true;
    emit pressed();
}

void itemListaMusica::mouseReleaseEvent(QMouseEvent *event){
    if (mousePressed) emit clicked(mousePressed);
    if (event->button() == Qt::LeftButton) mousePressed = false;
    emit released();
}

void itemListaMusica::mouseDoubleClickEvent(QMouseEvent *){
    emit doubleClicked(indice);
}
