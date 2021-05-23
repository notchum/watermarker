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

FirstWindow::FirstWindow( QWidget *parent ) : QWidget(parent)
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
                     [=]() { radioButton_slot(RadioButton::BATC_RADIO); });

   // when the individual radio button is selected
   QObject::connect(indvRadio, &QRadioButton::clicked, 
                     [=]() { radioButton_slot(RadioButton::IDNV_RADIO); });

   // when the browse path button pressed
   QObject::connect(pathButton, &QPushButton::clicked, 
                     [=]() { selectPath_slot(); });

   // when the OK button pressed
   QObject::connect(okayButton, &QPushButton::clicked, 
                     [=]() { okayButtonPressed_slot(); });

   // when the exit button pressed
   QObject::connect(exitButton, &QPushButton::clicked, 
                     [=]() { exitButtonPressed_slot(); });
} // end FirstWindow::FirstWindow()

QString FirstWindow::getPath( void )
{
   return path;
} // end FirstWindow::getPath()

bool FirstWindow::isPathFile( void )
{
   return QFileInfo::exists(path) && QFileInfo(path).isFile();
} // end FirstWindow::isPathFile()

bool FirstWindow::isPathDir( void )
{
   return QFileInfo::exists(path) && QFileInfo(path).isDir();
} // end FirstWindow::isPathDir()

void FirstWindow::radioButton_slot( RadioButton index )
{
   bool isPathFile = this->isPathFile();
   bool isPathDir = this->isPathDir();

   switch(index) {
      case RadioButton::BATC_RADIO:
         LOG_INFO("Batch option selected\n");
         currentOption = RadioButton::BATC_RADIO;
         if(isPathDir) {
               okayButton->setEnabled(true);
         }
         else {
               okayButton->setDisabled(true);
         }
         break;
      case RadioButton::IDNV_RADIO:
         LOG_INFO("Individual option selected\n");
         currentOption = RadioButton::IDNV_RADIO;
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
} // end FirstWindow::radioButton_slot()

void FirstWindow::selectPath_slot( void )
{
   if(currentOption == RadioButton::BATC_RADIO) {
      path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                QDir::homePath(),
                                                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
   }
   else if(currentOption == RadioButton::IDNV_RADIO) {
      path = QFileDialog::getOpenFileName(this, tr("Open Photo"),
                                                QDir::homePath(),
                                                tr("Images (*.png *.jpeg *.jpg);; All files (*.*)"));
   }

   if(QFileInfo::exists(path)) {
      LOG_INFO("Selected {}\n", path.toStdString());
      pathLineEdit->setText(path);
      okayButton->setEnabled(true);
   }
   else {
      LOG_INFO("Path does not exist\n");
      okayButton->setDisabled(true);
   }
} // end FirstWindow::selectPath_slot()

void FirstWindow::okayButtonPressed_slot( void )
{
   emit okayButtonPressed();
   LOG_DEBUG("FirstWindow okayButtonPressed emitted\n");
} // end FirstWindow::okayButtonPressed_slot()

void FirstWindow::exitButtonPressed_slot( void )
{
   LOG_INFO("Done. Exiting...\n");
   this->close();
} // end FirstWindow::exitButtonPressed_slot()