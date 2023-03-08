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

#include "lib/logger/logger.hpp"
#include "lib/utils/intersection.hpp"

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
   void setTransparency( int alpha );
   void invertImage( void );

   // enum class StartPosition
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
   void resizeEvent( QResizeEvent *event );
   void mousePressEvent( QMouseEvent *event );
   void mouseMoveEvent( QMouseEvent *event );

private:
   void setPixmap( void );
   void resizeImage( void );
   void drawImageBorder( void );

   /* A QLabel can be used to diplay an image */
   QLabel *mImageLbl;

   /* Source Image */
   cv::Mat mSourceImage;

   /* Main Image */
   cv::Mat mImage;
   cv::Rect mBorder;

   /* Other */
   QPoint mOldPosition;
   iPoint mTopLeftCoords;
   iPoint mBottomRightCoords;
   //StartPosition mStartPosition;
   double mScale;

}; // end class WatermarkWidget

#endif // WM_WIDGET_HPP