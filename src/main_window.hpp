/** 
 * @file   main_window.hpp
 * 
 * @brief  Contains the definitions of the MainWindow class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   May 29th, 2020
 */

#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "first_window.hpp"
#include "second_window.hpp"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

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
	MainWindow(QWidget * parent = nullptr);

	/** 
	 * @brief Destructor 
	 */
	virtual ~MainWindow() {}

	// Enum used for keeping track of current window
	enum class windows
	{
		FIRST_WINDOW,
		SECOND_WINDOW,
		MAIN_WINDOW
	};

public slots:
	/** 
	 * @brief Qt slot for disabling (changing to red) a QFrame
     * 
     * @param frame pointer to the QFrame to be altered
	 */
	//void disableIndLight(QFrame *frame);

	void advanceWindow();

private:
	windows current_window;
	FirstWindow first_window;
	SecondWindow second_window;

}; // end class MainWindow

#endif // MAIN_WINDOW_HPP