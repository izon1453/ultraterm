#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>

class SerialPort : public QSerialPort
{
	Q_OBJECT

public:
	SerialPort();

public slots:
//	void connOpen();
//	void connClose();

};

#endif // SERIALPORT_H
