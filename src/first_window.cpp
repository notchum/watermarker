/** 
 * @file   first_window.cpp
 * 
 * @brief  Contains the implementation of the FirstWindow class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 8th, 2020
 */

#include "first_window.hpp"
#include "lib/logger/logger.hpp"

FirstWindow::FirstWindow(QWidget *parent) : QWidget(parent)
{
   batcRadio = new QRadioButton(tr("Batch"));
   indvRadio = new QRadioButton(tr("Individual"));
   batcRadio->setChecked(true);

   QVBoxLayout *radioLayout = new QVBoxLayout();
   radioLayout->setAlignment(Qt::AlignHCenter);
   radioLayout->addWidget(new QLabel(tr("Select an option:")));
   radioLayout->addWidget(batcRadio);
   radioLayout->addWidget(indvRadio);

   pathLineEdit = new QLineEdit();
   pathButton = new QPushButton(tr("Browse"));
   pathLineEdit->setFixedWidth(200);
   pathLineEdit->setReadOnly(true);

   QHBoxLayout *pathBar = new QHBoxLayout();
   pathBar->addWidget(pathLineEdit);
   pathBar->addWidget(pathButton);

   okayButton = new QPushButton(tr("OK"));
   exitButton = new QPushButton(tr("Cancel"));
   okayButton->setDisabled(true);

   QHBoxLayout *bottomBar = new QHBoxLayout();
   bottomBar->setAlignment(Qt::AlignRight);
   bottomBar->addWidget(okayButton);
   bottomBar->addWidget(exitButton);

   QVBoxLayout *mainLayout = new QVBoxLayout();
   mainLayout->addLayout(radioLayout);
   mainLayout->addWidget(new QLabel(tr("Select location:")));
   mainLayout->addLayout(pathBar);
   mainLayout->addLayout(bottomBar);
   setLayout(mainLayout);

   // when the batch radio button is selected
   QObject::connect(batcRadio, &QRadioButton::clicked, 
                     [=]() { radioButton_slot(radio_buttons::BATC_RADIO); });

   // when the individual radio button is selected
   QObject::connect(indvRadio, &QRadioButton::clicked, 
                     [=]() { radioButton_slot(radio_buttons::IDNV_RADIO); });

   // when the browse path button pressed
   QObject::connect(pathButton, &QPushButton::clicked, 
                     [=]() { selectPath_slot(); });

   // when the OK button pressed
   QObject::connect(okayButton, &QPushButton::clicked, 
                     [=]() { okayButtonPressed_slot(); });

   // when the exit button pressed
   QObject::connect(exitButton, &QPushButton::clicked, 
                     [=]() { exitButtonPressed_slot(); });
}

QString FirstWindow::getPath()
{
   return path;
}

bool FirstWindow::isPathFile()
{
   return QFileInfo::exists(path) && QFileInfo(path).isFile();
}

bool FirstWindow::isPathDir()
{
   return QFileInfo::exists(path) && QFileInfo(path).isDir();
}

void FirstWindow::radioButton_slot(radio_buttons index)
{
   bool isPathFile = this->isPathFile();
   bool isPathDir = this->isPathDir();

   switch(index) {
      case radio_buttons::BATC_RADIO:
         LOG::INFO("Batch option selected");
         currentOption = radio_buttons::BATC_RADIO;
         if(isPathDir) {
               okayButton->setEnabled(true);
         }
         else {
               okayButton->setDisabled(true);
         }
         break;
      case radio_buttons::IDNV_RADIO:
         LOG::INFO("Individual option selected");
         currentOption = radio_buttons::IDNV_RADIO;
         if(isPathFile) {
               okayButton->setEnabled(true);
         }
         else {
               okayButton->setDisabled(true);
         }
         break;
      default:
         break;
   }
}

void FirstWindow::selectPath_slot()
{
   if(currentOption == radio_buttons::BATC_RADIO) {
      path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                QDir::homePath(),
                                                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
   }
   else if(currentOption == radio_buttons::IDNV_RADIO) {
      path = QFileDialog::getOpenFileName(this, tr("Open Photo"),
                                                QDir::homePath(),
                                                tr("Images (*.png *.jpeg *.jpg);; All files (*.*)"));
   }

   if(QFileInfo::exists(path)) {
      LOG::INFO(("Selected " + path.toStdString()).c_str());
      pathLineEdit->setText(path);
      okayButton->setEnabled(true);
   }
   else {
      LOG::INFO("Path does not exist");
      okayButton->setDisabled(true);
   }
}

void FirstWindow::okayButtonPressed_slot()
{
   emit okayButtonPressed();
   LOG::DEBUG("FirstWindow okayButtonPressed emitted");
}

void FirstWindow::exitButtonPressed_slot()
{
   LOG::INFO("Done. Exiting...");
   this->close();
}