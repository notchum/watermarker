/** 
 * @file   image_viewer.cpp
 * 
 * @brief  Contains the implementation of the ImageViewer class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 11th, 2020
 */

#include "image_viewer.hpp"

ImageViewer::ImageViewer( QWidget *parent ) : QWidget(parent)
{
   // Create the label
   image_lbl = new QLabel();
   wmw = new WatermarkWidget();

   // Setting layout for watermark
   QVBoxLayout *layout = new QVBoxLayout();
   layout->addWidget(wmw, 0, Qt::AlignCenter);
   image_lbl->setLayout(layout);

   // After overlaying the layout for the main image, create the main layout
   QVBoxLayout *mainLayout = new QVBoxLayout();
   mainLayout->addWidget(image_lbl);
   setLayout(mainLayout);
} // end ImageViewer::ImageViewer()

void ImageViewer::init( cv::String imgPath, cv::String wmPath )
{
   // Set the image matrix
   this->image = cv::imread(imgPath);

   // Convert the color encoding to the RGB for Qt
   cv::cvtColor(this->image, this->image, 4); // CV_BGR2RGB = 4

   this->setPixmap();

   // Initialize the watermark
   wmw->init(wmPath);
} // end ImageViewer::init()


void ImageViewer::resizeEvent( QResizeEvent *event )
{
   this->setPixmap();
   QWidget::resizeEvent(event);
} // end ImageViewer::resizeEvent()

void ImageViewer::setPixmap( void )
{
   // Resize the OpenCV image to fit the window but keep aspect ratio
   cv::Mat img = this->resizeImage(image, this->width() - 30);

   img = this->drawBox(img);

   // Set the pixmap for the QLabel which displays the image recieved
   image_lbl->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)));
} // end ImageViewer::setPixmap()

cv::Mat ImageViewer::resizeImage( const cv::Mat& img, int target_width )
{
   int width = img.cols, height = img.rows;

   // Create a new square image using zeros (black)
   cv::Mat out_img = cv::Mat::zeros(target_width, target_width, img.type());

   // Set new image to a color that matches the background
   out_img.setTo(cv::Scalar(255, 255, 255));

   // Obtain ROI while keeping aspect ratio from orig image
   int max_dim = (width >= height) ? width : height;
   float scale = ((float)target_width) / max_dim;

   if (width >= height) {
      roi.width = target_width;
      roi.x = 0;
      roi.height = height * scale;
      roi.y = (target_width - roi.height) / 2;
   }
   else {
      roi.y = 0;
      roi.height = target_width;
      roi.width = width * scale;
      roi.x = (target_width - roi.width) / 2;
   }

   // Use OpenCV's resize function
   cv::resize(img, out_img(roi), roi.size());

   // Return the newly resized image
   return out_img;
} // end ImageViewer::resizeImage()

cv::Mat ImageViewer::drawBox( cv::Mat img )
{
   cv::rectangle(img, this->roi, cv::Scalar(0, 255, 0), 1);
   return img;
} // end ImageViewer::drawBox()

// void ImageViewer::blendImages( void )
// {
//    // load the input image, then add an extra dimension to the
//    // image (i.e., the alpha transparency)
//    image = cv2.imread(imagePath)
//    (h, w) = image.shape[:2]
//    image = np.dstack([image, np.ones((h, w), dtype="uint8") * 255])

//    // construct an overlay that is the same size as the input
//    // image, (using an extra dimension for the alpha transparency),
//    // then add the watermark to the overlay in the bottom-right
//    // corner
//    overlay = np.zeros((h, w, 4), dtype="uint8")
//    overlay[imgHeight - wmHeight - 10:imgHeight - 10, w - wW - 10:imgWidth - ] = watermark

//    // blend the two images together using transparent overlays
//    output = image.copy()
//    cv2.addWeighted(overlay, args["alpha"], output, 1.0, 0, output)

//    // write the output image to disk
//    filename = imagePath[imagePath.rfind(os.path.sep) + 1:]
//    p = os.path.sep.join((args["output"], filename))
//    cv2.imwrite(p, output)
// }