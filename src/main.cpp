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

int main(int argc, char **argv)
{
   // Set the path to log to
   std::string file_path = __FILE__ ;
   std::string src_path = file_path.substr(0, file_path.rfind(PATH_DELIM)) ;
   std::string top_path = src_path.substr(0, src_path.rfind(PATH_DELIM)) ;
   LOG::set_file_name( (top_path + PATH_DELIM + "watermarker.log").c_str() ) ;

   QApplication::setStyle("plastique");
   QApplication app(argc, argv);

   QSize size = app.screens()[0]->size();

   WindowWatcher *main = new WindowWatcher(1, size);

   app.exec();

   // After the app is closed, shutdown
   delete main;
}