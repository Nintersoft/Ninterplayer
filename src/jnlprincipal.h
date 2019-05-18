#ifndef JNLPRINCIPAL_H
#define JNLPRINCIPAL_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QSlider>
#include <QLabel>
#include <QLayoutItem>
#include <QFileDialog>
#include <QTimer>
#include <QPalette>

#include "jnlsobre.h"
#include "visualizadormusica.h"
#include "estadoreprodutor.h"
#include "visualizadorlista.h"

namespace Ui {
class jnlPrincipal;
}

class jnlPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit jnlPrincipal(QWidget *parent = 0);
    ~jnlPrincipal();

private:
    Ui::jnlPrincipal *ui;

    jnlSobre* jnlSbr;
    visualizadorMusica* visualizadorMsc;
    visualizadorLista* visualizadorListaRep;
    estadoReprodutor* estadoRep;
    QVideoWidget* videoPlayer;
    QMediaPlayer* mediaPlayer;
    QMediaPlaylist* listaRep;
    QSlider* progresso;
    QTimer* atualizador;

protected:
    void resizeEvent(QResizeEvent*);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void abrirVideo();
    void abrirAudio();

};

#endif // JNLPRINCIPAL_H
