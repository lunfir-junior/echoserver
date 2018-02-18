#include <QCoreApplication>
#include <EchoServer.h>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  EchoServer server;

  return a.exec();
}
