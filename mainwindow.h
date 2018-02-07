#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "connectwidget.h"
#include "serialport.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;

	ConnectWidget *connectWidget;

	SerialPort *serial;

private slots:
	void connOpen();
	void connClose();
};

#endif // MAINWINDOW_H
