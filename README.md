# QtGuiDemo
- QtGuiDemo是基于之前[人脸检测demo](https://github.com/jmu201521121021/FaceDetector-Base-Yolov3-spp)和[人脸识别demo](https://github.com/jmu201521121021/faceRecognition)整理出来的纯界面demo
- QtGuiDemo是用QT和OpenCV开发一个界面的demo,可简便选择本地图片、摄像头、视频文件来展示图像算法(深度学习、传统)处理结果
## 开发软件环境
- Windows 10
- QT 5.9
- OpenCV 3.3.0
- Visual Studio 2017
## 使用步骤
- 软件安装
  - download code:git clone https://github.com/jmu201521121021/QtGuiDemo.git
  - 安装QT,VS且在VS上配置QT
- 编译
  - 用VS 打开项目，进入属性管理器，选择**debug**模式下的配置文件opencv3.props修改自己opencv的include lib路径
  - 切记默认**debug**模式，**release**模式需要再加个opencv配置即可
- 接入自己图像处理算法
  - 接入自己图像处理算法可以通过处理this->inputImage输出结果显示在this->imageLabel控件上
  - 本地图片处理:void openPictureSlot()，在这个槽函数处理this->imputImage
  - 视频文件和本地摄像头处理:void paintEvent(QPaintEvent *e),在这个槽函数处理每一帧this->imageLabel
  - 整个界面整洁赶紧只有一个菜单栏功能模块和一个QLabel来显示图片

## 相关使用例子
- [人脸检测demo](https://github.com/jmu201521121021/FaceDetector-Base-Yolov3-spp)
- [人脸识别demo](https://github.com/jmu201521121021/faceRecognition)
