/** 
 * @file   main_window.cpp
 * 
 * @brief  Contains the implementation of the MainWindow class.
 * 
 * @author Morgan Chumbley
 * 
 * @date   July 10th, 2020
 */

#include "main_window.hpp"

MainWindow::MainWindow(QSize windowSize, QWidget *parent) : QWidget(parent), windowHeight(windowSize.height()), windowWidth(windowSize.width())
{
   /************************************************************************************************
    *
    *                             IMAGE VIEWER
    * 
    ************************************************************************************************/

   // Create the image viewer widget
   imgViewer = new ImageViewer();
   imgViewer->setFixedWidth(windowWidth / 2);

   /************************************************************************************************
    *
    *                             COMMANDS
    * 
    ************************************************************************************************/

   // Create buttons with their layout
   okayButton = new QPushButton(tr("OK"));
   exitButton = new QPushButton(tr("Cancel"));
   QHBoxLayout *bottomBar = new QHBoxLayout();
   bottomBar->setAlignment(Qt::AlignRight);
   bottomBar->addWidget(okayButton);
   bottomBar->addWidget(exitButton);

   // Create group box for commands
   QGroupBox *commandGroupBox = new QGroupBox(tr("Commands"));

   // Create & add commands
   invertCB = new QCheckBox(tr("Invert Watermark"));
   progressBar = new QProgressBar();
   progressBar->setOrientation(Qt::Horizontal);
   progressBar->setRange(0, 100);
   progressBar->setTextVisible(false);

   tranSlider = new QSlider(Qt::Horizontal);
   sizeSlider = new QSlider(Qt::Horizontal);
   tranSpinBox = new QSpinBox();
   sizeSpinBox = new QSpinBox();
   sizeSlider->setValue(100);
   sizeSpinBox->setValue(100);
   tranSlider->setRange(0, 100);
   sizeSlider->setRange(10, 100);
   tranSpinBox->setRange(0, 100);
   sizeSpinBox->setRange(10, 100);

   QHBoxLayout *tranLayout = new QHBoxLayout();
   tranLayout->addWidget(tranSpinBox);
   tranLayout->addWidget(tranSlider);

   QHBoxLayout *sizeLayout = new QHBoxLayout();
   sizeLayout->addWidget(sizeSpinBox);
   sizeLayout->addWidget(sizeSlider);

   // Create layout for commands
   QVBoxLayout *commandLayout = new QVBoxLayout();
   //commandLayout->setAlignment(Qt::AlignVCenter);
   commandLayout->addWidget(invertCB);
   commandLayout->addLayout(sizeLayout);
   commandLayout->addLayout(tranLayout);
   commandLayout->addWidget(progressBar);
   commandLayout->addLayout(bottomBar);
   commandGroupBox->setLayout(commandLayout);

   /************************************************************************************************
    *
    *                            LAYOUTS
    * 
    ************************************************************************************************/

   QHBoxLayout *mainLayout = new QHBoxLayout();
   mainLayout->addWidget(imgViewer);
   mainLayout->addWidget(commandGroupBox);
   setLayout(mainLayout);

   /************************************************************************************************
    *
    *                            CONNECTIONS
    * 
    ************************************************************************************************/

   QObject::connect(invertCB, &QCheckBox::stateChanged, 
                     [=](int state) { checkBox_slot(state); });

   // Tran slider changed
   QObject::connect(tranSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
                     [=](int value) { tranValueChanged(0, value); });

   // Tran spin box changed
   QObject::connect(tranSlider, &QSlider::valueChanged, 
                     [=](int value) { tranValueChanged(1, value); });		

   // Size spin box changed
   QObject::connect(sizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), 
                     [=](int value) { sizeValueChanged(0, value); });

   // Size slider changed
   QObject::connect(sizeSlider, &QSlider::valueChanged, 
                     [=](int value) { sizeValueChanged(1, value); });

   // when the OK button pressed
   QObject::connect(okayButton, &QPushButton::clicked, 
                     [=]() { okayButtonPressed_slot(); });

   // when the exit button pressed
   QObject::connect(exitButton, &QPushButton::clicked, 
                     [=]() { exitButtonPressed_slot(); });
}

void MainWindow::init(QString path, QString wmPath, bool isPathDir)
{
   // First, set the paths
   this->setPaths(path, wmPath);

   // Load watermarked image and then the invert of it
   wmImg = cv::imread(_wmPath.toStdString());
   wmImg_n = ~wmImg;

   if(isPathDir) { // Is it a directory
      // Use glob to store a vector of all filenames
      cv::glob(_mnPath.toStdString(), filenames);
   }
   else { // If not then it must be a file
      filenames.push_back(_mnPath.toStdString());
   }

   if(filenames.size() == 1) { // For single images
      imgViewer->init(filenames[0], _wmPath.toStdString());
   }
   else { // For directories with many images
      this->okayButtonPressed_slot();
   }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
   windowWidth = this->width();
   windowHeight = this->height();
   imgViewer->setFixedWidth(windowWidth / 2);
   QWidget::resizeEvent(event);
}

void MainWindow::setPaths(QString path, QString wmPath) 
{
   _mnPath = path;
   _wmPath = wmPath;
}

void MainWindow::okayButtonPressed_slot()
{
   static int i = 0;
   if(i < filenames.size()) {
      qInfo() << "Advance to " << QString::fromStdString(filenames[i]);
      imgViewer->init(filenames[i], _wmPath.toStdString());
      i++;
   }
   else {
      this->exitButtonPressed_slot();
   }
}

void MainWindow::exitButtonPressed_slot()
{
   qInfo() << "Done. Exiting...";
   this->close();
}

void MainWindow::checkBox_slot(int state) 
{
   switch(state) {
      case 0:
         qInfo() << "Inverted watermark: OFF";
         break;
      case 1: 
         qInfo() << "tristate 1";
         break;
      case 2:
         qInfo() << "Inverted watermark: ON";
         break;
      default:
         break;
   }
}

void MainWindow::tranValueChanged(int8_t ident, int value)
{
   switch(ident){
      case 0: // Case where the spin box triggers the slider to change
         tranSlider->setValue(value);
         break;
      case 1: // Case where the slider triggers the spin box to change
         tranSpinBox->setValue(value);
         break;
      default:
         break;
   }
   wmTran = value;
}

void MainWindow::sizeValueChanged(int8_t ident, int value)
{
   switch(ident){
      case 0: // Case where the spin box triggers the slider to change
         sizeSlider->setValue(value);
         break;
      case 1: // Case where the slider triggers the spin box to change
         sizeSpinBox->setValue(value);
         break;
      default:
         break;
   }
   wmSize = value;
   imgViewer->changeWMScale(wmSize);
}