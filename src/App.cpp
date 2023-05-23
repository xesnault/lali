#include "App.h"

App::App(QObject *parent) : QObject(parent)
{
	QDir().mkdir(dataPath);
	localListRepository = std::make_unique<LocalListRepository>(dataPath);
}

void App::loadLists() {
	animeLists = localListRepository->getAll();
	emit animeListsChanged();
}

void App::searchAnimes(QString title) {
	aniList.SearchAnimes(title, [=](QList<Anime> results) {
			searchResults = AnimeList("Search results", results);
			emit searchResultChanged();
		}, [=](){
			qDebug() << "FAILED TO FETCH ANIMES";
		});
}

QList<AnimeList> App::getLists() const {
	return animeLists;
}

AnimeList App::getSearchResults() const {
	return searchResults;
}

void App::addAnimeToList(Anime anime, QString listName) {
	auto list = std::find_if(animeLists.begin(), animeLists.end(), [=] (const AnimeList& list) {return list.getName() == listName;});
	list->add(anime);
	localListRepository->save(animeLists);
	refreshImagesCache(*list);
	emit animeListsChanged();
};

void App::moveAnimeToList(Anime anime, QString fromListName, QString toListName) {
	auto fromList = std::find_if(animeLists.begin(), animeLists.end(), [=] (const AnimeList& list) {return list.getName() == fromListName;});
	auto toList = std::find_if(animeLists.begin(), animeLists.end(), [=] (const AnimeList& list) {return list.getName() == toListName;});
	toList->add(anime);
	fromList->removeByName(anime.getTitle());
	localListRepository->save(animeLists);
	emit animeListsChanged();
};

void App::removeAnimeFromList(Anime anime, QString listName) {
	auto list = std::find_if(animeLists.begin(), animeLists.end(), [=] (const AnimeList& list) {return list.getName() == listName;});
	list->removeByName(anime.getTitle());
	localListRepository->save(animeLists);
	emit animeListsChanged();
};

void App::createList(QString listName) {
	auto newList = AnimeList(listName);
	animeLists.append(newList);
	localListRepository->save(animeLists);
	emit animeListsChanged();
}

void App::deleteList(QString listName) {
	animeLists.removeIf([&](AnimeList list) {
		return list.getName() == listName;
	});
	localListRepository->save(animeLists);
	emit animeListsChanged();
}

void App::importFromAnilist(const QString& userName, const QString& listName, const QString& targetListName) {
	importStatus = Status::InProgress;
	emit importStatusChanged();
	aniList.FetchUserLists(userName, [=](QList<AnimeList> results) {
			importStatus = Status::Completed;
			emit importStatusChanged();
			qDebug() << "SUCCESS";
			auto list = std::find_if(results.begin(), results.end(), [=] (const AnimeList& list) {return list.getName() == listName;});
			if (list != results.end()) {
				qDebug() << "Found list " << listName << " on user " << userName;
				AnimeList t(targetListName, list->getAnimes());
				animeLists.append(t);
				localListRepository->save(animeLists);
				emit animeListsChanged();
			}
		}, [=](){
			importStatus = Status::Error;
			emit importStatusChanged();
			qDebug() << "FAILED";
		});
};

QString formatName(QString name) {
	for (auto& character : name) {
		if (!character.isDigit() && !character.isLetter() && !character.isSpace())
			character = '_';
	}
	return name;
}

void App::refreshImagesCache(AnimeList animeList) {
	/*if (!selectedList) {
		return;
	}*/
	for (auto& anime : animeList.getAnimes()) {
		const auto path = cachePath + "/" + formatName(anime.title);
		if (QFile::exists(path)) {
			// qDebug() << path << "already exists";
			continue ;
		}
		QNetworkRequest coverImageRequest;
		coverImageRequest.setUrl(QUrl(anime.getCoverImageUrl()));
		QNetworkReply* coverImageReply = http.get(coverImageRequest);
		connect(coverImageReply, &QNetworkReply::finished, this, [=] {
			if (coverImageReply->error()) {
				QString answer = coverImageReply->readAll();
				std::cout << "Error fetching image!" << std::endl;
				std::cout << coverImageReply->errorString().toStdString() << std::endl;
				std::cout << coverImageReply->error() << std::endl;
				std::cout << answer.toStdString() << std::endl;
				return;
			}
			
			QByteArray coverImageData = coverImageReply->readAll();
			QFile file(path);
			if (file.open(QIODevice::WriteOnly)) {
				file.write(coverImageData);
				file.flush();
				file.close();
			}
		});
	}
}

void App::updateList(QString listName, AnimeList listWithUpdate) {
	auto list = std::find_if(animeLists.begin(), animeLists.end(), [=] (const AnimeList& list) {return list.getName() == listName;});
	if (list == animeLists.end()) {
		return ;
	}
	list->setName(listWithUpdate.getName());
	emit animeListsChanged();
	localListRepository->save(animeLists);
}
