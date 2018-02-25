#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkSession>

class EchoServer : public QObject
{
    Q_OBJECT
  public:
    explicit EchoServer(quint16 port, QObject *parent = nullptr);
    explicit EchoServer(QObject *parent = nullptr);

    virtual ~EchoServer();

    bool isRunning() const;
    quint16 getPort() const;
    void start();
    void stop();

  private:
    QTcpServer *m_server;
    quint16 m_port;
    QMap<uint, QTcpSocket*> m_clients;

  signals:

  public slots:
    void slotNewClient();
    void slotProcessData();

  Q_SIGNALS:
    void destroyed();
};

#endif // ECHOSERVER_H
