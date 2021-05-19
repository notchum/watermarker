/** 
 * @file   image_viewer.cpp
 * 
 * @brief  Contains the implementation of the ImageViewer class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 11th, 2020
 */

#include "wm_widget.hpp"
#include "lib/logger/logger.hpp"

WatermarkWidget::WatermarkWidget( QWidget * parent ) : QWidget(parent)
{
   // Create the label
   image_lbl = new QLabel();
   image_lbl->setCursor(Qt::PointingHandCursor);
   //image_lbl->setMouseTracking(true);

   // Setting layout
   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(image_lbl);
   setLayout(layout);
} // end WatermarkWidget::WatermarkWidget()

void WatermarkWidget::init( cv::String filename )
{
   // Set the image matrix
   this->image = cv::imread(filename);

   cv::cvtColor(this->image, this->image, 4); // CV_BGR2RGB = 4

   image_lbl->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888)));
} // end WatermarkWidget::init()

// void WatermarkWidget::resizeEvent( QResizeEvent *event )
// {
//     this->setPixmap();
//     QWidget::resizeEvent(event);
// } // end WatermarkWidget::resizeEvent()

void WatermarkWidget::setScale( int scale )
{
   this->scale = scale;
   this->setPixmap();
} // end WatermarkWidget::setScale()

void WatermarkWidget::setPixmap( void )
{
   // Resize the OpenCV image to fit the window but keep aspect ratio
   cv::Mat img = this->resize();

   img = this->drawBox(img);

   // Set the pixmap for the QLabel which displays the image recieved
   image_lbl->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)));
} // end WatermarkWidget::setPixmap()

cv::Mat WatermarkWidget::resize( void )
{
   double percentScale = this->scale / 100;

   

   cv::Mat outImg;
   cv::resize(this->image, outImg, cv::Size(this->image.cols * percentScale, this->image.rows * percentScale));
   return outImg;
} // end WatermarkWidget::resize()

cv::Mat WatermarkWidget::drawBox( cv::Mat img )
{
   cv::rectangle(img, this->roi, cv::Scalar(0, 255, 0), 1);
   return img;
} // end WatermarkWidget::drawBox()