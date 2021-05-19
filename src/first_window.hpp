/** 
 * @file   first_window.hpp
 * 
 * @brief  Contains the definitions of the FirstWindow class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   June 1st, 2020
 */

#ifndef FIRST_WINDOW_HPP
#define FIRST_WINDOW_HPP

#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QFileInfo>

/** 
 * @class   FirstWindow
 * 
 * @brief   A class to create the main Qt window.
 * 
 * @details A more detailed class description.
 * 			Class description continued
 */
class FirstWindow : public QWidget
{
   Q_OBJECT

public:
   /** 
    * @brief Constructor 
    */
   FirstWindow( QWidget * parent = nullptr );

   /** 
    * @brief Destructor 
    */
   virtual ~FirstWindow( void ) {}

   /** 
    * @brief Getter for input path 
    */
   QString getPath( void );

   /** 
    * @brief Check if path exists and if yes: Is it a file and no directory?
    */
   bool isPathFile( void );

   /** 
    * @brief Check if path exists and if yes: Is it a directory?
    */
   bool isPathDir( void );

   // Enum used for keeping track of current radio button
   enum class RadioButton
   {
      BATC_RADIO,
      IDNV_RADIO
   };

signals:
   /** 
    * @brief Qt signal for when the okay button is pressed
    */
   void okayButtonPressed( void );

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
    * 
    * @param index the index of the radio button selected
    */
   void radioButton_slot( RadioButton index );

   /** 
    * @brief Qt slot for when the browse path button is pressed
    */
   void selectPath_slot( void );

private:
   /* Required advance or exit buttons */
   QPushButton *okayButton;
   QPushButton *exitButton;

   /* Mutually exclusive radio buttons */
   QRadioButton *batcRadio;
   QRadioButton *indvRadio;
   RadioButton currentOption;

   /* The file browser widgets */
   QPushButton *pathButton;
   QLineEdit *pathLineEdit;
   QString path;

}; // end class FirstWindow

#endif // FIRST_WINDOW_HPP