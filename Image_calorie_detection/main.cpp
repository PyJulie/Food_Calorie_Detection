#include "Image_calorie_detection.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Image_calorie_detection w;
	w.show();
	return a.exec();
}
