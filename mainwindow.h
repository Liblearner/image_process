#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QPixmap>
#include <QImage>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>
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
    cv::Mat src;

private slots:
    void button_file_choose_clicked();
    void button_gray_Clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *rgb2gray;
    QPushButton *file_choose;

    void displayImage();
};
#endif // MAINWINDOW_H
