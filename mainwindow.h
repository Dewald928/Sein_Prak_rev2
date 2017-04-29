#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <complex> // om komplekse wiskunde te doen
#include <QVector>
#include <QList>
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

private slots:
    void on_btn_load_clicked();

    void on_btn_rgb_clicked();

    void on_btn_sobel_clicked();

    void on_btn_grey_clicked();

    void on_btn_recon_clicked();

    void on_btn_dft_clicked();

    void on_btn_idft_clicked();

private:
    Ui::MainWindow *ui;

    QImage *img_in, *img_red, *img_green, *img_blue, *img_grey, *img_dft_amp, *img_dft_phase, *img_idft;
    QImage *img_sobel_total[3];
    QImage *img_sobel_recon;

    //complex<double> *data; //complex datatype
    //complex<double> *dataout; //complex datatype
    QVector< complex < double > > complex_1D;
    QVector< QVector < complex < double > > > complex_2D;
    QVector< QVector < complex < double > > > inverse_2D;

    //idft 1-D Function
    void IDFT1();

    //dft 1-D Function
    void DFT1();

//    //fft 1-D function
//    complex<double> *fft1(complex<double> *data, unsigned int size, int log2n,  bool inverse);

//    //fft 2-D function
//    complex<double> **fft2(complex<double> **data, int r, int c, bool inverse);


    void sobel(QImage *img, int iteration);

    void resetgraphic();

    int screen_height;
    int screen_width;

    int h;
    int w;

    QColor curcolour;
    QColor sobel_colour[9];

    int xKernel;
    int yKernel;

    bool inverse = false;
};

#endif // MAINWINDOW_H
