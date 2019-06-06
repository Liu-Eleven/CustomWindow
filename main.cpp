#include "CustomWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CustomWindow w;
    //w.showMaximized();
    w.show();
	return a.exec();
}
