#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QShowEvent *event;
    showEvent(event);
    pushButton_file_choose = new QPushButton("file_choose",this);
    pushButton_rgb2gray = new QPushButton("rgb2gray",this);
    connect(pushButton_file_choose, SIGNAL(clicked()), this, SLOT(button_file_choose_clicked()));
    connect(pushButton_rgb2gray, SIGNAL(clicked()), this, SLOT(button_gray_Clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayImage(){
    cv::Mat src = cv::imread("E:\\Project\\qt_prj\\cv_gui\\cv_gui\\image\\hero.jpg");
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
    // QString testFileName = QFileDialog::getOpenFileName(this,tr(""),"../../../../open_image","files(*)");
    // image = imread(testFileName.toStdString());
    // cvtColor(image, grayImg, CV_BGR2GRAY);

    // Mat temp;
    // QImage Qtemp;
    // cvtColor(image, temp, COLOR_BGR2RGB);//BGR convert to RGB
    // Qtemp = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, temp.step, QImage::Format_RGB888);

    // ui->image->setPixmap(QPixmap::fromImage(Qtemp));
    // Qtemp = Qtemp.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // ui->image->setScaledContents(true);
    // ui->image->resize(Qtemp.size());
    // ui->image->show();

}

void MainWindow::button_gray_Clicked()//BGR转灰度
{
    // //Mat gray;
    // grayImg.create(srcImg.rows, srcImg.cols, CV_8UC1);
    // QImage Qtemp;

    // for(int i = 0 ; i < srcImg.rows ; i++)
    //     for(int j = 0 ; j < srcImg.cols ; j++){
    //         grayImg.at<uchar>(i,j) = (int)0.11 * srcImg.at<Vec3b>(i,j)[0]
    //                                   + 0.59 * srcImg.at<Vec3b>(i,j)[1]
    //                                   + 0.3 * srcImg.at<Vec3b>(i,j)[2];
    //     }

    // Qtemp = QImage((const uchar*)(grayImg.data), grayImg.cols, grayImg.rows, grayImg.cols*grayImg.channels(), QImage::Format_Indexed8);
    // ui->image->setPixmap(QPixmap::fromImage(Qtemp));
    // Qtemp = Qtemp.scaled(250, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // ui->image->setScaledContents(true);
    // ui->image->resize(Qtemp.size());
    // ui->image->show();
}
