#include <QObject>
#include <QString>
#include <QDebug>
#include <iostream>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <qqml.h>

#include "LocalListRepository.h"

QList<AnimeList> LocalListRepository::getAll() {
	if (cachedLists.empty()) {
		cachedLists = loadLists();
	}
	return cachedLists;
}

void LocalListRepository::save(QList<AnimeList> lists) {
	cachedLists = lists;
	
	QJsonArray listsJson;
	
	for (const AnimeList& list : lists) {
		
		QJsonArray animesJson;
		
		for (const auto& anime : list.animes) {
			QJsonObject animeJson;
			
			animeJson["title"] = anime.getTitle();
			animeJson["description"] = anime.GetDescription();
			animeJson["coverImageUrl"] = anime.getCoverImageUrl();
			animeJson["episodes"] = anime.GetEpisodes();
			animeJson["status"] = anime.GetStatus();
			
			QJsonArray genresJson;
			for (const QString& genreName : anime.GetGenres()) {
				genresJson.append(genreName);
			}
			
			QJsonObject startDate;
			startDate["year"] = anime.GetStartYear();
			startDate["month"] = anime.GetStartMonth();
			startDate["day"] = anime.GetStartDay();
			
			QJsonObject endDate;
			endDate["year"] = anime.GetEndYear();
			endDate["month"] = anime.GetEndMonth();
			endDate["day"] = anime.GetEndDay();
			
			animeJson["genres"] = genresJson;
			animeJson["startDate"] = startDate;
			animeJson["endDate"] = endDate;
			
			animesJson.append(animeJson);
		}
		
		QJsonObject listJson;
		
		listJson["name"] = list.name;
		listJson["animes"] = animesJson;
		
		listsJson.append(listJson);
	}
	
	QJsonObject saveJson;
	saveJson.insert("lists", listsJson);
	
	QFile saveFile(dataPath + "/save.json");
	
	if (!saveFile.open(QIODevice::WriteOnly)) {
		qWarning("Couldn't save the lists");
		return ;
	}
	
	saveFile.write(QJsonDocument(saveJson).toJson());
	saveFile.close();
}

QList<AnimeList> LocalListRepository::loadLists() {
	
	QFile loadFile(dataPath + "/save.json");
	
	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning() << "Couldn't find existing save at " << dataPath + "/save.json";
	}
	
	QByteArray loadData = loadFile.readAll();
	QJsonObject json = QJsonDocument::fromJson(loadData).object();
	loadFile.close();
	
	QList<AnimeList> lists;
	
	auto listsJson = json["lists"].toArray();
	for (auto listJson : listsJson) {
		AnimeList list(listJson.toObject()["name"].toString());
		auto animesJson = listJson.toObject()["animes"].toArray();
		for (int i = 0; i < animesJson.count(); ++i) {
			Anime anime ;
			anime.SetTitle(animesJson[i].toObject()["title"].toString());
			anime.SetDescription(animesJson[i].toObject()["description"].toString());
			anime.SetCoverImageByUrl(animesJson[i].toObject()["coverImageUrl"].toString());
			anime.SetStatus(animesJson[i].toObject()["status"].toString());
			anime.SetEpisodes(animesJson[i].toObject()["episodes"].toInt());
			
			auto genresJson = animesJson[i].toObject()["genres"].toArray();
			for (auto genreJson : genresJson) {
				anime.AddGenre(genreJson.toString());
			}
			
			anime.SetStartYear(animesJson[i].toObject()["startDate"].toObject()["year"].toInt());
			anime.SetStartMonth(animesJson[i].toObject()["startDate"].toObject()["month"].toInt());
			anime.SetStartDay(animesJson[i].toObject()["startDate"].toObject()["day"].toInt());
			
			anime.SetEndYear(animesJson[i].toObject()["endDate"].toObject()["year"].toInt());
			anime.SetEndMonth(animesJson[i].toObject()["endDate"].toObject()["month"].toInt());
			anime.SetEndDay(animesJson[i].toObject()["endDate"].toObject()["day"].toInt());
			
			list.add(anime);
		}
		lists.push_back(list);
	}
	
	if (lists.isEmpty())
		lists.push_back(AnimeList("Watched"));
	return lists;
}
