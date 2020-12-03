#include <public/mainwindow.h>
#include <QApplication>

#include <Poco/Data/Session.h>
#include <Poco/Data/SQLite/Connector.h>

#include <public/DB/Manager.h>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::UnicodeConverter;

int main(int argc, char *argv[])
{
    Poco::Data::SQLite::Connector::registerConnector();
    Session session("SQLite", "QuesterDB.db");
    Utils::session = &session;
    DB::ManagerTest::CreateContext();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
