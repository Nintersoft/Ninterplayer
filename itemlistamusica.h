#ifndef ITEMLISTAMUSICA_H
#define ITEMLISTAMUSICA_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class itemListaMusica;
}

class itemListaMusica : public QWidget
{
    Q_OBJECT

public:
    explicit itemListaMusica(QWidget *parent = 0);
    ~itemListaMusica();

    void defineMusica(const QString &titulo);
    void defineArtistaAlbum(const QString &artistaAlbum);
    void defineArteAlbum(const QPixmap &arteAlbum);
    void defineIndice(int indiceAtual);
    int retornaIndice();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent*);

signals:
    void pressed();
    void released();
    void clicked(bool);
    void doubleClicked(int);

private:
    Ui::itemListaMusica *ui;
    bool mousePressed = false;
    int indice;
};

#endif // ITEMLISTAMUSICA_H
