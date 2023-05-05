#ifndef APP_H
#define APP_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QList>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <qqml.h>
#include <memory>

#include "ListRepository.h"
#include "AniList.h"
#include "ListQML.h"


class App : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QStringList listsNames READ getListsNames NOTIFY listsNamesChanged);
	Q_PROPERTY(ListQML* selectedList MEMBER selectedList NOTIFY selectedListChanged);
	Q_PROPERTY(ListQML* searchResults MEMBER searchResults NOTIFY searchResultChanged);
	QML_ELEMENT
	
public:
	explicit App(QObject *parent = nullptr);
	
	// State
	
	ListQML* selectedList = nullptr;
	ListQML* searchResults = nullptr;
	
	QStringList getListsNames();
	
	Q_INVOKABLE void searchAnimes(QString title);
	Q_INVOKABLE void importFromAnilist(const QString& userName, const QString& listName, const QString& targetListName);
	
	Q_INVOKABLE void loadLists();
	Q_INVOKABLE void selectListByName(QString name);
	Q_INVOKABLE void addAnimeToList(AnimeQML* anime, QString listName);
	Q_INVOKABLE void moveAnimeToList(AnimeQML* anime, QString fromListName, QString toListName);
	Q_INVOKABLE void removeAnimeFromList(AnimeQML* anime, QString listName);
	Q_INVOKABLE void createList(QString listName);
	Q_INVOKABLE void deleteList(QString listName);
    Q_INVOKABLE void updateList(QString listName, ListQML* listQML);
	
	/*void saveLists();*/
	
private:
	
	void refreshImagesCache();
	
	std::unique_ptr<ListRepository> listRepository;
	AniList aniList;
	
	// State
	QList<List> lists;
	
	QNetworkAccessManager http;
	
	QString dataPath = QDir::homePath() + "/.local/share/lali";
	QString cachePath = QDir::homePath() + "/.cache/lali";
	
signals:
	void listsChanged();
	void searchResultChanged();
	void listsNamesChanged();
	void selectedListChanged();
};

#endif // APP_H
