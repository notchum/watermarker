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

WatermarkWidget::WatermarkWidget( QWidget * parent ) : QWidget(parent)
{
   // Create the label
   mImageLbl = new QLabel();
   mImageLbl->setCursor(Qt::PointingHandCursor);
   //mImageLbl->setMouseTracking(true);

   // Setting layout
   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(mImageLbl);
   setLayout(layout);
} // end WatermarkWidget::WatermarkWidget()


void WatermarkWidget::init( cv::String filename )
{
   // Set the image matrix directly from source
   this->mSourceImage = cv::imread(filename);

   // Convert the color encoding to the RGB for Qt
   cv::cvtColor(this->mSourceImage, this->mSourceImage, 4); // CV_BGR2RGB = 4

   // Set the main image that will be worked with
   this->mImage = this->mSourceImage.clone();

   // Set the scale to 100% to begin with
   this->mScale = 1.00;

   // Set the widget's pixmap
   this->setPixmap();
} // end WatermarkWidget::init()


void WatermarkWidget::setScale( int scale )
{
   this->mScale = double(scale) / double(100);
   // LOG_DEBUG("Watermark scale = {:.2f}\n", this->mScale);
   this->setPixmap();
} // end WatermarkWidget::setScale()


void WatermarkWidget::setTransparency( int alpha )
{
   ;
} // end WatermarkWidget::setTransparency()


void WatermarkWidget::invertImage( void )
{
   cv::bitwise_not(this->mSourceImage, this->mImage);
   this->setPixmap();
} // end WatermarkWidget::invertImage()


void WatermarkWidget::setPixmap( void )
{
   // Resize the OpenCV image according to set scale
   this->resizeImage();

   // DEBUGGING
   this->drawImageBorder();

   // Set the pixmap for the QLabel which displays the image recieved
   mImageLbl->setPixmap(QPixmap::fromImage(QImage(this->mImage.data, this->mImage.cols, this->mImage.rows, this->mImage.step, QImage::Format_RGB888)));
} // end WatermarkWidget::setPixmap()


void WatermarkWidget::resizeImage( void )
{
   // Use OpenCV's resize function
   cv::resize(this->mSourceImage, this->mImage, cv::Size(0, 0), this->mScale, this->mScale);

   // Update the image border rectangle
   this->mBorder.x = 0;
   this->mBorder.y = 0;
   this->mBorder.width = this->mImage.cols;
   this->mBorder.height = this->mImage.rows;
} // end WatermarkWidget::resize()


void WatermarkWidget::drawImageBorder( void )
{
   cv::rectangle(this->mImage, this->mBorder, cv::Scalar(0, 255, 0), 1);
} // end WatermarkWidget::drawBox()

//*********************************************//
///////////////     QT EVENTS     ///////////////
//*********************************************//

void WatermarkWidget::resizeEvent( QResizeEvent *event )
{
   this->setPixmap();
   QWidget::resizeEvent(event);
} // end ImageViewer::resizeEvent()


void WatermarkWidget::mousePressEvent( QMouseEvent *event )
{
   this->mOldPosition = event->globalPos();
} // end WatermarkWidget::mousePressEvent()


void WatermarkWidget::mouseMoveEvent( QMouseEvent *event )
{
   const QPoint delta = event->globalPos() - this->mOldPosition;
   this->move(x()+delta.x(), y()+delta.y());
   this->mOldPosition = event->globalPos();

   // Update the coordinates of the watermark
   this->mTopLeftCoords.x = this->mOldPosition.x();
   this->mTopLeftCoords.y = this->mOldPosition.y();
   this->mBottomRightCoords.x = this->mTopLeftCoords.x + this->mImage.cols;
   this->mBottomRightCoords.y = this->mTopLeftCoords.y + this->mImage.rows;
   // if (this->underMouse()) {
   // 	LOG_INFO("Under mouse\n");
   // 	// No drag, just change the cursor and return
   // 	if (event->x() <= 3 && event->y() <= 3) {
   // 	startPos = start_positions::topleft;
   // 	setCursor(Qt::SizeFDiagCursor);
   // 	} else if (event->x() <= 3 && event->y() >= height() - 3) {
   // 		startPos = start_positions::bottomleft;
   // 		setCursor(Qt::SizeBDiagCursor);
   // 	} else if (event->x() >= width() - 3 && event->y() <= 3) {
   // 		startPos = start_positions::topright;
   // 		setCursor(Qt::SizeBDiagCursor);
   // 	} else if (event->x() >= width() - 3 && event->y() >= height() - 3) {
   // 		startPos = start_positions::bottomright;
   // 		setCursor(Qt::SizeFDiagCursor);
   // 	} else if (event->x() <= 3) {
   // 		startPos = start_positions::left;
   // 		setCursor(Qt::SizeHorCursor);
   // 	} else if (event->x() >= width() - 3) {
   // 		startPos = start_positions::right;
   // 		setCursor(Qt::SizeHorCursor);
   // 	} else if (event->y() <= 3) {
   // 		startPos = start_positions::top;
   // 		setCursor(Qt::SizeVerCursor);
   // 	} else if (event->y() >= height() - 3) {
   // 		startPos = start_positions::bottom;
   // 		setCursor(Qt::SizeVerCursor);
   // 	} else {
   // 		startPos = start_positions::move;
   // 		setCursor(Qt::PointingHandCursor);
   // 	}
   // 	return;
   // }
} // end WatermarkWidget::mouseMoveEvent()
