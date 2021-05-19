/** 
 * @file   printer.hpp
 * 
 * @brief  Contains the definitions of the Printer class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   December 8th, 2020
 */

#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <iostream>
#include <string>

/** 
 * @class   Printer
 * 
 * @brief   A class to create the main Qt window.
 * 
 * @details This class is used to provide basic
 * 			standard output as well as log all
 * 			output piped through it.
 */
class Printer
{

public:
	/** 
	 * @brief Constructor 
	 */
	Printer() {}

	/** 
	 * @brief Destructor 
	 */
	virtual ~Printer() {}

	/** 
	 * @brief Parameterized constructor 
     * 
     * @param windowSize the primary screen size
	 */
	void DEBUG(std::string input_string);
	void INFO(std::string input_string);
	void WARNING(std::string input_string);
	void ERROR(std::string input_string);
	void CRITICAL(std::string input_string);
	void INDENT(std::string input_string);
	void DIVIDER();
	

}; // end class Printer

#endif // PRINTER_HPP