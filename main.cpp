#include <QGuiApplication>
#include <QFont>
#include <QQmlApplicationEngine>

int main(int argc, char** argv) {
	QGuiApplication app(argc, argv);
	QGuiApplication::setFont(QFont("Noto Sans", 10));
	QQmlApplicationEngine engine {};
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
	engine.load("qrc:/gameModule/qml/Main.qml");
	return QGuiApplication::exec();
}
