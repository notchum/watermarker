/** 
 * @file   window_watcher.cpp
 * 
 * @brief  Contains the implementation of the WindowWatcher class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 8th, 2020
 */

#include "window_watcher.hpp"
#include "lib/logger/logger.hpp"

WindowWatcher::WindowWatcher( uint8_t window_number, QSize size, QWidget *parent ) : QWidget(parent), windowSize(size)
{
   // Create each window
   mainWindow = new MainWindow(windowSize);
   firstWindow = new FirstWindow();
   secondWindow = new SecondWindow();

   switch(window_number) {
      case 1:
         currentWindow = Window::FIRST_WINDOW;
         firstWindow->show();
         break;

      case 2:
         currentWindow = Window::SECOND_WINDOW;
         secondWindow->show();
         break;

      case 3:
         currentWindow = Window::MAIN_WINDOW;
         mainWindow->setMinimumSize(1280, 720);
         mainWindow->showMaximized();
         mainWindow->show();
         break;
         
      default:
         LOG_FATAL("Invalid starting window!\n");
         break;
   }  

   // Hide the initial window when the OK button pressed
   QObject::connect(firstWindow, &FirstWindow::okayButtonPressed, 
                  [=]() { advanceWindow(); });

   // Hide the second window when the OK button pressed
   QObject::connect(secondWindow, &SecondWindow::okayButtonPressed, 
                  [=]() { advanceWindow(); });
} // end WindowWatcher::WindowWatcher()

void WindowWatcher::advanceWindow( void )
{
   switch(currentWindow) {
      case Window::FIRST_WINDOW:
         mainWindow->hide();
         firstWindow->hide();
         secondWindow->show();
         currentWindow = Window::SECOND_WINDOW;
         break;

      case Window::SECOND_WINDOW:
         firstWindow->hide();
         secondWindow->hide();
         mainWindow->init(firstWindow->getPath(), secondWindow->getPath(), firstWindow->isPathDir());
         mainWindow->setMinimumSize(1280, 720);
         mainWindow->showMaximized();
         mainWindow->show();
         currentWindow = Window::MAIN_WINDOW;
         break;

      case Window::MAIN_WINDOW:
         break;

      default:
         break;
   }
} // end WindowWatcher::advanceWindow()