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

#include "LocalListRepository.h"
#include "AniList.h"
#include "AnimeList.h"

class App : public QObject
{
	Q_OBJECT
    Q_PROPERTY(QList<AnimeList> animeLists READ getLists NOTIFY animeListsChanged);
	Q_PROPERTY(AnimeList searchResults READ getSearchResults NOTIFY searchResultChanged);
	QML_ELEMENT
	
public:
	explicit App(QObject *parent = nullptr);
	
	QStringList getListsNames();
    
	Q_INVOKABLE void loadLists();
    Q_INVOKABLE void createList(QString listName);
    Q_INVOKABLE void deleteList(QString listName);
    Q_INVOKABLE void updateList(QString listName, AnimeList listWithUpdate);
    
	Q_INVOKABLE void addAnimeToList(Anime anime, QString listName);
	Q_INVOKABLE void moveAnimeToList(Anime anime, QString fromListName, QString toListName);
	Q_INVOKABLE void removeAnimeFromList(Anime anime, QString listName);
    
    Q_INVOKABLE void searchAnimes(QString title);
    Q_INVOKABLE void importFromAnilist(const QString& userName, const QString& listName, const QString& targetListName);
	Q_INVOKABLE void refreshImagesCache(AnimeList animeList);
    
    QList<AnimeList> getLists() const;
    AnimeList getSearchResults() const;
	
private:
	
    std::unique_ptr<LocalListRepository> localListRepository;
	AniList aniList;
    
    AnimeList searchResults{"Search resulsts"};
	
	QList<AnimeList> animeLists;
	
	QNetworkAccessManager http;
	
	QString dataPath = QDir::homePath() + "/.local/share/lali";
	QString cachePath = QDir::homePath() + "/.cache/lali";
	
signals:
	void animeListsChanged();
	void searchResultChanged();
};

#endif // APP_H
