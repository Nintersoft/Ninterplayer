#ifndef VISUALIZADORLISTA_H
#define VISUALIZADORLISTA_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QPushButton>
#include <QSpacerItem>

#include "itemlistamusica.h"

namespace Ui {
class visualizadorLista;
}

class visualizadorLista : public QWidget
{
    Q_OBJECT

public:
    explicit visualizadorLista(QWidget *parent = 0);
    ~visualizadorLista();

    void definirLista(QMediaPlaylist* lista);
    void atualizarLista();

    QMediaPlaylist* listaRep;
    QMediaPlayer* reprodutorTeste;

private:
    Ui::visualizadorLista *ui;

    int totalMidia = 0, midiaAtual = -1;
    itemListaMusica** itens = NULL;
    QSpacerItem* espacador = NULL;

public slots:
    void adquirirMetadados(QMediaPlayer::MediaStatus estado);
};

#endif // VISUALIZADORLISTA_H
