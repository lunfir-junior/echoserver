#include <QCoreApplication>
#include <EchoServer.h>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  EchoServer server;

  qDebug() << "before start: " << server.isRunning();

  server.start();

  qDebug() << "after start: " << server.isRunning();

  return a.exec();
}
