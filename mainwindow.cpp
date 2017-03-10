#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->explorer = new fileExplorer();
    this->explorer->seed();
    this->root = explorer->getRaiz();
    this->selected = this->root;
    this->anterior = NULL;
    dibujar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::graphicsView()
{/*
    QGraphicsView * view = ui->display_graphicsView;

    QGraphicsScene * scene = new QGraphicsScene(view);

    view->setScene(scene);

    QGraphicsRectItem * rect = new QGraphicsRectItem(-10,-10,0,0);

    scene->addItem(rect);

    QGraphicsTextItem * text = scene->addText("hola");*/
}
void MainWindow::crearArchivos(QString nombre,int tipo)
{
    explorer->crearArchivo(selected,nombre.toStdString(),tipo);
    dibujar();
}

void MainWindow::dibujar()
{
    if(selected == root)
        ui->ruta_lbl->setText(QString::fromStdString(selected->getRuta())+"\\"+QString::fromStdString(selected->getNombre()));
    else
        ui->ruta_lbl->setText(QString::fromStdString(selected->getRuta()));

    Lista_Apuntador lista = explorer->listarArchivos(selected);

    cout<<endl<<endl<<"Lista de archivos-----------"<<selected->getRuta()<<endl;
    int paraX = 0;
    for (int x = 0; x< lista.getTamano(); x++)
    {
        archivo * temp = lista.obtener(x);
        QString name = QString::fromStdString(temp->getNombre());
        cout<<temp->getTipo()<<"--"<<temp->getNombre()<<"--"<<temp->getRuta()<<endl;

        paraX == 9 ? paraX = 0: false;
        if(temp->getTipo()=="Folder")
        {
            crearBotones(name,0,paraX,(x/9));
        }
        else
            crearBotones(name,1,paraX,(x/9));
        paraX+=1;
    }
}

void MainWindow::crearBotones(QString nombre,int tipo,int xPos, int yPos)
{
    int xSize = 70;
    int ySize = 70;
    int xPosIni = 190 + (xPos*xSize);
    int yPosIni = 80 + (yPos*ySize)+10;

    QPixmap pixmapFolder("C:\\Users\\renan\\Desktop\\FileSystemVisual\\FileSystem\\Resources\\Folder.png");
    QPixmap pixmapArchivo("C:\\Users\\renan\\Desktop\\FileSystemVisual\\FileSystem\\Resources\\File.png");

    QPushButton * boton = new QPushButton(this);
    boton->setGeometry(QRect(QPoint(xPosIni,yPosIni),QSize(xSize,ySize)));
    QIcon botonIcon((tipo==1 ? pixmapArchivo : pixmapFolder));
    boton->setIcon(botonIcon);
    boton->setIconSize(QSize(xSize-5,ySize-5));
    boton->show();
    boton->setAccessibleName(QString::number(tipo));
    boton->setObjectName(nombre);
    connect(boton,SIGNAL (pressed()),this,SLOT(handleButton()));
    ui->gridLayout->addWidget(boton,yPos,xPos);

}

void MainWindow::on_actionNuevo_Folder_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Nuevo Folder"),tr("Nombre del folder"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
        crearArchivos(text,0);
}

void MainWindow::on_actionNuevo_Archivo_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Nuevo Archivo"),tr("Nombre del archivo"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty())
        crearArchivos(text,1);
}

void MainWindow::on_actionCopiar_triggered()
{

}

void MainWindow::on_actionPegar_triggered()
{

}

void MainWindow::on_actionSalir_triggered()
{
    QCoreApplication::quit();
}
void MainWindow::imprimir(const QString name)
{
    cout<<name.toStdString()<<endl;
}

void MainWindow::handleButton()
{
    QPushButton* clickedButton = qobject_cast< QPushButton* >( sender() );
    if ( clickedButton )
    {
        const QString clickedButtonName = clickedButton->objectName();
        const QString tipo = clickedButton->accessibleName();
        imprimir(clickedButton->accessibleName());
        QMessageBox msgBox;
        msgBox.setText(clickedButtonName);
        msgBox.exec();
        if(tipo=="1")
        {
            archivo * ar = explorer->cargarArchivo(clickedButtonName.toStdString());
            archivoTexto * txt = (archivoTexto*)ar;
            bool ok;
            QString text = QInputDialog::getText(this, tr("Contenido del Archivo"),tr("Contenido"), QLineEdit::Normal,QString::fromStdString(txt->getContenido()), &ok);
            if (ok && !text.isEmpty())
                txt->setContenido(text.toStdString());
        }
        else if(tipo == "0")
        {
            archivo * ar = explorer->cargarArchivo(clickedButtonName.toStdString());
            folder * fol = (folder*)ar;
            anterior = selected;
            selected = fol;
            dibujar();
        }
    }

}
