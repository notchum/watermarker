/** 
 * @file   second_window.hpp
 * 
 * @brief  Contains the definitions of the SecondWindow class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 8th, 2020
 */

#ifndef SECOND_WINDOW_HPP
#define SECOND_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QFileDialog>

/** 
 * @class   SecondWindow
 * 
 * @brief   A class to create the main Qt window.
 * 
 * @details A more detailed class description.
 * 			Class description continued
 */
class SecondWindow : public QWidget
{
   Q_OBJECT

public:
   /** 
    * @brief Constructor 
    */
   SecondWindow(QWidget * parent = nullptr);

   /** 
    * @brief Destructor 
    */
   virtual ~SecondWindow() {}

   /** 
    * @brief Getter for input path 
    */
   QString getPath();

signals:
   /** 
    * @brief Qt signal for when the okay button is pressed
    */
   void okayButtonPressed();

public slots:
   /** 
    * @brief Qt slot for when the okay button is pressed
    */
   void okayButtonPressed_slot();

   /** 
    * @brief Qt slot for when the exit button is pressed
    */
   void exitButtonPressed_slot();

   /** 
    * @brief Qt slot for when the browse path button is pressed
    */
   void selectPath_slot();

private:
   /* Required advance or exit buttons */
   QPushButton *okayButton;
   QPushButton *exitButton;

   /* The file browser widgets */
   QPushButton *wmButton;
   QLineEdit *wmLineEdit;
   QString path;

}; // end class SecondWindow

#endif // SECOND_WINDOW_HPP