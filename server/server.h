#pragma once
#include <QObject>
#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    bool startServer(const uint64_t port);

private slots:
    void onNewConnection();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpServer *m_server;
    QMap<QTcpSocket*, QByteArray> m_clients;
};
