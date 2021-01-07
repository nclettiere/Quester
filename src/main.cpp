#include <public/mainwindow.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QTextStream>

#include <Poco/Data/Session.h>
#include <Poco/Data/SQLite/Connector.h>

#include <public/Utils.h>
#include <public/DB/Manager.h>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::UnicodeConverter;

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //
    //Poco::Data::SQLite::Connector::registerConnector();
    //Session session("SQLite", "QuesterDB.db");
    //Utils::session = &session;
    //Utils::Context = QCoreApplication::applicationDirPath().toStdString();
    //DB::Manager::CreateContext();
    //
    //MainWindow mainWindow;
    //
    //mainWindow.show();

    QGuiApplication a(argc, argv);

    QCoreApplication::addLibraryPath("./");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return a.exec();
}
