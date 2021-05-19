/** 
 * @file   wm_widget.hpp
 * 
 * @brief  Contains the definitions of the WatermarkWidget class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 11th, 2020
 */

#ifndef WM_WIDGET_HPP
#define WM_WIDGET_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>

/** 
 * @class   WatermarkWidget
 * 
 * @brief   A class to create the widget containing the watermark.
 */
class WatermarkWidget: public QWidget
{
   Q_OBJECT

public:
   /** 
    * @brief Constructor 
    */
   WatermarkWidget( QWidget * parent = nullptr );

   /** 
    * @brief Destructor 
    */
   virtual ~WatermarkWidget( void ) {}

   /** 
    * @brief Initialization function
    * 
    * @param filename Location of watermark image
    */
   void init( cv::String filename );

   void setScale( int scale );

   // enum class start_positions 
   // {
   // 	topleft, 
   // 	left, 
   // 	bottomleft, 
   // 	bottom, 
   // 	bottomright, 
   // 	right, 
   // 	topright, 
   // 	top, 
   // 	move
   // };

protected:
   void mousePressEvent( QMouseEvent *event )
   {
      oldPos = event->globalPos();
   } // end mousePressEvent()

   void mouseMoveEvent( QMouseEvent *event )
   {
      const QPoint delta = event->globalPos() - oldPos;
      move(x()+delta.x(), y()+delta.y());
      oldPos = event->globalPos();

      // if (this->underMouse()) {
      // 	LOG::INFO("Under mouse");
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
   } // end mouseMoveEvent()

private:
   void setPixmap( void );
   cv::Mat resize( void );
   cv::Mat drawBox( cv::Mat img );

   /* A QLabel can be used to diplay an image */
   QLabel *image_lbl;

   /* Main Image */
   cv::Mat image;
   cv::Rect roi;

   /* Other */
   QPoint oldPos;
   //start_positions startPos;
   int scale;

}; // end class WatermarkWidget

#endif // WM_WIDGET_HPP