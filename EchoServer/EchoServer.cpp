#include "EchoServer.h"

#define DEFAULT_PORT 1234

EchoServer::EchoServer(quint16 port, QObject *parent) : QObject(parent)
{
  Q_UNUSED(parent);

  m_server = new QTcpServer(this);
  m_port = port;
}

EchoServer::EchoServer(QObject *parent) : QObject(parent)
{
  Q_UNUSED(parent);

  m_server = new QTcpServer(this);
  m_port = DEFAULT_PORT;
}

EchoServer::~EchoServer()
{
//  qDeleteAll(m_sockets);
  delete m_server;
}

bool EchoServer::isRunning() const
{
  return m_server->isListening();
}

quint16 EchoServer::getPort() const
{
  return m_port;
}

void EchoServer::start()
{
  connect(m_server, SIGNAL(newConnection()), this, SLOT(newClient()));

  if ( !m_server->listen(QHostAddress::Any, m_port) )
    qDebug() << m_server->errorString();
  else
    qDebug() << "server is running...";
}

void EchoServer::stop()
{

}

void EchoServer::newClient()
{

}

