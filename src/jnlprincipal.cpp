#include "jnlprincipal.h"
#include "ui_jnlprincipal.h"

jnlPrincipal::jnlPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::jnlPrincipal)
{
    ui->setupUi(this);

    ui->setupUi(this);
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    jnlSbr = new jnlSobre(this);

    connect(ui->actionSobre, SIGNAL(triggered(bool)), jnlSbr, SLOT(show()));
    connect(ui->actionSair, SIGNAL(triggered(bool)), this, SLOT(close()));

    videoPlayer = new QVideoWidget(this);
    videoPlayer->show();

    mediaPlayer = new QMediaPlayer(this);
    listaRep = new QMediaPlaylist(this);

    visualizadorMsc = new visualizadorMusica(this);
    visualizadorMsc->definirReprodutor(mediaPlayer, listaRep);

    visualizadorListaRep = new visualizadorLista(this);
    visualizadorListaRep->definirLista(listaRep);

    estadoRep = new estadoReprodutor(this);
    estadoRep->definirReprodutor(mediaPlayer);


    connect(ui->actionAbrir_arquivo_de_v_deo, SIGNAL(triggered(bool)), this, SLOT(abrirVideo()));
    connect(ui->actionAbrir_arquivo_de_udio, SIGNAL(triggered(bool)), this, SLOT(abrirAudio()));

    mediaPlayer->setVideoOutput(videoPlayer);
    videoPlayer->setMinimumSize(QSize(250, 200));
    ui->layout->addWidget(visualizadorMsc, 0, 0, 2, 1);
    ui->layout->addWidget(visualizadorListaRep, 0, 1);
    ui->layout->addWidget(estadoRep, 1, 1);
    videoPlayer->hide();
}

jnlPrincipal::~jnlPrincipal()
{
    delete ui;
}

void jnlPrincipal::abrirVideo()
{
    QString caminho = QDir::homePath() + "\\Videos";
    QString caminhoVideo = QFileDialog::getOpenFileName(this,
                                                       "Ninterplayer | Abrir arquivo de vídeo",
                                                       caminho,
                                                       "Arquivos de vídeo (*.mp4 *.wmv *.avi)");
    disconnect(mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(adquirirMetadados(QMediaPlayer::MediaStatus)));
    videoPlayer->show();
    visualizadorMsc->hide();
    mediaPlayer->setMedia(QUrl::fromUserInput(caminhoVideo));
    mediaPlayer->setVolume(100);
    mediaPlayer->play();
}

void jnlPrincipal::abrirAudio()
{
    QString caminho = QDir::homePath() + "\\Music";
    bool temMidia = false;
    QStringList caminhoAudios = QFileDialog::getOpenFileNames(this,
                                                             tr("Ninterplayer | Abrir arquivo de áudio"),
                                                             caminho,
                                                             tr("Arquivos de áudio (*.mp3 *.wma)"));
    for (int i = 0; i < caminhoAudios.size(); ++i){
        if (QFileInfo(caminhoAudios.at(i)).exists()){
            listaRep->addMedia(QUrl::fromUserInput(caminhoAudios.at(i)));
            temMidia = true;
        }
    }
    if (temMidia){
        connect(mediaPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), visualizadorMsc, SLOT(adquirirMetadados(QMediaPlayer::MediaStatus)));
        visualizadorListaRep->atualizarLista();
        videoPlayer->hide();
        mediaPlayer->setPlaylist(listaRep);
        visualizadorMsc->show();
        mediaPlayer->setVolume(100);
        mediaPlayer->play();
    }
}

void jnlPrincipal::resizeEvent(QResizeEvent *)
{
    if (this->width() <= 400){
        ui->layout->takeAt(ui->layout->indexOf(estadoRep));
        ui->layout->addWidget(estadoRep, 2, 0);
        visualizadorMsc->setMaximumWidth(400);
        visualizadorListaRep->setVisible(false);

    }
    else{
        ui->layout->takeAt(ui->layout->indexOf(estadoRep));
        ui->layout->addWidget(estadoRep, 1, 1);
        visualizadorMsc->setMaximumWidth(300);
        visualizadorListaRep->setVisible(true);
    }
}

void jnlPrincipal::keyPressEvent(QKeyEvent *event){
    if ((event->key() == Qt::Key_MediaPause || event->key() == Qt::Key_MediaPlay) && mediaPlayer->state() == QMediaPlayer::PlayingState){
        mediaPlayer->pause();
    }
    else if (event->key() == Qt::Key_MediaPlay &&
             (mediaPlayer->isAudioAvailable() || mediaPlayer->isVideoAvailable()))
                 mediaPlayer->play();
}
