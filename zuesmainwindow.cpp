#include "zuesmainwindow.h"
#include "zuesmdwidget.h"

ZuesMainWindow::ZuesMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ZuesMDWidget* kmd = new ZuesMDWidget(this);
	setCentralWidget(kmd);
	resize(800, 800);
}

ZuesMainWindow::~ZuesMainWindow()
{
}

