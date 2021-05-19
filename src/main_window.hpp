/** 
 * @file   main_window.hpp
 * 
 * @brief  Contains the definitions of the MainWindow class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 11th, 2020
 */

#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "image_viewer.hpp"
#include "wm_widget.hpp"

#include <vector>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QCheckBox>
#include <QProgressBar>
#include <QGroupBox>
#include <QSlider>
#include <QSpinBox>

/** 
 * @class   MainWindow
 * 
 * @brief   A class to create the main Qt window.
 * 
 * @details This class is used to add all custom
 * 			widgets to a single window. This class
 * 			constructor is then called in main.cpp
 * 			to execute the entire application.
 */
class MainWindow : public QWidget
{
   Q_OBJECT

public:
   /** 
    * @brief Constructor 
    */
   MainWindow( QWidget * parent = nullptr ) : QWidget(parent) {}

   /** 
    * @brief Parameterized constructor 
    * 
    * @param windowSize the primary screen size
    */
   MainWindow( QSize windowSize, QWidget * parent = nullptr );

   /** 
    * @brief Destructor 
    */
   virtual ~MainWindow() {}

   /** 
    * @brief Initialization function for when the main window is entered into
    */
   void init( QString path, QString wmPath, bool isPathDir );

public slots:
   /** 
    * @brief Qt slot for when the okay button is pressed
    */
   void okayButtonPressed_slot( void );

   /** 
    * @brief Qt slot for when the exit button is pressed
    */
   void exitButtonPressed_slot( void );

   /** 
    * @brief Qt slot for when the exit button is pressed
    */
   void checkBox_slot( int state );

   void tranValueChanged( int8_t ident, int value );
   void sizeValueChanged( int8_t ident, int value );

protected:
   void resizeEvent( QResizeEvent *event );

private:
   /** 
    * @brief Setter for paths
    * 
    * @param path main path
    * 
    * @param wmPath watermark path
    */
   void setPaths( QString path, QString wmPath );

   /* Required advance or exit buttons */
   QPushButton *okayButton;
   QPushButton *exitButton;

   /* Useful command widgets */
   QCheckBox *invertCB;
   QSlider *tranSlider;
   QSlider *sizeSlider;
   QSpinBox *tranSpinBox;
   QSpinBox *sizeSpinBox;
   QProgressBar *progressBar;

   /* Images */
   cv::Mat wmImg;
   cv::Mat wmImg_n;
   std::vector<cv::String> filenames;
   ImageViewer *imgViewer;

   /* Paths */
   QString _mnPath;
   QString _wmPath;

   /* Other */
   int windowWidth;
   int windowHeight;
   int wmTran;
   int wmSize;

}; // end class MainWindow

#endif // MAIN_WINDOW_HPP