/** 
 * @file   commands.hpp
 * 
 * @brief  Contains the definitions of the Commands class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   June 1st, 2020
 */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QProgressBar>

/** 
 * @class   Commands
 * 
 * @brief   A class to create the widget containing all commands/options.
 * 
 * @details This class is used to add all custom
 * 			widgets to a single window. This class
 * 			constructor is then called in main.cpp
 * 			to execute the entire application.
 */
class Commands: public QWidget
{
	Q_OBJECT

public:
	/** 
	 * @brief Constructor 
	 */
	Commands(QWidget * parent = nullptr);

	/** 
	 * @brief Destructor 
	 */
	virtual ~Commands() {}

private:
    /* */
    QSlider transSlider;
    QProgressBar progressBar;
    QPushButton okayButton;
    QPushButton exitButton;
    QPushButton invButton;

}; // end class Commands

#endif // COMMANDS_HPP