#include <QCoreApplication>
#include <EchoServer.h>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  EchoServer server;
  QObject::connect(&server, &EchoServer::destroyed, &a, &QCoreApplication::quit);

  server.start();

  return a.exec();
}
