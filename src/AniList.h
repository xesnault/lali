#ifndef ANILIST_H
#define ANILIST_H
#include <QObject>
#include <QString>
#include <QByteArray>
#include <QVector>
#include <QList>
#include <QMap>
#include <QtNetwork>
#include <functional>
#include <iostream>
#include <QJsonObject>

// #include "Settings.h"
#include "Anime.h"
#include "AnimeList.h"

// Please keep the whitespaces with a REAL SPACE, NOT TAB for graphQL queries for the moment
#define GRAPHQL_ANILIST_MEDIA_CONTENT "\
    id\
    title {\
        romaji\
    }\
    description\
    episodes\
    genres\
    status\
    startDate {\
        year\
        month\
        day\
    }\
    endDate {\
        year\
        month\
        day\
    }\
    coverImage {\
        extraLarge\
    }"

class AniList : public QObject
{
	Q_OBJECT
public:
	explicit AniList(QObject *parent = nullptr);
	
	void GraphQLQuery(QString body_, std::function<void(QJsonObject)> onSuccess, std::function<void()> onFailure);
	
	void SearchAnimes(const QString& title, std::function<void(QList<Anime>)> onSuccess, std::function<void()> onFailure);
	void FetchUserLists(const QString userName, std::function<void(QList<AnimeList>)> onSuccess, std::function<void()> onFailure);
	
signals:
	
private:
	
	QNetworkAccessManager http;
	
};

#endif // ANILIST_H
