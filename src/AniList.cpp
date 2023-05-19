#include <QJsonDocument>
#include "AniList.h"

AniList::AniList(QObject *parent) : QObject(parent)
{
	
}

// Basically, converts the "\u75a2" like sequences into real unicode (because they are escaped)
void HandleUnicode(QString* text) {
	QRegularExpression rx("(\\\\u([0-9a-fA-F]{4}))");
	QRegularExpressionMatch rxMatch;
	int pos = 0;
	while ((rxMatch = rx.match(*text, pos)).hasMatch()) {
		(*text).replace(rxMatch.capturedStart(), 6, QChar(rxMatch.captured(2).toUShort(0, 16)));
		pos = rxMatch.capturedStart() + 1;
	}
	text->replace(QRegularExpression("\\\\(n|r)"), "");
}

void AniList::GraphQLQuery(QString body, std::function<void(QJsonObject)> onSuccess, std::function<void()> onFailure) {
	
	body.replace(QRegularExpression("\t"), " "); // It seems that AniList GraphQL doesn't work with tabs
	QByteArray bodyRequest = QByteArray(body.toUtf8());
	
	QNetworkRequest request;
	request.setUrl(QUrl("https://graphql.anilist.co"));
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Content-Length", QByteArray::number(bodyRequest.size()));

	auto* reply = http.post(request, bodyRequest);
	connect(reply, &QNetworkReply::finished, [=] {
		if (reply->error()) {
			std::cerr << "Error!" << std::endl;
			std::cerr << reply->errorString().toStdString() << std::endl;
			std::cerr << reply->error() << std::endl;
			QString answer = reply->readAll();
			std::cerr << answer.toStdString() << std::endl;
			onFailure();
			return;
		}
		QString answer = reply->readAll();
		HandleUnicode(&answer);
		
		QJsonDocument document = QJsonDocument::fromJson(answer.toUtf8());
		
		if (document.isNull() || !document.isObject()) {
			std::cerr << "Error while parsing json. " << std::endl;
			onFailure();
			return ;
		}
		QJsonObject json = QJsonDocument::fromJson(answer.toUtf8()).object();
		onSuccess(std::move(json));
	});
}

void AniList::SearchAnimes(const QString& title, std::function<void(QList<Anime>)> onSuccess, std::function<void()> onFailure) {
	QString body =
	"{\
		\"query\": \"\
			query ($id: Int, $page: Int, $perPage: Int, $search: String) {\
				Page(page: $page, perPage: $perPage) {\
					pageInfo {\
						total\
						currentPage\
						lastPage\
						hasNextPage\
						perPage\
					}\
					media(id: $id, search: $search, type: ANIME) {\
						" + QString(GRAPHQL_ANILIST_MEDIA_CONTENT) + "\
					}\
				}\
			}\
		\",\
		\"variables\": {\
			\"search\": \"" + title + "\"\
		}\
	}";

	GraphQLQuery(body, [=](QJsonObject json) {
		auto medias = json["data"].toObject()["Page"].toObject()["media"].toArray();

		QList<Anime> animes;

		// This loop will check each field of the media before adding it to the Anime object.
		for (auto media : medias) {
			Anime anime;
			if (media.isObject() && media.toObject()["title"].isObject() && media.toObject()["title"].toObject()["romaji"].isString()) {
				anime.SetTitle(media.toObject()["title"].toObject()["romaji"].toString());
			}
			else {
			   anime.SetTitle("[Unknown]");
			}

			if (media.isObject() && media.toObject()["description"].isString()) {
				anime.SetDescription(media.toObject()["description"].toString());
			}
			else {
				anime.SetDescription("[No description provided]");
			}

			if (media.isObject() && media.toObject()["coverImage"].isObject() && media.toObject()["coverImage"].toObject()["extraLarge"].isString()) {
				if (true /*GetSettings().ShouldFetchImages()*/)
					anime.SetCoverImageByUrl(media.toObject()["coverImage"].toObject()["extraLarge"].toString().replace("\\", ""));
			}
			else {
				anime.SetCoverImageByUrl("[No image]");
			}

			if (media.isObject() && media.toObject()["status"].isString()) {
				anime.SetStatus(media.toObject()["status"].toString());
			}
			else {
				anime.SetStatus("[Unknown status]");
			}

			if (media.isObject() && media.toObject()["episodes"].isDouble()) {
				anime.SetEpisodes(media.toObject()["episodes"].toInt());
			}
			else {
				anime.SetEpisodes(-1);
			}

			if (media.isObject() && media.toObject()["startDate"].isObject()) {
				QJsonObject startDateJson = media.toObject()["startDate"].toObject();
				anime.SetStartYear(startDateJson["year"].isDouble() ? startDateJson["year"].toInt() : -1);
				anime.SetStartMonth(startDateJson["month"].isDouble() ? startDateJson["month"].toInt() : -1);
				anime.SetStartDay(startDateJson["day"].isDouble() ? startDateJson["day"].toInt() : -1);
			}

			if (media.isObject() && media.toObject()["endDate"].isObject()) {
				QJsonObject endDateJson = media.toObject()["endDate"].toObject();
				anime.SetEndYear(endDateJson["year"].isDouble() ? endDateJson["year"].toInt() : -1);
				anime.SetEndMonth(endDateJson["month"].isDouble() ? endDateJson["month"].toInt() : -1);
				anime.SetEndDay(endDateJson["day"].isDouble() ? endDateJson["day"].toInt() : -1);
			}

			if (media.isObject() && media.toObject()["genres"].isArray()) {
				for (int i = 0; i < media.toObject()["genres"].toArray().count(); ++i) {
					if (media.toObject()["genres"].toArray()[i].isString())
						anime.AddGenre(media.toObject()["genres"].toArray()[i].toString());
				}
			}
			animes.push_back(anime);
		}
		onSuccess(animes);
	}, [=]{
		onFailure();
	});
}
	
void AniList::FetchUserLists(const QString userName, std::function<void(QList<AnimeList>)> onSuccess, std::function<void()> onFailure) {
	QString body =
    "{\
        \"query\": \"\
            query {\
                MediaListCollection(userName: \\\"" + userName + "\\\", type: ANIME) {\
                    lists {\
                        name\
                        entries {\
                            id\
                            media {\
                                " + QString(GRAPHQL_ANILIST_MEDIA_CONTENT) + "\
                            }\
                        }\
                    }\
                }\
            }\",\
        \"variables\": null\
    }";

	GraphQLQuery(body, [=](QJsonObject json) {
	
		QList<AnimeList> lists;

			
		for (int i = 0; i < json["data"].toObject()["MediaListCollection"].toObject()["lists"].toArray().count(); ++i) {
			auto listJson = json["data"].toObject()["MediaListCollection"].toObject()["lists"].toArray()[i].toObject();
			auto entries = json["data"].toObject()["MediaListCollection"].toObject()["lists"].toArray()[i].toObject()["entries"].toArray();
			AnimeList list(listJson["name"].toString());
			
			for (auto entry : entries) {
				auto media = entry.toObject()["media"].toObject();
				Anime anime;
                if (media["title"].isObject() && media["title"].toObject()["romaji"].isString()) {
					anime.SetTitle(media["title"].toObject()["romaji"].toString());
				}
				else {
				   anime.SetTitle("[Unknown]");
				}
	
				if (media["description"].isString()) {
					anime.SetDescription(media["description"].toString());
				}
				else {
					anime.SetDescription("[No description provided]");
				}
	
				if (media["coverImage"].isObject() && media["coverImage"].toObject()["extraLarge"].isString()) {
					if (true /*GetSettings().ShouldFetchImages()*/)
						anime.SetCoverImageByUrl(media["coverImage"].toObject()["extraLarge"].toString().replace("\\", ""));
				}
				else {
					anime.SetCoverImageByUrl("[No image]");
				}
	
				if (media["status"].isString()) {
					anime.SetStatus(media["status"].toString());
				}
				else {
					anime.SetStatus("[Unknown status]");
				}
	
				if (media["episodes"].isDouble()) {
					anime.SetEpisodes(media["episodes"].toInt());
				}
				else {
					anime.SetEpisodes(-1);
				}
	
				if (media["startDate"].isObject()) {
					QJsonObject startDateJson = media["startDate"].toObject();
					anime.SetStartYear(startDateJson["year"].isDouble() ? startDateJson["year"].toInt() : -1);
					anime.SetStartMonth(startDateJson["month"].isDouble() ? startDateJson["month"].toInt() : -1);
					anime.SetStartDay(startDateJson["day"].isDouble() ? startDateJson["day"].toInt() : -1);
				}
	
				if (media["endDate"].isObject()) {
					QJsonObject endDateJson = media["endDate"].toObject();
					anime.SetEndYear(endDateJson["year"].isDouble() ? endDateJson["year"].toInt() : -1);
					anime.SetEndMonth(endDateJson["month"].isDouble() ? endDateJson["month"].toInt() : -1);
					anime.SetEndDay(endDateJson["day"].isDouble() ? endDateJson["day"].toInt() : -1);
				}
	
				if (media["genres"].isArray()) {
					for (int i = 0; i < media["genres"].toArray().count(); ++i) {
						if (media["genres"].toArray()[i].isString())
							anime.AddGenre(media["genres"].toArray()[i].toString());
					}
				}
				
				list.add(anime);
			}
			lists.push_back(list);
		}
		
		onSuccess(lists);
	}, [=]{
		onFailure();
	});
}
