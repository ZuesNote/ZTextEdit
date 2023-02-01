#include "zuesmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ZuesMainWindow w;
	w.show();
	return a.exec();
}
