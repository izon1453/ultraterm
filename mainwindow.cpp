#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSerialPort>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// serial
	serial = new SerialPort();

	// connectWidget
	connectWidget = new ConnectWidget(this);
	ui->deviceToolBar->addWidget(connectWidget);

	this->setMinimumWidth(ui->mainToolBar->width() + connectWidget->width());

	// File menu
	connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(connOpen()));
	connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(connClose()));
	connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

	// View menu
	connect(ui->actionMainToolbar, SIGNAL(toggled(bool)), ui->mainToolBar, SLOT(setVisible(bool)));
	connect(ui->actionDeviceToolbar, SIGNAL(toggled(bool)), ui->deviceToolBar, SLOT(setVisible(bool)));
	connect(ui->actionWriteArea, SIGNAL(toggled(bool)), ui->pltxInput, SLOT(setVisible(bool)));

	// Help menu
	connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
	if(serial->isOpen())
		serial->close();
	delete serial;

	delete connectWidget;

	delete ui;
}

void MainWindow::connOpen()
{
	QString portName = connectWidget->getPortName();

	serial->setPortName(portName);
	if(serial->open(QIODevice::ReadWrite))
	{
		qDebug() << serial->portName();
		if(serial->setBaudRate(connectWidget->getBaudRate()))
		{
			connectWidget->getDataBits();
			qDebug() << connectWidget->getParity();
		}
		qDebug() << connectWidget->getBaudRate();
	}
	else
	{
		QMessageBox msgBox;
		msgBox.setText(QString("Cannot open \"%1\" port!").arg(portName));
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();
	}
}

void MainWindow::connClose()
{

}
