/** 
 * @file   second_window.cpp
 * 
 * @brief  Contains the implementation of the SecondWindow class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 8th, 2020
 */

#include "second_window.hpp"
#include "lib/logger/logger.hpp"

SecondWindow::SecondWindow( QWidget *parent ) : QWidget(parent)
{
   wmLineEdit = new QLineEdit();
   wmButton = new QPushButton(tr("Browse"));
   wmLineEdit->setFixedWidth(200);
   wmLineEdit->setReadOnly(true);

   QHBoxLayout *wmPathBar = new QHBoxLayout();
   wmPathBar->addWidget(wmLineEdit);
   wmPathBar->addWidget(wmButton);

   okayButton = new QPushButton(tr("OK"));
   exitButton = new QPushButton(tr("Cancel"));
   okayButton->setDisabled(true);

   QHBoxLayout *bottomBar = new QHBoxLayout();
   bottomBar->setAlignment(Qt::AlignRight);
   bottomBar->addWidget(okayButton);
   bottomBar->addWidget(exitButton);

   QVBoxLayout *mainLayout = new QVBoxLayout();
   mainLayout->addWidget(new QLabel(tr("Select watermark location:")));
   mainLayout->addLayout(wmPathBar);
   mainLayout->addLayout(bottomBar);
   setLayout(mainLayout);

   // when the browse path button pressed
   QObject::connect(wmButton, &QPushButton::clicked, 
                  [=]() { selectPath_slot(); });

   // when the OK button pressed
   QObject::connect(okayButton, &QPushButton::clicked, 
                  [=]() { okayButtonPressed_slot(); });

   // when the exit button pressed
   QObject::connect(exitButton, &QPushButton::clicked, 
                  [=]() { exitButtonPressed_slot(); });
} // end SecondWindow::SecondWindow()

QString SecondWindow::getPath( void )
{
   return path;
} // end SecondWindow::getPath()

void SecondWindow::selectPath_slot( void )
{
   path = QFileDialog::getOpenFileName(this, tr("Open Photo"),
                                       QDir::homePath(),
                                       tr("Images (*.png *.jpeg *.jpg);; All files (*.*)"));
   if(QFileInfo::exists(path)) {
      LOG_INFO("Selected {}\n", path.toStdString());
      wmLineEdit->setText(path);
      okayButton->setEnabled(true);
   }
   else {
      LOG_INFO("Path does not exist\n");
      okayButton->setDisabled(true);
   }
} // end SecondWindow::selectPath_slot()

void SecondWindow::okayButtonPressed_slot( void )
{
   emit okayButtonPressed();
   LOG_DEBUG("SecondWindow okayButtonPressed emitted\n");
} // end SecondWindow::okayButtonPressed_slot()

void SecondWindow::exitButtonPressed_slot( void )
{
   LOG_INFO("Done. Exiting...\n");
   this->close();
} // end SecondWindow::exitButtonPressed_slot()