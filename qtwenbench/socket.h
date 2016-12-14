#pragma once

#include <QTcpSocket>


QVector<QTcpSocket*> CreatSocketList(QString domain, quint16 port, quint32 threads) {
	QVector<QTcpSocket*> vpSocket;
	for (quint32 i = 0; i < threads; i++) {
		
		QTcpSocket *socket = new QTcpSocket();
		socket->connectToHost(domain, port);
		if (!socket->waitForConnected()) {
			qDebug() << "connected erroe.";
		}
		
		vpSocket.append(socket);
	}

	return vpSocket;
}