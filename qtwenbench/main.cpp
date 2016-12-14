#include <QtCore/QCoreApplication>
#include <QDebug>
#include <QSettings>
#include <QTcpSocket>
#include <QHostAddress>
#include <QUrl>

#include "socket.h"

void build_request(QByteArray &request, QString host, QString path, int type);

int main(int argc, char *argv[])
{

	QCoreApplication a(argc, argv);

	enum Method_Type
	{
		METHOD_GET,
		METHOD_HEARD,
	};
	
	/* 读取配置文件 */
	QSettings *configs = new QSettings("config.ini", QSettings::IniFormat);

	QString url = configs->value("config/url").toString();
	QString clients = configs->value("config/clients").toString();
	quint16 method = configs->value("config/method").toInt();
	quint16 port = configs->value("config/port").toInt();
	qDebug() << url << clients.toInt()<<port;
	qDebug() << method <<"method";
	delete configs;

	/* 解析url */
	QUrl urls(url);
	if (urls.isEmpty())
	{
		qDebug() << "url is empty.";
	}
	QString host = urls.host();
	QString path = urls.path();

	/* 确认请求类型构造请求 */
	QByteArray request("");
	switch (method)
	{
	case METHOD_GET:
		build_request(request, host, path, METHOD_GET);
		break;
	case METHOD_HEARD:
		build_request(request, host, path, METHOD_GET);
		break;
	default:
		break;
	}

	qDebug() << request;  //rquest 构造完成

	/* 建立连接 */

	QVector<QTcpSocket*> vpSockets = CreatSocketList(host, port, clients.toInt());

	/* 发送数据 */
	for (size_t i = 0; i < vpSockets.size(); i++)
	{
		qDebug() << vpSockets[i]->peerAddress().toString();
		qDebug() << "success write " <<vpSockets[i]->write(request);
		vpSockets[i]->waitForDisconnected();
	}


	return a.exec();
}


void build_request(QByteArray &request, QString host, QString path, int type) {
	
	switch (type)
	{
	case 0:
		request.append("GET " + path + " HTTP/1.1\r\n");
		request.append("Host: " + host + "\r\n");
		request.append("User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/50.0.2661.102 Safari/537.36\r\n");
		request.append("Connection: close\r\n");
		request.append("\r\n");
		/* add empty line at end */
		break;
	default:
		break;
	}

	return ;
}