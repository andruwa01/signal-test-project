#include <QCoreApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    std::cout << "hello there" << std::endl;
    app.exec();
}
