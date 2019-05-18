#include "visualizadormusica.h"
#include "ui_visualizadormusica.h"

visualizadorMusica::visualizadorMusica(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::visualizadorMusica)
{
    ui->setupUi(this);

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    this->parent = parent;
}

visualizadorMusica::~visualizadorMusica()
{
    delete ui;
}

void visualizadorMusica::definirReprodutor(QMediaPlayer *rep,  QMediaPlaylist *lista){
    reprodutor = rep;
    listaRep = lista;
    connect(ui->barraVolume, SIGNAL(sliderMoved(int)), reprodutor, SLOT(setVolume(int)));
    connect(ui->botaoPausar, SIGNAL(clicked(bool)), reprodutor, SLOT(pause()));
    connect(ui->botaoReproduzir, SIGNAL(clicked(bool)), reprodutor, SLOT(play()));
    connect(ui->botaoProximo, SIGNAL(clicked(bool)), this, SLOT(avancarMusica()));
    connect(ui->botaoAnterior, SIGNAL(clicked(bool)), this, SLOT(retrocederMusica()));
}

void visualizadorMusica::adquirirMetadados(QMediaPlayer::MediaStatus estado){

    if (estado != QMediaPlayer::EndOfMedia && !reprodutor->isVideoAvailable()){
        qDebug() << reprodutor->availableMetaData();

        QPixmap arte = QPixmap::fromImage(reprodutor->metaData(QMediaMetaData::ThumbnailImage).value<QImage>());
        if (arte.isNull()) arte = QPixmap(":/imgs/np_cp_pad.png");
        arte = arte.scaled(this->size(), Qt::IgnoreAspectRatio);
        ui->arteAlbum->setPixmap(arte);

        parent->setWindowTitle(reprodutor->metaData(QMediaMetaData::Title).toString()  + " - " + reprodutor->metaData(QMediaMetaData::Author).toString() +
                               " | Ninterplayer");

        ui->tituloMusica->setText(tr("Título : ") + reprodutor->metaData(QMediaMetaData::Title).toString());
        ui->nomeArtista->setText(tr("Artista : ") + reprodutor->metaData(QMediaMetaData::Author).toString());
        ui->nomeAlbum->setText(tr("Álbum : ") + reprodutor->metaData(QMediaMetaData::AlbumTitle).toString());
        ui->anoAlbum->setText(tr("Ano : ") + reprodutor->metaData(QMediaMetaData::Year).toString());
        ui->faixaMusica->setText(tr("Faixa : ") + reprodutor->metaData(QMediaMetaData::TrackNumber).toString());
        ui->generoMusica->setText(tr("Gênero : ") + reprodutor->metaData(QMediaMetaData::Genre).toString());
        ui->classificacaoMusica->setText(tr("Classificação : ") + QString::number(reprodutor->metaData(QMediaMetaData::UserRating).toInt()/20) + tr("/5"));
    }
}

void visualizadorMusica::resizeEvent(QResizeEvent *event){
    if (reprodutor->isAudioAvailable()){
        QPixmap arte = QPixmap::fromImage(reprodutor->metaData(QMediaMetaData::ThumbnailImage).value<QImage>());
        arte = arte.scaled(this->size(), Qt::IgnoreAspectRatio);
        ui->arteAlbum->setPixmap(arte);
    }
    else {
        QPixmap arte = QPixmap(":/imgs/np_cp_pad.png");
        arte = arte.scaled(this->size(), Qt::IgnoreAspectRatio);
        ui->arteAlbum->setPixmap(arte);
    }

    QWidget::resizeEvent(event);
}

void visualizadorMusica::avancarMusica(){
    if (!listaRep->isEmpty() && listaRep->currentIndex() != (listaRep->mediaCount() - 1) ) listaRep->next();
}
void visualizadorMusica::retrocederMusica(){
    if (!listaRep->isEmpty() && listaRep->currentIndex() > 0 ) listaRep->previous();
}
