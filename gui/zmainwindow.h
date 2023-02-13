#ifndef ZMAINWINDOW_H
#define ZMAINWINDOW_H

#include <QMainWindow>

class ZMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	ZMainWindow(QWidget *parent = nullptr);
	~ZMainWindow();
};
#endif // Z_MAINWINDOW
