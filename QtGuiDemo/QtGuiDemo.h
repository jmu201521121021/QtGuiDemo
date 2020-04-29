#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiDemo.h"

#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>S
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QFormLayout>
#include <QObject>
#include <QMetaEnum>
#include <QDebug>
#include <QIcon>

#include <string>
#include <qstring.h>
#include <opencv2/opencv.hpp>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class QtGuiDemo : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiDemo(QWidget *parent = Q_NULLPTR);
	~QtGuiDemo();
	/**opencv mat 图像转为qImage, 显示在qLabel上**/
	void setCVMat2QtLabel(const cv::Mat &image, QLabel *qLabel);
// QT 界面初始化和槽
public slots:
	/* 界面*/
	void initView();
	void initMenu();
	void cleanMenu();
	void initLayout();
	void cleanLayout();
	/* 菜单槽函数 */
	void openVideoSlot();				// 打开本地视频文件槽
	void openPictureSlot();				// 打开图片槽
	void openCaptureSlot();
	void paintEvent(QPaintEvent *e);	// 实时现实槽

private:
	Ui::QtGuiDemoClass ui;
	/* 菜单栏 */
	QMenu *openFileMenu;
	
	QAction *openCaptureAction;			// 打开摄像头
	QAction *openVideoAction;			// 打开本地视频文件
	QAction *openPictureAction;			// 打开图片
	QLabel *imageLabel;					// 显示图片Label控件

	QWidget *centralWidget;

	cv::VideoCapture capture_;
	cv::Mat inputImage_;

	// 视频开关
	bool isOpenVedio_ = false;
	// 选择摸索 0. 打开图片文件 2.打开本地视频 3.打开本地摄像头
	int selectMode_;
};
