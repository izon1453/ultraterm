#include "connectwidget.h"
#include "ui_connectwidget.h"

#include <QDebug>
#include <QSerialPortInfo>

ConnectWidget::ConnectWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ConnectWidget)
{
	ui->setupUi(this);

	renewTimer = new QTimer(this);
	connect(renewTimer, SIGNAL(timeout()), this, SLOT(renewPorts()));
	renewTimer->start(1000);

	ui->cboxBits->addItem("8", 8);
	ui->cboxBits->addItem("7", 7);
	ui->cboxBits->addItem("6", 6);
	ui->cboxBits->addItem("5", 5);

	ui->cboxStopbits->addItem("1", 1);
	ui->cboxStopbits->addItem("2", 2);

	renewPorts();
}

ConnectWidget::~ConnectWidget()
{
	delete renewTimer;

	delete ui;
}

QString ConnectWidget::getPortName()
{
	return ui->cboxPort->itemText(ui->cboxPort->currentIndex());
}

quint32 ConnectWidget::getBaudRate()
{
	qint32 tmpBaudRate = ui->cboxBaudrate->currentText().toInt();
	if(tmpBaudRate < 0)
	{
		tmpBaudRate = 0;
		ui->cboxBaudrate->setCurrentText("0");
	}
	return (quint32)tmpBaudRate;
}

/**
 * @brief ConnectWidget::renewPorts Обновляет список com-портов в виджете.
 */
void ConnectWidget::renewPorts()
{
	bool f_renew = false;
	QList<QSerialPortInfo> tmpAvailPorts = QSerialPortInfo::availablePorts();

	if(portList.length() == tmpAvailPorts.length())
	{
		for(int i = 0; i < portList.length(); i++)
			if(portList.at(i).portName() != tmpAvailPorts.at(i).portName())
			{
				f_renew = true;
				break;
			}
	}
	else
		f_renew = true;

	if(f_renew)
	{
		portList = tmpAvailPorts;
		ui->cboxPort->clear();
		foreach(QSerialPortInfo portinfo, portList)
			ui->cboxPort->addItem(portinfo.portName());
	}
}
