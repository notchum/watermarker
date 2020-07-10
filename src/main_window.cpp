/** 
 * @file   main_window.cpp
 * 
 * @brief  Contains the implementation of the MainWindow class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 8th, 2020
 */

#include "main_window.hpp"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	/************************************************************************************************
	*
	*                             IMAGE VIEWER
	* 
	************************************************************************************************/

	// Connect the indicator lights to the signals from string classes
	//QObject::connect(modules, &Modules::enabled, 
	//				 [=]() { this->enableIndLight(line1); });

	/************************************************************************************************
	*
	*                             COMMANDS
	* 
	************************************************************************************************/

	// Create group box for visuals
	// QGroupBox *commandGroupBox = new QGroupBox(tr("Commands"));

	// // Create layout for commands
	// QVBoxLayout *topLayout = new QVBoxLayout;
	// topLayout->setAlignment(Qt::AlignVCenter);

	// // Create & add commands
	// Commands *commands = new Commands();
	// topLayout->addWidget(commands);
	// commandGroupBox->setLayout(topLayout);
	// commandGroupBox->setMaximumHeight(300);

	FirstWindow *first_window = new FirstWindow();
	SecondWindow *second_window = new SecondWindow();

	// Hide the initial window when the OK button pressed
	QObject::connect(first_window, &FirstWindow::okayButtonPressed, 
					 [=]() { advanceWindow(); });

	// Hide the second window when the OK button pressed
	QObject::connect(second_window, &SecondWindow::okayButtonPressed, 
					 [=]() { advanceWindow(); });

	/************************************************************************************************
	*
	*                            LAYOUTS
	* 
	************************************************************************************************/

	QHBoxLayout *mainLayout = new QHBoxLayout;
	setLayout(mainLayout);
}

void MainWindow::advanceWindow()
{
	switch(current_window) {
		case windows::FIRST_WINDOW:
			first_window.hide();
			second_window.show();
			break;
		case windows::SECOND_WINDOW:
			second_window.hide();

			break;
		case windows::MAIN_WINDOW:
			break;
		default:
			break;
	}
}