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
	/**opencv mat ͼ��תΪqImage, ��ʾ��qLabel��**/
	void setCVMat2QtLabel(const cv::Mat &image, QLabel *qLabel);
// QT �����ʼ���Ͳ�
public slots:
	/* ����*/
	void initView();
	void initMenu();
	void cleanMenu();
	void initLayout();
	void cleanLayout();
	/* �˵��ۺ��� */
	void openVideoSlot();				// �򿪱�����Ƶ�ļ���
	void openPictureSlot();				// ��ͼƬ��
	void openCaptureSlot();
	void paintEvent(QPaintEvent *e);	// ʵʱ��ʵ��

private:
	Ui::QtGuiDemoClass ui;
	/* �˵��� */
	QMenu *openFileMenu;
	
	QAction *openCaptureAction;			// ������ͷ
	QAction *openVideoAction;			// �򿪱�����Ƶ�ļ�
	QAction *openPictureAction;			// ��ͼƬ
	QLabel *imageLabel;					// ��ʾͼƬLabel�ؼ�

	QWidget *centralWidget;

	cv::VideoCapture capture_;
	cv::Mat inputImage_;

	// ��Ƶ����
	bool isOpenVedio_ = false;
	// ѡ������ 0. ��ͼƬ�ļ� 2.�򿪱�����Ƶ 3.�򿪱�������ͷ
	int selectMode_;
};
