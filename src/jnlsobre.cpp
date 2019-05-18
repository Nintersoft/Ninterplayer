#include "jnlsobre.h"
#include "ui_jnlsobre.h"

jnlSobre::jnlSobre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::jnlSobre)
{
    ui->setupUi(this);
}

jnlSobre::~jnlSobre()
{
    delete ui;
}
