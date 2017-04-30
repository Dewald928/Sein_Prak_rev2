#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QRect>
#include <QDebug>
#include <QColor>
#include <math.h>
#include <complex>
#include <iostream>
#include <QVector>
#include <time.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//load image
void MainWindow::on_btn_load_clicked()
{
    //load image
    img_in = new QImage;
    img_in->load(":/img/deadpool2.jpg");

    h = img_in->height();
    w = img_in->width();


    //displays
    QLabel *l = new QLabel(this);
    l->setPixmap(QPixmap::fromImage(*img_in));
    l->setMinimumWidth(img_in->width());
    l->setMinimumHeight(img_in->height());
    l->move(20,20);
    l->show();
    ui->gridLayout_5->addWidget(l);


}

void MainWindow::on_btn_rgb_clicked()
{
    //initializes images
    img_red = new QImage(w,h,img_in->format());
    img_green = new QImage(w,h,img_in->format());
    img_blue = new QImage(w,h,img_in->format());

    //make rgb images
    int curcolourvalue;
    for (int x = 0;x < w;x++)
    {
        for (int y = 0;y < h;y++)
        {
            curcolourvalue = qRed(img_in->pixel(x,y));
            img_red->setPixel(x,y,qRgb(curcolourvalue,0,0));

            curcolourvalue = qGreen(img_in->pixel(x,y));
            img_green->setPixel(x,y,qRgb(0,curcolourvalue,0));

            curcolourvalue = qBlue(img_in->pixel(x,y));
            img_blue->setPixel(x,y,qRgb(0,0,curcolourvalue));
        }
    }

    //displays
    QLabel *r = new QLabel(this);
    r->setPixmap(QPixmap::fromImage(*img_red));
    r->setMinimumWidth(w);
    r->setMinimumHeight(h);
    r->move(20,20+h);
    r->show();
    ui->gridLayout_5->addWidget(r);

    QLabel *g = new QLabel(this);
    g->setPixmap(QPixmap::fromImage(*img_green));
    g->setMinimumWidth(w);
    g->setMinimumHeight(h);
    g->move(20,20+h*2);
    g->show();
    ui->gridLayout_5->addWidget(g);

    QLabel *b = new QLabel(this);
    b->setPixmap(QPixmap::fromImage(*img_blue));
    b->setMinimumWidth(w);
    b->setMinimumHeight(h);
    b->move(20,20+h*3);
    b->show();
    ui->gridLayout_5->addWidget(b);
}

void MainWindow::on_btn_sobel_clicked()
{
    sobel(img_red,0);
    sobel(img_green,1);
    sobel(img_blue,2);

}

void MainWindow::sobel(QImage *img, int iteration)
{
    //initialize vertical, horizontal and total edges
    QImage *img_sobel_hor = new QImage(w,h,img_in->format());
    QImage *img_sobel_ver = new QImage(w,h,img_in->format());
    img_sobel_total[iteration] = new QImage(w,h,img_in->format());

    //initialize kernels
    int i =0;
    int G,Gx,Gy;
    int gx[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int gy[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    //times kernel with each pixel
    for (int x = 1; x < w-1; ++x)
    {
        for (int y = 1; y < h-1; ++y)
        {
            i  = 0;
            Gx = 0;
            Gy = 0;
            G  = 0;
            for (int dy = -1; dy <= 1; ++dy)
            {
                for (int dx = -1; dx <= 1; ++dx)
                {
                    Gx += qGray(img->pixel(x+dx,y+dy)) * gx[i]; //  <--- Het jou fout sommer vinnig gekry ;P
                    Gy += qGray(img->pixel(x+dx,y+dy)) * gy[i]; //  <--- dx was dy
                    i++;
                }
            }
            G = sqrt(Gx*Gx + Gy*Gy);
            img_sobel_ver->setPixel(x,y,Gy);
            img_sobel_hor->setPixel(x,y,Gx);
            img_sobel_total[iteration]->setPixel(x,y,qRgb(G,G,G));
        }
    }

    //display horizontal edges
    QLabel *hor_edge = new QLabel(this);
    hor_edge->setPixmap(QPixmap::fromImage(*img_sobel_hor));
    hor_edge->setMinimumWidth(w);
    hor_edge->setMinimumHeight(h);
    hor_edge->move(20+w,20+h);
    hor_edge->show();
    ui->gridLayout_5->addWidget(hor_edge,iteration+1, 1);


    //display vertical edges
    QLabel *ver_edge = new QLabel(this);
    ver_edge->setPixmap(QPixmap::fromImage(*img_sobel_ver));
    ver_edge->setMinimumWidth(w);
    ver_edge->setMinimumHeight(h);
    ver_edge->move(20+2*w,20+h);
    ver_edge->show();
    ui->gridLayout_5->addWidget(ver_edge,iteration+1, 2);


    //display total edges
    QLabel *tot_edge = new QLabel(this);
    tot_edge->setPixmap(QPixmap::fromImage(*img_sobel_total[iteration]));
    tot_edge->setMinimumWidth(w);
    tot_edge->setMinimumHeight(h);
    tot_edge->move(20+3*w,20+h);
    tot_edge->show();
    ui->gridLayout_5->addWidget(tot_edge, iteration+1, 3);


}

void MainWindow::on_btn_grey_clicked()
{
    img_grey = new QImage;
    *img_grey = img_in->convertToFormat(QImage::Format_Grayscale8);
    bool b = img_grey->save("deadpool_gray.png");

    QLabel *gr = new QLabel(this);
    gr->setPixmap(QPixmap::fromImage(*img_grey));
    gr->setMinimumWidth(w);
    gr->setMinimumHeight(h);
    gr->move(20,20+h*6);
    gr->show();
    ui->gridLayout_5->addWidget(gr,6,0);


}

void MainWindow::on_btn_recon_clicked()
{
    //initialize image
    img_sobel_recon = new QImage(w,h,img_in->format());
    int r_edge = 0;
    int g_edge = 0;
    int b_edge = 0;


    //add r g b total of sobels togehter
    for (int y = 1; y < h-1; ++y)
    {
        for (int x = 1; x < w-1; ++x)
        {
            r_edge = qGray(img_sobel_total[0]->pixel(x,y));
            g_edge = qGray(img_sobel_total[1]->pixel(x,y));
            b_edge = qGray(img_sobel_total[2]->pixel(x,y));
            img_sobel_recon->setPixel(x,y,qRgb(r_edge,g_edge,b_edge));
        }
    }

    QLabel *sobel = new QLabel(this);
    sobel->setPixmap(QPixmap::fromImage(*img_sobel_recon));
    sobel->setMinimumWidth(w);
    sobel->setMinimumHeight(h);
    sobel->move(20,20+h*5);
    sobel->show();
    ui->gridLayout_5->addWidget(sobel,5,0);

}

void MainWindow::on_btn_dft_clicked()
{
    //initialize images
    img_dft_amp = new QImage(w,h,img_in->format());
    img_dft_phase = new QImage(w,h,img_in->format());
    img_dft_amp_shift = new QImage(w,h,img_in->format());
    img_dft_phase_shift = new QImage(w,h,img_in->format());


    //1-D dft on each row and coloumn
    DFT1();

    //normalize dft to image and shift
    cout << "Start dft print: " << clock() << " "  << endl;
    int tempMag =0;
    int tempPhase =0;

    for (int k = 0; k < (w/2)-1; ++k) {
        for (int l = 0; l < (h/2)-1; ++l) {

            DFTShifted[k + (w/2)][l + (h/2)] = complex_2D[k][l];
            DFTShifted[k][l] = complex_2D[k + w/2][l + h/2];
            DFTShifted[k + w/2][l] = complex_2D[k][l + h/2];
            DFTShifted[k][l + h/2] = complex_2D[k + w/2][l];
        }
    }


    for (int k = 0; k < w-1; ++k)
    {
        for (int l = 0; l < h-1; ++l)
        {
            //magnitude
            tempMag = (int)(round( std::abs(complex_2D[k][l])));
            img_dft_amp->setPixel( k, l , qRgb(tempMag,tempMag,tempMag));
            //phase
            tempPhase = (int)(round( std::arg(complex_2D[k][l])))*255/2*M_PI;
            img_dft_phase->setPixel( k, l , qRgb(tempPhase,tempPhase,tempPhase));

            //shifted magnitude
            tempMag = (int)(round( std::abs(DFTShifted[k][l])));
            img_dft_amp_shift->setPixel( k, l , qRgb(tempMag,tempMag,tempMag));
            //shifted phase
            tempPhase = (int)(round( std::arg(DFTShifted[k][l])))*255/2*M_PI;
            img_dft_phase_shift->setPixel( k, l , qRgb(tempPhase,tempPhase,tempPhase));
        }
    }


    //display mag shift
    QLabel *mag_shift = new QLabel(this);
    mag_shift->setPixmap(QPixmap::fromImage(*img_dft_amp_shift));
    mag_shift->setMinimumWidth(w);
    mag_shift->setMinimumHeight(h);
    mag_shift->show();
    ui->gridLayout_5->addWidget(mag_shift,8,0);

    //display phase shift
    QLabel *phase_shift = new QLabel(this);
    phase_shift->setPixmap(QPixmap::fromImage(*img_dft_phase_shift));
    phase_shift->setMinimumWidth(w);
    phase_shift->setMinimumHeight(h);
    phase_shift->show();
    ui->gridLayout_5->addWidget(phase_shift,8,1);


    //display mag
    QLabel *mag = new QLabel(this);
    mag->setPixmap(QPixmap::fromImage(*img_dft_amp));
    mag->setMinimumWidth(w);
    mag->setMinimumHeight(h);
    mag->show();
    ui->gridLayout_5->addWidget(mag,7,0);

    //display phase
    QLabel *phase = new QLabel(this);
    phase->setPixmap(QPixmap::fromImage(*img_dft_phase));
    phase->setMinimumWidth(w);
    phase->setMinimumHeight(h);
    phase->show();
    ui->gridLayout_5->addWidget(phase,7,1);


    cout << "End dft print: " << clock() << " "  << endl;



}


void MainWindow::IDFT1()
{
    double pi2 = 2.0 * M_PI;
    complex<double> F (0,0);
    double M = w;
    double N = h;
    int pixVal;

    inverse_2D.resize(N);
    inverse_2D[0].resize(w);

    for (int x = 0; x < M; ++x)
    {
        for (int y = 0; y < N; ++y)
        {

            inverse_2D[x][y] = 0;
            inverse_2D[y].resize(w);
            //inverse fourier
            for (int u = 0; u < M-1; ++u)
            {
                for (int v = 0; v < N-1; ++v)
                {
                    F = complex_2D[u][v];
                    inverse_2D[x][y] += F * exp(complex<double> (0,pi2*((u*x)/M + (v*y)/N)));

                }
            }
            inverse_2D[x][y] *= 1/sqrt(M*N);
            pixVal = (int)(std::abs(inverse_2D[x][y]));
            img_idft->setPixel(x,y,qRgb(pixVal,pixVal,pixVal));

        }
        ui->progressBar->setValue(100*x/M +2);
    }




}

void MainWindow::DFT1()
{
    cout << "Start DFT: " << clock() << " "  << endl;
    double pi2 = 2.0 * M_PI;
    double pixVal;
    double M = w;
    double N = h;

    complex_2D.resize(N);
    complex_2D[0].resize(M);
    DFTShifted.resize(N);
    DFTShifted[0].resize(M);

    //fourier pixel k
    for (int k = 0; k < M-1; ++k)
    {

        //for pixel l
        for (int l = 0; l < N-1; ++l)
        {
            complex_2D[k][l] = 0;
            complex_2D[l].resize(w);
            DFTShifted[l].resize(w);
            DFTShifted[k][l] = 0;

            //1 coloumn
            for (int m = 0; m < M-1; ++m)
            {

                //1 row
                for (int n = 0; n < N-1; ++n)
                {

                    pixVal = qGray(img_grey->pixel(m,n));
                    complex_2D[k][l] += pixVal * exp(complex<double> (0,-pi2*((k*m)/M + (l*n)/N)));

                }
            }
            complex_2D[k][l] *= 1/sqrt(M*N);
        }
        ui->progressBar->setValue(100*k/M+2);
    }
    cout << "End DFT: " << clock() << " "  << endl;

}




void MainWindow::on_btn_idft_clicked()
{
    //initialize idft image
    img_idft = new QImage(w,h,img_in->format());

    //run idft
    cout << "Start Inverse DFT: " << clock() << " "  << endl;
    IDFT1();

    //display image
    //display phase
    QLabel *inverse = new QLabel(this);
    inverse->setPixmap(QPixmap::fromImage(*img_idft));
    inverse->setMinimumWidth(w);
    inverse->setMinimumHeight(h);
    inverse->show();
    ui->gridLayout_5->addWidget(inverse,9,0);


    cout << "End Inverse DFT " << clock() << " "  << endl;

}
