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

SecondWindow::SecondWindow(QWidget *parent) : QWidget(parent)
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
}

QString SecondWindow::getPath()
{
   return path;
}

void SecondWindow::selectPath_slot()
{
   path = QFileDialog::getOpenFileName(this, tr("Open Photo"),
                                       QDir::homePath(),
                                       tr("Images (*.png *.jpeg *.jpg);; All files (*.*)"));
   if(QFileInfo::exists(path)) {
      qInfo() << "Selected " << path;
      wmLineEdit->setText(path);
      okayButton->setEnabled(true);
   }
   else {
      qInfo() << "Path does not exist";
      okayButton->setDisabled(true);
   }
}

void SecondWindow::okayButtonPressed_slot()
{
   emit okayButtonPressed();
   qInfo() << "SecondWindow okayButtonPressed emitted";
}

void SecondWindow::exitButtonPressed_slot()
{
   qInfo() << "Done. Exiting...";
   this->close();
}