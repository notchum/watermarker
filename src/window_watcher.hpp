/** 
 * @file   main_window.hpp
 * 
 * @brief  Contains the definitions of the WindowWatcher class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   May 29th, 2020
 */

#ifndef WINDOW_WATCHER_HPP
#define WINDOW_WATCHER_HPP

#include "main_window.hpp"
#include "first_window.hpp"
#include "second_window.hpp"

#include <QWidget>
#include <QDebug>
#include <QScreen>

/** 
 * @class   WindowWatcher
 * 
 * @brief   A class to create the main Qt window.
 * 
 * @details This class is used to add all custom
 * 			widgets to a single window. This class
 * 			constructor is then called in main.cpp
 * 			to execute the entire application.
 */
class WindowWatcher : public QWidget
{
	Q_OBJECT

public:
   /** 
    * @brief Constructor 
    */
   WindowWatcher( QWidget * parent = nullptr ) : QWidget(parent) {}

   /** 
    * @brief Parameterized constructor 
    * 
    * @param window_number corresponds to the enum "Window" to choose a starting window
    * 
    * @param size the primary screen size
    */
   WindowWatcher( uint8_t window_number, QSize size, QWidget * parent = nullptr );

   /** 
    * @brief Destructor 
    */
   virtual ~WindowWatcher( void ) {}

   /* Enum used for keeping track of current window */
   enum class Window
   {
      FIRST_WINDOW,
      SECOND_WINDOW,
      MAIN_WINDOW
   };

public slots:
   /** 
    * @brief Qt slot to change windows
    */
   void advanceWindow( void );

private:
   Window currentWindow;
   MainWindow *mainWindow;
   FirstWindow *firstWindow;
   SecondWindow *secondWindow;

   QSize windowSize;

}; // end class WindowWatcher

#endif // WINDOW_WATCHER_HPP