#include <QtNetwork>

#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent){
    initServer();
}

void Server::initServer(){
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen()){
        qCritical() << QString("Unable to start the server: %1.").arg(tcpServer->errorString());
        return;
    }

    QString ipAddress;
    const QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for (const QHostAddress &address: ipAddressList) {
        if (address != QHostAddress::LocalHost && address.toIPv4Address()) {
            ipAddress = address.toString();
        }
    }

    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qInfo() << QString("The server is running on\n\nIP: %1\nport: %2\n\n"
                       "Run client app now.").arg(ipAddress).arg(tcpServer->serverPort());
}


void Server::sendSignal(){

}

void Server::generateSignal(){
    int n_dots = 100;
    // Initialize 2d array (x, y) values of y = sin(x)
    QVector<QVector<double>> array(n_dots, QVector<double>(n_dots, 0.0));
    for(int y = 0; y < n_dots; y++){
    }
}
