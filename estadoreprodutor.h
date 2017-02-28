#ifndef ESTADOREPRODUTOR_H
#define ESTADOREPRODUTOR_H

#include <QWidget>
#include <QPalette>
#include <QMediaPlayer>

namespace Ui {
class estadoReprodutor;
}

class estadoReprodutor : public QWidget
{
    Q_OBJECT

public:
    explicit estadoReprodutor(QWidget *parent = 0);
    void definirReprodutor(QMediaPlayer *rep);
    ~estadoReprodutor();

private:
    Ui::estadoReprodutor *ui;
    QMediaPlayer* reprodutor;

public slots:
    void atualizarProg(qint64);
    void atualizarMaxProg(qint64);
    void definirPosicao(int);
};

#endif // ESTADOREPRODUTOR_H
