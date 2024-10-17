#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->rgb2gray, SIGNAL(clicked()),this,SLOT(button_gray_Clicked()));
    connect(ui->file_choose, SIGNAL(clicked()),this,SLOT(button_file_choose_clicked()));

    QShowEvent *event;
    showEvent(event);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayImage(){
    src = cv::imread("E:\\Project\\qt_prj\\cv_gui\\cv_gui\\image\\hero.jpg");
    if (src.empty()) {
        qDebug() << "Failed to load image!";
        return;
    }

    qDebug() << "Original Image Size:" << src.cols << "x" << src.rows;

    int labelWidth  = ui->image->width();
    int labelHeight  = ui->image->height();


    qDebug() << "QLabel Size:" << labelWidth << "x" << labelHeight;


    cv::Mat resized;
    double aspectRatio = static_cast<double>(src.cols) / src.rows;
    int newWidth = labelWidth ;
    int newHeight = static_cast<int>(labelWidth  / aspectRatio);

    if (newHeight > labelHeight ) {
        newHeight = labelHeight ;
        newWidth = static_cast<int>(labelHeight  * aspectRatio);
    }

    cv::resize(src, resized, cv::Size(newWidth, newHeight));

    qDebug() << "Resized Image Size:" << resized.cols << "x" << resized.rows;

    QImage qimg(resized.data, resized.cols, resized.rows, resized.step, QImage::Format_RGB888);

    qimg = qimg.rgbSwapped();
    QPixmap pixmap = QPixmap::fromImage(qimg);
    ui->image->setPixmap(pixmap);  // 在QLabel上显示图像
    ui->image->setAlignment(Qt::AlignCenter);  // 使图像居中

}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    //重载showEvent，在窗口显示后进行图像加载和显示，
    //避免获取image QLabel时，窗口和QLabel还没有完全布局好，导致获取到的尺寸不正确。
    displayImage();  // 窗口显示后加载并显示图像
}

using namespace cv;

void MainWindow::button_file_choose_clicked()//选择文件
{
    qDebug() << "file_choose button clicked!";
    QString testFileName = QFileDialog::getOpenFileName(this,tr(""),"../../../../open_image","files(*)");

    src = imread(testFileName.toStdString());
    // cvtColor(src, grayImg, CV_BGR2GRAY);

    Mat resized;
    int labelWidth  = ui->image->width();
    int labelHeight  = ui->image->height();
    double aspectRatio = static_cast<double>(src.cols) / src.rows;
    int newWidth = labelWidth ;
    int newHeight = static_cast<int>(labelWidth  / aspectRatio);

    if (newHeight > labelHeight ) {
        newHeight = labelHeight ;
        newWidth = static_cast<int>(labelHeight  * aspectRatio);
    }

    cv::resize(src, resized, cv::Size(newWidth, newHeight));

    qDebug() << "Resized Image Size:" << resized.cols << "x" << resized.rows;

    QImage qimg(resized.data, resized.cols, resized.rows, resized.step, QImage::Format_RGB888);

    qimg = qimg.rgbSwapped();
    QPixmap pixmap = QPixmap::fromImage(qimg);
    ui->image->setPixmap(pixmap);  // 在QLabel上显示图像
    ui->image->setAlignment(Qt::AlignCenter);  // 使图像居中

}

void MainWindow::button_gray_Clicked()//BGR转灰度
{
    qDebug() << "rgb2gray button clicked!";
    cv::Mat src_gray;
    src_gray.create(src.rows, src.cols, CV_8UC1);
    cvtColor(src,src_gray,COLOR_RGB2GRAY);
    QImage Qtemp;
    Qtemp = QImage((const uchar*)(src_gray.data), src_gray.cols, src_gray.rows, src_gray.cols*src_gray.channels(), QImage::Format_Indexed8);
    ui->image->setPixmap(QPixmap::fromImage(Qtemp));
    Qtemp = Qtemp.scaled(600, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->image->setScaledContents(true);
    ui->image->setAlignment(Qt::AlignCenter);  // 使图像居中
    ui->image->resize(Qtemp.size());
    ui->image->show();

}
