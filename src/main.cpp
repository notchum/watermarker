/** 
 * @file   main.cpp
 * 
 * @author Morgan Chumbley
 * 
 * @date   May 29th, 2020
 */

#include <QApplication>

#include "window_watcher.hpp"

int main(int argc, char **argv)
{
	QApplication::setStyle("plastique");
	QApplication app(argc, argv);

	WindowWatcher *main = new WindowWatcher(1);

	app.exec();

	// After the app is closed, shutdown
	delete main;
}