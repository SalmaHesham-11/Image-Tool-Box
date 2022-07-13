//*********************** salma hesham othman - sec.2 - 17782 *************************//
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include"QFileDialog"
#include"QDir"
#include"QPixmap"
#include"iostream"
using namespace std;
using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

string path;

Mat dest;

Mat image2 ;
Mat image=imread("E:\\smister 9\\digital image\\tool_box\\img4.jpg",0);

int r,c;

void MainWindow::on_pushButton_enter_clicked()
{
    //*********** to make user enter the image from files *****//////
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpeg .jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this,
       tr("Open Images"), QDir::homePath(), tr("Image Files (.png *.jpg *.bmp *.jpeg)"));
    if (!fileName.isEmpty())
    {
        image2 = imread(fileName.toLatin1().data(),0);
        QImage image(image2.data,image2.cols,image2.rows,image2.step,QImage::Format_Grayscale8);

    }

}

//**********************translation*************//
void MainWindow::on_pushButton_clicked()
{
    QString text1 = ui->lineEdit_x_3->text();
        double tx = text1.toDouble();

    QString text2 = ui->lineEdit_y_2->text();
        double ty = text2.toDouble();

    Mat TM = (Mat_<float>(2, 3) << 1, 0, tx, 0, 1, ty);
    cv::warpAffine(image2, dest, TM, image2.size());
    namedWindow("Translation", 0);
    imshow("Translation", dest);
    imwrite("Trans.jpg", dest);
    waitKey(0);
    image2=dest;

}
//******************skewing******************//
void MainWindow::on_pushButton_3_clicked()
{
    QString text1 = ui->lineEdit_skewing->text();
        double x = text1.toDouble();


    cv::Point2f src_p[3];
    src_p[0] = Point2f(0, 0);
    src_p[1] = Point2f(image2.cols - 1, 0);
    src_p[2] = Point2f(0, image2.rows - 1);
    cv::Point2f dst_p[3];
    dst_p[0] = Point2f(0, 0);
    dst_p[1] = Point2f(image2.cols - x, 0);
    dst_p[2] = Point2f(x, image2.rows - 1);
    Mat SM = cv::getAffineTransform(src_p, dst_p);
    cv::warpAffine(image2, dest, SM, image2.size());
    namedWindow("skewing", 0);
    imshow("skewing", dest);
    waitKey(0);
    image2=dest;
}

//***********************rotation****************//
void MainWindow::on_pushButton_rotation_clicked()
{
    QString text1 = ui->lineEdit_degree->text();
        double degree = text1.toDouble();

    QString text2 = ui->lineEdit_scale->text();
        double scale = text2.toDouble();

    Mat R = cv::getRotationMatrix2D(Point2f(image2.rows / 2, image2.cols / 2), degree, scale);
    cv::warpAffine(image2, dest, R, image2.size());
    namedWindow("rotate ", 0);
    imshow("rotate ", dest);
    waitKey(0);
    image2 = dest;
}

//*********************zoom**************//
void MainWindow::on_pushButton_4_clicked()
{
    QString text1 = ui->lineEdit_x->text();
        double x = text1.toDouble();

    QString text2 = ui->lineEdit_y->text();
        double y = text2.toDouble();

    Mat imcrop = image2(Rect(x, y, image2.rows / 2, image2.cols / 2));
    cv::resize(imcrop, dest, image2.size(), 1, 1, 1);
    namedWindow("image_zoom", 0);
    imshow("image_zoom", dest);
    waitKey(0);
    image2=dest;
}

//**************** flip***************//
void MainWindow::on_pushButton_5_clicked()
{  //****************way to choose flip around using wait key only work on visoual studio not work on Qt creater***********//
    /* char k;
    k = cv::waitKey(0);
    //cin>>k;

    if(k=='y'){
        flip(image2, dest, 1);
        namedWindow("flip around y", 0);
        imshow("flip around y", dest);
        imwrite("flip around y.jpg", dest);
        waitKey(121);
        image2=dest;
    }
    if(k =='x'){
        flip(image2, dest, 0);
        namedWindow("flip around x", 0);
        imshow("flip around x", dest);
        imwrite("flip around x.jpg", dest);
        waitKey(0);
        image2=dest;
    }
    if(k=='z'){
        flip(image2, dest, -1);
        namedWindow("flip around xy", 0);
        imshow("flip around xy", dest);
        imwrite("flip around xy.jpg", dest);
        waitKey(0);
        image2=dest;
    }*/

    QString text = ui->lineEdit_flip->text();
        double f = text.toDouble();
    if(f==1){
        flip(image2, dest, 1);
        namedWindow("flip around y", 0);
        imshow("flip around y", dest);
        imwrite("flip around y.jpg", dest);
        waitKey(0);
        image2=dest;
}
    if(f==2){
        flip(image2, dest, 0);
        namedWindow("flip around x", 0);
        imshow("flip around x", dest);
        imwrite("flip around x.jpg", dest);
        waitKey(0);
        image2=dest;
    }
    if(f==3){
        flip(image2, dest, -1);
        namedWindow("flip around xy", 0);
        imshow("flip around xy", dest);
        imwrite("flip around xy.jpg", dest);
        waitKey(0);
        image2=dest;
    }

}

//****************blinging*****************//
void MainWindow::on_pushButton_blinding_clicked()
{
    Mat dest(image.rows, image.cols, CV_8UC1);
    cv::resize(image2, image2, Size(image.cols, image.rows),0,0,0);

    for (r = 0; r < image.rows; r++)
    {
        for (c = 0; c < image.cols; c++)
        {
            dest.at<uchar>(r, c) = image.at<uchar>(r, c) * 0.7 +
            image2.at<uchar>(r, c) * 0.3;

        }
    }
    namedWindow("image2", 0);
    imshow("image2", image2);
    namedWindow("image2", 0);
    imshow("image", image);
    namedWindow("blinding", 0);
    imshow("blinding", dest);
    waitKey(0);
    image2 = dest;
}
//*******************negative image***************//
void MainWindow::on_pushButton_8_clicked()
{       dest=image2;
        for (r = 0; r < image2.rows; r++)
        {
            for (c = 0; c < image2.cols; c++)
            {
                dest.at<uchar>(r, c) = 255 - image2.at<uchar>(r, c);

            }
        }
        namedWindow("image negative", 0);
        imshow("image negative", dest);
        waitKey(0);
        image2 = dest;

}


//************** log tranformation & power low with gamma <1 ***************//
void MainWindow::on_pushButton_9_clicked()
{
    image2.convertTo(image2, CV_32F);
    image2 = image2 + 1;
    log(image2, dest);
    normalize(dest, dest, 0, 255, NORM_MINMAX);
    convertScaleAbs(dest, dest);

    imshow("log transformation_image", dest);
    waitKey(0);

//************** powerlow*****************//
    image2.convertTo(image2,CV_32F);
    dest = image2;
    for (r = 0; r < image2.rows; r++)
      {
        for (c = 0; c < image2.cols; c++)
        {
            dest.at<float>(r, c) = powf(image2.at<float>(r, c), 0.3);
        }
    }
    normalize(dest, dest, 0, 255, NORM_MINMAX);
    convertScaleAbs(dest, dest);
    namedWindow("power low with gamma=0.3",0);
    imshow("power low with gamma= 0.3", dest);
    waitKey(0);
    image2=dest;


}

void MainWindow::on_pushButton_Histogram_clicked()
{
    float hist[256] = { 0 };
    for (int g = 0; g < 256; g++)
    {
        for (int r = 0; r < image2.rows; r++)
        {
            for (int c = 0; c < image2.cols; c++)
            {
                if (image2.at<uchar>(r, c) == g)
                    hist[g] = hist[g] + 1;
            }
         }
    if (hist[g] != 0)
    cout << "hist[" << g << "]= " << hist[g] << endl;
    }
    cv::equalizeHist(image2,dest);
    namedWindow("Histogram Equlazation",0);
    imshow("Histogram Equlaziation", dest);
    waitKey(0);

    image2 = dest;

}
//************* b\w image*************//
void MainWindow::on_pushButton_thershoding_clicked()
{
    namedWindow("Image", 0);
    imshow("Image", image2);
    waitKey(0);
    threshold(image2, dest, 180, 255,THRESH_BINARY );
    namedWindow("After thresholding", 0);
    imshow("After thresholding", dest);
    waitKey(0);
    image2 = dest;
    //**********gray level slicing***************//

    dest = image2;
    for (r = 0; r < image2.rows; r++)
    {
        for (c = 0; c < image2.cols; c++)
        {
            if (image2.at<uchar>(r, c) > 180 && image2.at<uchar>(r, c) <200)
                   dest.at<uchar>(r, c) = 255;
            else
                   dest.at<uchar>(r, c) = image2.at<uchar>(r, c);
        }
    }
    namedWindow("After Gray level slicing", 0);
    imshow("After Gray level slicing", dest);
    waitKey(0);
   // image2 = dest;
}

//**************powerlow(brigthness decrease)*******************//

void MainWindow::on_pushButton_powerlow_clicked()
{
    dest = image2;
    for (r = 0; r < image2.rows; r++)
      {
        for (c = 0; c < image2.cols; c++)
        {
            dest.at<float>(r, c) = powf(image2.at<float>(r, c), 1);
        }
    }
    normalize(dest, dest, 0, 255, NORM_MINMAX);
    convertScaleAbs(dest, dest);
    namedWindow("powerlow with gamma=1",0);
    imshow("powerlow with gamma=1", dest);
    waitKey(0);
    image2 = dest;

}
//************** Median filter ***************//
void MainWindow::on_pushButton_Median_filtering_clicked()
{
    namedWindow("before median filter", 0);
    imshow("before median filter", image2);
    medianBlur(image2, dest, 5);
    namedWindow("median filter", 0);
    imshow("median filter", dest);
    waitKey(0);  
    image2 = dest;
}

//***********************smoothing filter****************//
void MainWindow::on_pushButton_Smoothing_clicked()
{
    //************************circular filter********************//
    Mat kernel_c=(Mat_<float>(5, 5) << 0,1,1,1,0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0);
    kernel_c = kernel_c / 21;
    filter2D(image2, dest, CV_8UC1, kernel_c);
    namedWindow("image circular filter", 0);
    imshow("image circular filter", dest);
    image2=dest;
    waitKey(0);

    //***********************pyramidal filter***********************//
    Mat kernel_p = (Mat_<float>(5, 5) << 1, 2, 3,2,1,2,4,6,4,2,3,6,9,6,3,2,4,6,4,2,1,2,3,2,1);
    cout << endl << kernel_p << endl;
    kernel_p = kernel_p / 81;
    cout << endl << kernel_p << endl;
    filter2D(image2, dest, CV_8UC1, kernel_p);
    namedWindow("pyramidal filter", 0);
    imshow("pyramidal filter", dest);
    waitKey(0);
   //******************** Tradtional filter**************//
    Mat kernel_T = (Mat_<float>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1);
    kernel_T = kernel_T / 9;

    filter2D(image2, dest, CV_8UC1, kernel_T);
    namedWindow("image tradtional filter", 0);
    imshow("image tradtional filter", dest);
    waitKey(0);
    image2=dest;
    //**************

}

//****************** sharpping filter***************//
void MainWindow::on_pushButton_13_clicked()
{   Mat dest_x,dest_y;
    namedWindow("before sobel", 0);
    imshow("before sobel", image2);
    waitKey(0);

    Sobel(image2, dest_x, CV_8UC1, 1, 0,3);
    namedWindow("sobel_x direction", 0);
    imshow("sobel_x direction", dest_x);
    waitKey(0);

    Sobel(image2, dest_y, CV_8UC1, 0, 1,3);
    namedWindow("sobel_y direction", 0);
    imshow("sobel_y direction", dest_y);
    waitKey(0);
    //image2=dest;
}

void MainWindow::on_pushButton_laplacian_clicked()
{
    //*********************** gaussian**************//
    Mat dest2;
    GaussianBlur(image2,dest2,Size(3,3),0);
    namedWindow("gaussian",0);
    imshow("gaussian", dest2);
    waitKey(0);

    //********************laplacion******************//
    Laplacian(dest2, dest, CV_8UC1);
    namedWindow("laplacion",0);
    imshow("laplacion",dest);
    waitKey(0);
}

void MainWindow::on_pushButton_Segmentation_clicked()
{
    //******************** thresholding****************//
    int th=100;
        for(int x=0 ; x<10 ; x++){
            threshold(image2 ,dest ,th ,255 ,THRESH_BINARY);
            namedWindow("after threshold",0);
            createTrackbar("threshold","after threshold",&th,255);
            imshow("after threshold",dest);
            waitKey(0);
        }
}
