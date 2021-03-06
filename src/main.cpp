/** 
 * @file   main.cpp
 * 
 * @author Morgan Chumbley
 * 
 * @date   May 29th, 2020
 */

#if defined(_WIN32)
   #define PATH_DELIM "\\"
#elif defined(__linux__)
   #define PATH_DELIM "/"
#endif

#include <QApplication>

#include "window_watcher.hpp"
#include "lib/logger/logger.hpp"

int main( int argc, char **argv )
{
   // Set the path to log to
   std::string file_path = __FILE__ ;
   std::string src_path = file_path.substr(0, file_path.rfind(PATH_DELIM)) ;
   std::string top_path = src_path.substr(0, src_path.rfind(PATH_DELIM)) ;
   set_log_file( (top_path + PATH_DELIM + "watermarker.log").c_str() ) ;

   // Create the Qt app 
   QApplication::setStyle("plastique");
   QApplication app(argc, argv);

   // Grab the monitor size
   QSize size = app.screens()[0]->size();

   // Create the window widget
   WindowWatcher *main = new WindowWatcher(1, size);

   // Execute the application
   app.exec();

   // After the app is closed, shutdown
   delete main;
} // end main()