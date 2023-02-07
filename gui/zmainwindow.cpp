#include "zmainwindow.h"

#include "ztextedit.h"

ZMainWindow::ZMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ZTextEdit* kmd = new ZTextEdit(this);
	setCentralWidget(kmd);
	resize(800, 800);
}

ZMainWindow::~ZMainWindow()
{
}

