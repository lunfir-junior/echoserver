#include "EchoServer.h"

EchoServer::EchoServer(int port, QObject *parent) : QObject(parent)
{
  Q_UNUSED(parent);

}

EchoServer::EchoServer(QObject *parent) : QObject(parent)
{
  Q_UNUSED(parent);

}

EchoServer::EchoServer(const EchoServer &other)
{

}

EchoServer::~EchoServer()
{
  qDeleteAll(m_sockets);
  delete m_server;
}

bool EchoServer::isRunning() const
{
  return m_server->isListening();
}

quint16 EchoServer::getPort() const
{
  return m_server->serverPort();
}

void EchoServer::start()
{

}

void EchoServer::stop()
{

}

