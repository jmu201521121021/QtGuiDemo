#include "QtGuiDemo.h"
#include"common.h"

#include <QFileDialog>

QtGuiDemo::QtGuiDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	initView();
}
QtGuiDemo::~QtGuiDemo()
{
	cleanMenu();
	cleanLayout();
}
void QtGuiDemo::initView()
{
	/* 菜单 */
	initMenu();
	/* 布局 */
	initLayout();
}
/**
* @brief MainWindow::initMenu - 初始化菜单栏
*/
void QtGuiDemo::initMenu()
{

	/* 文件菜单ui设置 */
	openFileMenu = new QMenu(SQ("功能模块"));

	openPictureAction = new QAction(SQ("图片文件"), this);
	connect(openPictureAction, SIGNAL(triggered()), this, SLOT(openPictureSlot()));
	openFileMenu->addAction(openPictureAction);

	openVideoAction = new QAction(SQ("打开视频文件"), this);
	connect(openVideoAction, SIGNAL(triggered()), this, SLOT(openVideoSlot()));
	openFileMenu->addAction(openVideoAction);

	openCaptureAction = new QAction(SQ("打开摄像头"), this);
	connect(openCaptureAction, SIGNAL(triggered()), this, SLOT(openCaptureSlot()));
	openFileMenu->addAction(openCaptureAction);

	/* 将功能模块添加到菜单栏上 */
	QMenuBar *menuBar = this->menuBar();
	menuBar->addMenu(openFileMenu);

	/* LOGO */
	this->setWindowTitle(SQ("QtGuiDemo"));
}

/**
* @brief MainWindow::initLayout - 初始化控件布局
*/
void QtGuiDemo::initLayout()
{
	/* 图片显示面板 */
	centralWidget = new QWidget(this);
	imageLabel = new  QLabel(centralWidget);
	imageLabel->setScaledContents(true);
	QSize labelSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	imageLabel->setFixedSize(labelSize);
	this->setCentralWidget(centralWidget);
	this->resize(SCREEN_WIDTH, SCREEN_HEIGHT);
	this->show();
}

void QtGuiDemo::cleanMenu()
{
	if (openFileMenu)
	{
		delete openFileMenu;
		openFileMenu = NULL;
	}
	if (openCaptureAction)
	{
		delete openCaptureAction;
		openCaptureAction = NULL;
	}
	if (openVideoAction)
	{
		delete openVideoAction;
		openVideoAction = NULL;
	}

	if (openPictureAction)
	{
		delete openPictureAction;
		openPictureAction = NULL;
	}
}

void QtGuiDemo::cleanLayout()
{

	if (centralWidget)
	{
		delete centralWidget;
		centralWidget = NULL;
	}

}

void QtGuiDemo::setCVMat2QtLabel(const cv::Mat &image, QLabel *qLabel)
{
	cv::Mat showImg;
	cv::cvtColor(image, showImg, CV_BGR2RGB); 
	QImage qImg = QImage((const uchar *)(showImg.data),
		showImg.cols, showImg.rows,
		showImg.cols * showImg.channels(),
		QImage::Format_RGB888);
	qLabel->clear();                                //清空控件label
	qLabel->setPixmap(QPixmap::fromImage(qImg));    //label赋值
	qLabel->show();
	qLabel->update();
}

void QtGuiDemo::openPictureSlot()
{
	this->selectMode = 0;
	QString imageFilePath;
	imageFilePath = QFileDialog::getOpenFileName(
		this,
		SQ("选择图片文件"),
		QDir::currentPath(),
		"All files(*.jpg *JPG *.jpeg *.png *.PNG *.gif *.bmp)");																						// 数据检查
	if (QS(imageFilePath).empty())
	{
		qDebug()<< "The imageFilePath is not exit!!!\n";
		return;
	}
	this->inputImage = cv::imread(QS(imageFilePath));
	this->setCVMat2QtLabel(this->inputImage, this->imageLabel);
}


// 本地摄像头槽
void QtGuiDemo::openVideoSlot() 
{
	
	QString vedioFilePath;
	vedioFilePath = QFileDialog::getOpenFileName(
		this,
		SQ("选择视频文件"),
		QDir::currentPath(),
		"All files(*.mp4 *.MP4 *.AVI *.avi)");																						// 数据检查
	if (QS(vedioFilePath).empty())
	{
		qDebug() << "The VedioFilePath is not exit!!!\n";
		return;
	}
	
	if (this->capture.isOpened())
	{
		this->capture.release();
	}
	if (!this->capture.open(QS(vedioFilePath)))
	{
			qDebug() << "open video false 0";
	}
	else
	{
		this->selectMode = 1;
		this->isOpenVedio = true;
		qDebug() << "open video file successful 0\n";
	}
	
	
}

void QtGuiDemo:: openCaptureSlot()
{
	if (openCaptureAction->text() == SQ("打开摄像头"))
	{
		this->selectMode = 2;
		if (!this->capture.open(0))
		{
			if (!this->capture.open(0)) {
				// capture.open(0);
			}
			qDebug() << "open video false 0";

		}
		qDebug() << "open video successful 0\n";
		this->isOpenVedio = true;
		this->openCaptureAction->setText(SQ("关闭摄像头"));

	}
	else
	{
		openCaptureAction->setText(SQ("打开摄像头"));
		this->capture.release();
		this->isOpenVedio = false;
	}
}


// 实时显示视频流
void QtGuiDemo::paintEvent(QPaintEvent *e)
{

	if (this->isOpenVedio && (this->selectMode>0))
	{
		this->capture >> this->inputImage;
		this->setCVMat2QtLabel(inputImage, this->imageLabel);
	}
	
	else if (!this->isOpenVedio && (this->selectMode>0))
	{
		this->imageLabel->clear();
	}
}
