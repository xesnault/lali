#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>
#include <QQmlContext>
#include "App.h"

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
	
	qmlRegisterType<AnimeList>("Lali.Types", 1, 0, "AnimeList");
	qmlRegisterType<Anime>("Lali.Types", 1, 0, "Anime");
	qmlRegisterType<StatusClass>("Lali.Types", 1, 0, "Status");
	
	QQmlApplicationEngine engine;
	App *backend = new App();
	engine.rootContext()->setContextProperty("_app", backend);
	const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		}, Qt::QueuedConnection);
	engine.load(url);
	
	return app.exec();
}
