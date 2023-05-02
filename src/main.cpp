#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include <QQmlContext>
#include "AnimeQML.h"
#include "ListQML.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
	
	QGuiApplication app(argc, argv);
	
	QTranslator translator;
	const QStringList uiLanguages = QLocale::system().uiLanguages();
	for (const QString &locale : uiLanguages) {
		const QString baseName = "lali_" + QLocale(locale).name();
		if (translator.load(":/i18n/" + baseName)) {
			app.installTranslator(&translator);
			break;
		}
	}
	
	// qmlRegisterType<BackEnd>("Lali.backend", 1, 0, "BackEnd");
	qmlRegisterType<AnimeQML>("Lali.Types", 1, 0, "AnimeQML");
	qmlRegisterType<ListQML>("Lali.Types", 1, 0, "ListQML");
	
	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);
	
	return app.exec();
}
