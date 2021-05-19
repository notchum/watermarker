/** 
 * @file   image_viewer.hpp
 * 
 * @brief  Contains the definitions of the ImageViewer class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 11th, 2020
 */

#ifndef IMAGE_VIEWER_HPP
#define IMAGE_VIEWER_HPP

#include "wm_widget.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

/** 
 * @class   ImageViewer
 * 
 * @brief   A class to create a widget to display an image.
 * 
 * @details A more detailed class description.
 * 			Class description continued
 */
class ImageViewer : public QWidget
{
   Q_OBJECT

public:
   /** 
    * @brief Constructor 
    */
   ImageViewer( QWidget *parent = nullptr );

   /** 
    * @brief Destructor 
    */
   virtual ~ImageViewer( void ) {}

   /**
    * @brief Initializes the main image
    */ 
   void init( cv::String imgPath, cv::String wmPath );

   /**
    * @brief Initializes the wm image
    */ 
   void loadWM( cv::String filename );

   void changeWMScale( int scale );

protected:
   void resizeEvent( QResizeEvent *event );

private:
   /** 
    * @brief Sets the QLabel's Pixmap from an OpenCV image
    */
   void setPixmap( void );

   /** 
    * @brief  Helper function to resize an OpenCV Mat image
    * 
    * @param  img the input OpenCV image
    * 
    * @param  target_width the target width of the output image
    * 
    * @return the resized image
    */
   cv::Mat resizeImage( const cv::Mat& img, int target_width = 500 );

   /* A QLabel can be used to diplay an image */
   QLabel *image_lbl;

   /* Main Image */
   cv::Mat image;
   cv::Rect roi;

   /* Watermark */
   WatermarkWidget *wmw;

}; // end class ImageViewer

#endif // IMAGE_VIEWER_HPP