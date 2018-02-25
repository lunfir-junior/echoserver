#include "EchoServer.h"

#define DEFAULT_PORT 1234

EchoServer::EchoServer(quint16 port, QObject *parent) : QObject(parent)
{
  Q_UNUSED(parent);

  m_server = new QTcpServer(this);
  m_port = port;

  connect(m_server, &QTcpServer::newConnection, this, &EchoServer::slotNewClient);
  connect(m_server, &QTcpServer::destroyed, this, &EchoServer::destroyed);
}

EchoServer::EchoServer(QObject *parent) : QObject(parent)
{
  Q_UNUSED(parent);

  m_server = new QTcpServer(this);
  m_port = DEFAULT_PORT;

  connect(m_server, &QTcpServer::newConnection, this, &EchoServer::slotNewClient);
  connect(m_server, &QTcpServer::destroyed, this, &EchoServer::destroyed);
}

EchoServer::~EchoServer()
{
  this->stop();
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
  if ( !m_server->listen(QHostAddress::Any, m_port) )
    qDebug() << m_server->errorString();
  else
    qDebug() << "server is running...";
}

void EchoServer::stop()
{
  m_server->close();

  foreach ( int i, m_clients.keys() ) {
    m_clients[i]->close();
  }
  qDeleteAll(m_clients.begin(), m_clients.end());
}

void EchoServer::slotNewClient()
{
  qDebug() << "new client!!!";
  QTcpSocket* clientSocket = m_server->nextPendingConnection();
  uint descriptor = clientSocket->socketDescriptor();
  m_clients.insert(descriptor, clientSocket);

  qDebug() << m_clients;

  connect( clientSocket, &QTcpSocket::readyRead, this, &EchoServer::slotProcessData );
}

void EchoServer::slotProcessData()
{
  QTcpSocket *clientSocket = (QTcpSocket*) sender();
  uint descriptor = clientSocket->socketDescriptor();

  QByteArray clientData = clientSocket->readAll();

  qDebug().noquote() << "client data: " << clientData;

  if ( clientData.toStdString() == "disconnect\r\n" ) {
    clientSocket->close();
    m_clients.remove(descriptor);
    clientSocket->deleteLater();
  } else {
    clientSocket->write(clientData);
  }
}

