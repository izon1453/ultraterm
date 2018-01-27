#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// connectWidget
	connectWidget = new ConnectWidget(this);
	ui->connectToolBar->addWidget(connectWidget);

	this->setMinimumWidth(connectWidget->width() + 10);
	ui->pltxOutput->adjustSize();
	ui->splitter->adjustSize();

	// File menu
	connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

	// View menu
	connect(ui->actionConnectToolbar, SIGNAL(toggled(bool)), ui->connectToolBar, SLOT(setVisible(bool)));
	connect(ui->actionInputArea, SIGNAL(toggled(bool)), ui->pltxInput, SLOT(setVisible(bool)));

	// Help menu
	connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

MainWindow::~MainWindow()
{
	delete connectWidget;

	delete ui;
}

void MainWindow::sltConnectToolbar(bool checked)
{
	if(checked)
		ui->connectToolBar->hide();
}

