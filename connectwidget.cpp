#include "connectwidget.h"
#include "ui_connectwidget.h"

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

ConnectWidget::ConnectWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ConnectWidget)
{
	ui->setupUi(this);

	renewTimer = new QTimer(this);
	connect(renewTimer, SIGNAL(timeout()), this, SLOT(renewPorts()));
	renewTimer->start(1000);

	ui->cboxBits->addItem("8", QSerialPort::Data8);
	ui->cboxBits->addItem("7", QSerialPort::Data7);
	ui->cboxBits->addItem("6", QSerialPort::Data6);
	ui->cboxBits->addItem("5", QSerialPort::Data5);

	ui->cboxParity->addItem("None", QSerialPort::NoParity);
	ui->cboxParity->addItem("Even", QSerialPort::EvenParity);
	ui->cboxParity->addItem("Odd", QSerialPort::OddParity);
	ui->cboxParity->addItem("Space", QSerialPort::SpaceParity);
	ui->cboxParity->addItem("Mark", QSerialPort::MarkParity);

	ui->cboxStopbits->addItem("1", 1);
	ui->cboxStopbits->addItem("2", 2);

	renewPorts();
}

ConnectWidget::~ConnectWidget()
{
	delete renewTimer;

	delete ui;
}

/**
 * @brief ConnectWidget::getPortName Геттер выбранного пользователем последовательного порта.
 * @return Возвращает имя выбранного порта.
 */
QString ConnectWidget::getPortName()
{
	return ui->cboxPort->itemText(ui->cboxPort->currentIndex());
}

/**
 * @brief ConnectWidget::getBaudRate Геттер выбранного пользователем бодрейта.
 * @return Возвращает значение выбранного бодрейта.
 */
qint32 ConnectWidget::getBaudRate()
{
	qint32 tmpBaudRate = ui->cboxBaudrate->currentText().toInt();
	if(tmpBaudRate < 0)
	{
		tmpBaudRate = 0;
		ui->cboxBaudrate->setCurrentText("0");
	}
	return (qint32)tmpBaudRate;
}

/**
 * @brief ConnectWidget::getDataBits Геттер выбранного пользователем количества бит данных в посылке.
 * @return Возвращает выбранное в виджете оличество бит данных.
 */
QSerialPort::DataBits ConnectWidget::getDataBits()
{
	QVariant tmp = ui->cboxBits->itemData(ui->cboxBits->currentIndex());
	return tmp.value<QSerialPort::DataBits>();
}

/**
 * @brief ConnectWidget::getParity Геттер выбранной пользователем четности.
 * @return Возвращает выбранный в виджете вариант расчета четности.
 */
QSerialPort::Parity ConnectWidget::getParity()
{
	QVariant tmp = ui->cboxParity->itemData(ui->cboxParity->currentIndex());
	return tmp.value<QSerialPort::Parity>();
}

/**
 * @brief ConnectWidget::renewPorts Обновляет список com-портов в виджете при необходимости.
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
