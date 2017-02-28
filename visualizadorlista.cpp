#include "visualizadorlista.h"
#include "ui_visualizadorlista.h"

visualizadorLista::visualizadorLista(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::visualizadorLista)
{
    ui->setupUi(this);
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    reprodutorTeste = new QMediaPlayer(this);
    connect(reprodutorTeste, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(adquirirMetadados(QMediaPlayer::MediaStatus)));
}

visualizadorLista::~visualizadorLista()
{
    delete ui;
}

void visualizadorLista::definirLista(QMediaPlaylist *lista){
    listaRep = lista;
}

void visualizadorLista::atualizarLista(){

    //IMPORTANTE ! Excluir ponteiros anteriores para criar novos

    /*if (itens != NULL){
        for(int i = 0; i < totalMidia; ++i){
            const int POSICAO_LISTA = i;
            disconnect(itens[POSICAO_LISTA], SIGNAL(doubleClicked(int)), listaRep, SLOT(setCurrentIndex(int)));
            delete itens[POSICAO_LISTA];
        }
        ui->arranjoLista->takeAt(0);
    }*/

    totalMidia = listaRep->mediaCount();
    midiaAtual = 0;
    if (totalMidia != 0) reprodutorTeste->setMedia(listaRep->media(midiaAtual));
}

void visualizadorLista::adquirirMetadados(QMediaPlayer::MediaStatus estado){
    if (estado != QMediaPlayer::EndOfMedia && !reprodutorTeste->isVideoAvailable()
            && estado == QMediaPlayer::LoadedMedia){

        const int POSICAO_LISTA = midiaAtual;

        itens = new itemListaMusica*[totalMidia];
        itens[midiaAtual] = new itemListaMusica(this);
        itens[midiaAtual]->defineIndice(POSICAO_LISTA);
        itens[midiaAtual]->defineMusica(reprodutorTeste->metaData(QMediaMetaData::Title).toString());
        itens[midiaAtual]->defineArtistaAlbum(reprodutorTeste->metaData(QMediaMetaData::Author).toString() + " - "
                                 + reprodutorTeste->metaData(QMediaMetaData::AlbumTitle).toString());
        itens[midiaAtual]->defineArteAlbum(QPixmap::fromImage(reprodutorTeste->metaData(QMediaMetaData::ThumbnailImage).value<QImage>()));
        itens[midiaAtual]->update();

        connect(itens[POSICAO_LISTA], SIGNAL(doubleClicked(int)), listaRep, SLOT(setCurrentIndex(int)));

        ui->arranjoLista->addWidget(itens[midiaAtual], midiaAtual, 0);

        if (midiaAtual < (totalMidia - 1)) reprodutorTeste->setMedia(listaRep->media(++midiaAtual));
        else{
             if (espacador == NULL) espacador = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
             ui->arranjoLista->addItem(espacador, totalMidia, 0);
        }
    }
}
