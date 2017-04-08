#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

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

private:
    Ui::MainWindow *ui;

    QImage *img_in, *img_red, *img_green, *img_blue, *img_grey, *img_dft_real, *img_dft_ima, *img_idft;
    QImage *img_sobel_total[3];
    QImage *img_sobel_recon;

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
};

#endif // MAINWINDOW_H
