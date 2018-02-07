#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include <QTimer>
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
	quint32 getBaudRate();

private:
	Ui::ConnectWidget *ui;

	QTimer *renewTimer;
	QList<QSerialPortInfo> portList;

public slots:
	void renewPorts();

};

#endif // CONNECTWIDGET_H
