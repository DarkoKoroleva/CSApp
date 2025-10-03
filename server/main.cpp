#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Server server;
    if (!server.startServer(12345))
        return -1;

    return app.exec();
}
