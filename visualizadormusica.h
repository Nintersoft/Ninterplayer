#ifndef VISUALIZADORMUSICA_H
#define VISUALIZADORMUSICA_H

#include <QWidget>
#include <QMainWindow>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaMetaData>

namespace Ui {
    class visualizadorMusica;
}

class visualizadorMusica : public QWidget
{
    Q_OBJECT

public:
    explicit visualizadorMusica(QWidget *parent = 0);
    void definirReprodutor(QMediaPlayer *rep, QMediaPlaylist *lista);
    ~visualizadorMusica();

private:
    Ui::visualizadorMusica *ui;
    QWidget* parent;
    QMediaPlayer* reprodutor;
    QMediaPlaylist* listaRep;

protected slots:
    void avancarMusica();
    void retrocederMusica();

public slots:
    void adquirirMetadados(QMediaPlayer::MediaStatus estado);
    void resizeEvent(QResizeEvent* evento);
};

#endif // VISUALIZADORMUSICA_H
