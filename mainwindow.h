#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <QFileDialog>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showEvent(QShowEvent *event);

private slots:
    void button_file_choose_clicked();
    void button_gray_Clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat image;
    cv::Mat gray;
    void displayImage();

    QPushButton *pushButton_file_choose;
    QPushButton *pushButton_rgb2gray;

};
#endif // MAINWINDOW_H
