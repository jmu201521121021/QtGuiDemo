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
	/* �˵� */
	initMenu();
	/* ���� */
	initLayout();
}
/**
* @brief MainWindow::initMenu - ��ʼ���˵���
*/
void QtGuiDemo::initMenu()
{

	/* �ļ��˵�ui���� */
	openFileMenu = new QMenu(SQ("����ģ��"));

	openPictureAction = new QAction(SQ("ͼƬ�ļ�"), this);
	connect(openPictureAction, SIGNAL(triggered()), this, SLOT(openPictureSlot()));
	openFileMenu->addAction(openPictureAction);

	openVideoAction = new QAction(SQ("����Ƶ�ļ�"), this);
	connect(openVideoAction, SIGNAL(triggered()), this, SLOT(openVideoSlot()));
	openFileMenu->addAction(openVideoAction);

	openCaptureAction = new QAction(SQ("������ͷ"), this);
	connect(openCaptureAction, SIGNAL(triggered()), this, SLOT(openCaptureSlot()));
	openFileMenu->addAction(openCaptureAction);

	/* ������ģ����ӵ��˵����� */
	QMenuBar *menuBar = this->menuBar();
	menuBar->addMenu(openFileMenu);

	/* LOGO */
	this->setWindowTitle(SQ("QtGuiDemo"));
}

/**
* @brief MainWindow::initLayout - ��ʼ���ؼ�����
*/
void QtGuiDemo::initLayout()
{
	/* ͼƬ��ʾ��� */
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
	qLabel->clear();                                //��տؼ�label
	qLabel->setPixmap(QPixmap::fromImage(qImg));    //label��ֵ
	qLabel->show();
	qLabel->update();
}

void QtGuiDemo::openPictureSlot()
{
	this->selectMode_ = 0;
	QString imageFilePath;
	imageFilePath = QFileDialog::getOpenFileName(
		this,
		SQ("ѡ��ͼƬ�ļ�"),
		QDir::currentPath(),
		"All files(*.jpg *JPG *.jpeg *.png *.PNG *.gif *.bmp)");																						// ���ݼ��
	if (QS(imageFilePath).empty())
	{
		qDebug()<< "The imageFilePath is not exit!!!\n";
		return;
	}
	this->inputImage_ = cv::imread(QS(imageFilePath));
	this->setCVMat2QtLabel(this->inputImage_, this->imageLabel);
}


// ��������ͷ��
void QtGuiDemo::openVideoSlot() 
{
	
	QString vedioFilePath;
	vedioFilePath = QFileDialog::getOpenFileName(
		this,
		SQ("ѡ����Ƶ�ļ�"),
		QDir::currentPath(),
		"All files(*.mp4 *.MP4 *.AVI *.avi)");																						// ���ݼ��
	if (QS(vedioFilePath).empty())
	{
		qDebug() << "The VedioFilePath is not exit!!!\n";
		this->isOpenVedio_ = false;
		return;
	}
	
	if (this->capture_.isOpened())
	{
		this->capture_.release();
	}
	if (!this->capture_.open(QS(vedioFilePath)))
	{
		qDebug() << "open video false!!!";
		this->isOpenVedio_ = false;
	}
	else
	{
		this->selectMode_ = 1;
		this->isOpenVedio_ = true;
		qDebug() << "open video file successful 0\n";
	}
	
	
}

void QtGuiDemo:: openCaptureSlot()
{
	if (openCaptureAction->text() == SQ("������ͷ"))
	{
		this->selectMode_ = 2;
		if (!this->capture_.open(0))
		{
			if (!this->capture_.open(0)) {
				// capture.open(0);
			}
			qDebug() << "open video false 0";

		}
		qDebug() << "open video successful 0\n";
		this->isOpenVedio_ = true;
		this->openCaptureAction->setText(SQ("�ر�����ͷ"));

	}
	else
	{
		openCaptureAction->setText(SQ("������ͷ"));
		this->capture_.release();
		this->isOpenVedio_ = false;
	}
}


// ʵʱ��ʾ��Ƶ��
void QtGuiDemo::paintEvent(QPaintEvent *e)
{

	if (this->isOpenVedio_ && (this->selectMode_>0))
	{
		bool isRead = this->capture_.read(this->inputImage_);
		if (isRead)
		{
			this->setCVMat2QtLabel(inputImage_, this->imageLabel);
		}
		else 
		{
			this->isOpenVedio_ = false;
			this->capture_.release();
		}
	}
	
	else if (!this->isOpenVedio_ && (this->selectMode_>0))
	{
		this->imageLabel->clear();
	}
}
