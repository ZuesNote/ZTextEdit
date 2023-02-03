#include <QApplication>

#include "./gui/zmainwindow.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ZMainWindow w;
	w.show();
	return a.exec();
}
