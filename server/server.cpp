#include <QTcpSocket>
#include <QDebug>
#include "server.h"

Server::Server(QObject* parent) : QObject(parent), m_server(new QTcpServer(this))
{
    connect(m_server, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

bool Server::startServer(const uint64_t port)
{
    if (!m_server->listen(QHostAddress::Any, port)) {
        qWarning() << "Server::startServer: Failed to start listening on port " << port;
        return false;
    }
    qDebug() << "Server::startServer: Listening on port " << port;
    return true;
}

void Server::onNewConnection()
{
    while (m_server->hasPendingConnections())
    {
        auto clientSocket = m_server->nextPendingConnection();
        m_clients[clientSocket] = QByteArray();

        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onReadyRead);

        qDebug() << "New client: " << clientSocket->peerAddress().toString() << ":" << clientSocket->peerPort();
    }
}

void Server::onDisconnected()
{
    auto clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket)
        return;

    qDebug() << "Client disconnected: " << clientSocket->peerAddress().toString() << ":" << clientSocket->peerPort();
    m_clients.remove(clientSocket);
    clientSocket->deleteLater();
}

void Server::onReadyRead()
{
    auto clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket)
        return;

    QByteArray &buffer = m_clients[clientSocket];
    buffer.append(clientSocket->readAll());

    while (true)
    {
        // parse client answer
    }
}
