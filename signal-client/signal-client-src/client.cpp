#include <QtNetwork>
#include <QIODevice>

#include "client.h"

Client::Client(QObject *parent) : QObject(parent), tcpSocket(new QTcpSocket(this))
{
    QVector<QString> hosts;

    // Find name of this (client) machine
    QString hostName = QHostInfo::localHostName();
    if(!hostName.isEmpty()){
        QString domainName = QHostInfo::localDomainName();
        if(!domainName.isEmpty())
             hosts.append(QString(hostName + "." + domainName));
    }

    if(hostName != QLatin1String("localhost"))
        hosts.append(QString("localhost"));


    // Find IP address of this machine
    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // Add non-localhost addresses
    for (const QHostAddress &entry : ipAddressesList){
        if (!entry.isLoopback())
            hosts.append(entry.toString());
    }

    // Add localhost addresses
    for (const QHostAddress &entry : ipAddressesList){
        if (entry.isLoopback())
            hosts.append(entry.toString());
    }

    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_5_15);


    // write function that send signal to slot requestNewSignal
    // connect(, this, &Client::requestNewSignal());
    connect(tcpSocket, &QIODevice::readyRead, this, &Client::readSignal);
    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &Client::displayError);
}

void Client::requestNewSignal(){
    tcpSocket->abort();
    // write taking host from the list of hosts
    // tcpSocket->connectToHost()
}

void Client::readSingal(){
    in.startTransaction();

    // Write getting new signal
    //    QVector<QPair>nextSignal;
    //    in >> nextSignal;

    if(!in.commitTransaction())
        return;

    // end this function
}

void Client::displayError(){
    // finish this function
}
