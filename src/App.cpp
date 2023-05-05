#include "App.h"

App::App(QObject *parent) : QObject(parent)
{
	QDir().mkdir(dataPath);
	listRepository = std::make_unique<ListRepository>(dataPath);
}

QStringList App::getListsNames() {
	QStringList names;
	for (const auto& list : lists) {
		names.push_back(list.getName());
	}
	return names;
}

void App::searchAnimes(QString title) {
	aniList.SearchAnimes(title, [=](QList<Anime> results) {
		searchResults = new ListQML(List("Search results", results));
		emit searchResultChanged();
	}, [=](){
		qDebug() << "FAILED TO FETCH ANIMES";
	});
}

void App::loadLists() {
	lists = listRepository->getAll();
	selectedList = new ListQML(lists[0]);
	emit listsNamesChanged();
	emit selectedListChanged();
}

void App::selectListByName(QString name) {
	const auto& list = std::find_if(lists.begin(), lists.end(), [=] (const List& list) {return list.getName() == name;});
	selectedList = new ListQML(*list);
	refreshImagesCache();
	emit selectedListChanged();
}

void App::addAnimeToList(AnimeQML* anime, QString listName) {
	auto list = std::find_if(lists.begin(), lists.end(), [=] (const List& list) {return list.getName() == listName;});
	list->add(anime->getAnime());
	listRepository->save(lists);
	selectListByName(selectedList->getName());
	emit selectedListChanged();
};

void App::moveAnimeToList(AnimeQML* anime, QString fromListName, QString toListName) {
	auto fromList = std::find_if(lists.begin(), lists.end(), [=] (const List& list) {return list.getName() == fromListName;});
	auto toList = std::find_if(lists.begin(), lists.end(), [=] (const List& list) {return list.getName() == toListName;});
	toList->add(anime->getAnime());
	fromList->removeByName(anime->getAnime().getTitle());
	listRepository->save(lists);
	selectListByName(selectedList->getName());
	emit selectedListChanged();
};

void App::removeAnimeFromList(AnimeQML* anime, QString listName) {
	auto list = std::find_if(lists.begin(), lists.end(), [=] (const List& list) {return list.getName() == listName;});
	list->removeByName(anime->getAnime().getTitle());
	listRepository->save(lists);
	selectListByName(selectedList->getName());
	emit selectedListChanged();
};

void App::createList(QString listName) {
	auto newList = List(listName);
	lists.append(newList);
	emit listsNamesChanged();
	listRepository->save(lists);
}

void App::deleteList(QString listName) {
	lists.removeIf([&](List list) {
		return list.getName() == listName;
	});
	emit listsNamesChanged();
	listRepository->save(lists);
    if (!lists.empty()) {
        selectListByName(lists[0].getName());
    }
}

void App::importFromAnilist(const QString& userName, const QString& listName, const QString& targetListName) {
	aniList.FetchUserLists(userName, [=](QList<List> results) {
		qDebug() << "SUCCESS";
		auto list = std::find_if(results.begin(), results.end(), [=] (const List& list) {return list.getName() == listName;});
		if (list != results.end()) {
			qDebug() << "Found list " << listName << " on user " << userName;
			auto t = List(targetListName, list->getAnimes());
			lists.append(t);
			emit listsNamesChanged();
			listRepository->save(lists);
		}
	}, [=](){
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

void App::refreshImagesCache() {
	if (!selectedList) {
		return;
	}
	for (auto anime : selectedList->getAnimes()) {
		const auto path = cachePath + "/" + formatName(anime->getTitle());
		if (QFile::exists(path)) {
			// qDebug() << path << "already exists";
			continue ;
		}
		QNetworkRequest coverImageRequest;
		coverImageRequest.setUrl(QUrl(anime->getImageUrl()));
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

void App::updateList(QString listName, ListQML* listQML) {
    auto list = std::find_if(lists.begin(), lists.end(), [=] (const List& list) {return list.getName() == listName;});
    if (list == lists.end()) {
        return ;
    }
    list->setName(listQML->getName());
    emit listsNamesChanged();
    listRepository->save(lists);
}
