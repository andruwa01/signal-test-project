#include <QCoreApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app_server(argc, argv);
    Server server;
    app_server.exec();
}
