#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Image_calorie_detection.h"
#include "ClogoRecognition.h"
#include <qfiledialog.h>
#include <qdebug.h>
class Image_calorie_detection : public QMainWindow
{
	Q_OBJECT

public:
	Image_calorie_detection(QWidget *parent = Q_NULLPTR);
	ClogoRecognition cl;
private:
	Ui::Image_calorie_detectionClass ui;

private slots:
void toGetCalorie() {
	QString filename = QFileDialog::getOpenFileName(this, "Open Image");
	if (filename.length() == 0) {
		return;
	}
	QPixmap image;
	QSize picSize(361, 181);
	image.load(filename);
	QPixmap scaledPixmap = image.scaled(picSize, Qt::KeepAspectRatio);
	ui.label_3->clear();
	ui.label_3->setPixmap(scaledPixmap);
	qDebug() << (361 - scaledPixmap.width()) / 2 << " " << ui.label_3->y() << " " << scaledPixmap.width() << " " << scaledPixmap.height();
	ui.label_3->setGeometry((622 - scaledPixmap.width())/2,ui.label_3->y(),scaledPixmap.width(),scaledPixmap.height());
	ui.label->setScaledContents(true);
	ui.label_3->show();
	int result = cl.svmTest(filename.toStdString());
	if (result == 1) {
		this->ui.label_2->setText("it's probably Egg Tart,Calorie:375 Cal/100g");
		
	}
	else if(result == 2){
		this->ui.label_2->setText("it's probably Strawberry,Calorie:30 Cal/100g");
	}
	else if(result == 3)
	{
		this->ui.label_2->setText("it's probably Cabbage,Calorie:17 Cal/100g");
	}
}
};
