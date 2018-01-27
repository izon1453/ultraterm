#include "connectwidget.h"
#include "ui_connectwidget.h"

#include <QDebug>

ConnectWidget::ConnectWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ConnectWidget)
{
	ui->setupUi(this);

	ui->cboxBits->addItem("8", 8);
	ui->cboxBits->addItem("7", 7);
	ui->cboxBits->addItem("6", 6);
	ui->cboxBits->addItem("5", 5);

	ui->cboxParity->addItem("None", 0);
	ui->cboxParity->addItem("Odd", 1);
	ui->cboxParity->addItem("Even", 2);

	ui->cboxStopbits->addItem("1", 1);
	ui->cboxStopbits->addItem("2", 2);
}

ConnectWidget::~ConnectWidget()
{
	delete ui;
}
