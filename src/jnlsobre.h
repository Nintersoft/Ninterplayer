#ifndef JNLSOBRE_H
#define JNLSOBRE_H

#include <QMainWindow>

namespace Ui {
class jnlSobre;
}

class jnlSobre : public QMainWindow
{
    Q_OBJECT

public:
    explicit jnlSobre(QWidget *parent = 0);
    ~jnlSobre();

private:
    Ui::jnlSobre *ui;
};

#endif // JNLSOBRE_H
