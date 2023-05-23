#ifndef APP_H
#define APP_H

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>
#include <QVariant>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <iostream>
#include <memory>
#include <qqml.h>

#include "AniList.h"
#include "AnimeList.h"
#include "LocalListRepository.h"
#include "Status.h"

class App : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QList<AnimeList> animeLists READ getLists NOTIFY animeListsChanged);
	Q_PROPERTY(AnimeList searchResults READ getSearchResults NOTIFY searchResultChanged);
	Q_PROPERTY(Status importStatus MEMBER importStatus NOTIFY importStatusChanged);
	QML_ELEMENT
	
public:
	explicit App(QObject *parent = nullptr);
	
	Q_INVOKABLE void loadLists();
	Q_INVOKABLE void createList(QString listName);
	Q_INVOKABLE void deleteList(QString listName);
	Q_INVOKABLE void updateList(QString listName, AnimeList listWithUpdate);
	
	Q_INVOKABLE void addAnimeToList(Anime anime, QString listName);
	Q_INVOKABLE void moveAnimeToList(Anime anime, QString fromListName, QString toListName);
	Q_INVOKABLE void removeAnimeFromList(Anime anime, QString listName);
	
	Q_INVOKABLE void searchAnimes(QString title);
	Q_INVOKABLE void refreshImagesCache(AnimeList animeList);
	
	Q_INVOKABLE void importFromAnilist(const QString &userName,
									   const QString &listName,
									   const QString &targetListName);
	
	QList<AnimeList> getLists() const;
	AnimeList getSearchResults() const;
	
private:
	std::unique_ptr<LocalListRepository> localListRepository;
	AniList aniList;
	
	Status importStatus;
	
	AnimeList searchResults{"Search resulsts"};
	
	QList<AnimeList> animeLists;
	
	QNetworkAccessManager http;
	
	QString dataPath = QDir::homePath() + "/.local/share/lali";
	QString cachePath = QDir::homePath() + "/.cache/lali";
	
signals:
	void animeListsChanged();
	void searchResultChanged();
	void importStatusChanged();
};

#endif // APP_H
