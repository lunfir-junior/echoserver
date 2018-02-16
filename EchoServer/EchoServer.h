#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <QObject>
#include <QTcpServer>

class EchoServer : public QObject
{
    Q_OBJECT
  public:
    explicit EchoServer(int port, QObject *parent = nullptr);
    explicit EchoServer(QObject *parent = nullptr);
    EchoServer(const EchoServer &other); // if needed

    virtual ~EchoServer();

    bool isRunning() const;
    quint16 getPort() const;
    void start();
    void stop();

  private:
    QTcpServer *m_server;
    QList<QTcpSocket*> m_sockets;

  signals:

  public slots:
};

#endif // ECHOSERVER_H
