#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>

#include "fileExplorer.h"
#include "Lista_Apuntador.h"

#include <QMainWindow>
#include <QPushButton>
#include <QDialog>
#include <QInputDialog>
#include <QDir>
#include <QCoreApplication>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QMessageBox>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPushButton * arreglo;
    private slots:
        void on_actionNuevo_Archivo_triggered();

        void on_actionNuevo_Folder_triggered();

        void on_actionCopiar_triggered();

        void on_actionPegar_triggered();

        void on_actionSalir_triggered();

        void handleButton();

private:
    Ui::MainWindow *ui;
    void graphicsView();
    void crearArchivos(QString nombre,int tipo);
    void crearBotones(QString nombre, int tipo, int xPos, int yPos);
    void dibujar();
    void imprimir(const QString name);
    folder * root;
    folder * selected;
    folder * anterior;
    fileExplorer * explorer;
};

#endif // MAINWINDOW_H
