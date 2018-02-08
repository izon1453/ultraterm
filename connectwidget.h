#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class ConnectWidget;
}

class ConnectWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ConnectWidget(QWidget *parent = 0);
	~ConnectWidget();

	QString getPortName();
	qint32 getBaudRate();
	QSerialPort::DataBits getDataBits();
	QSerialPort::Parity getParity();

private:
	Ui::ConnectWidget *ui;

	QTimer *renewTimer;
	QList<QSerialPortInfo> portList;

public slots:
	void renewPorts();

};

#endif // CONNECTWIDGET_H
