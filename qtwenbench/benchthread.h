#pragma once

#include <QThread>

class benchthread : public QThread
{
	Q_OBJECT

public:
	benchthread(QObject *parent);
	~benchthread();
	//void run();
};
