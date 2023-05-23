#ifndef ANIME_H
#define ANIME_H
#include <QObject>
#include <QString>
#include <QVector>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

class Anime
{
	
public:
	Q_GADGET
	Q_PROPERTY(QString title MEMBER title CONSTANT)
	Q_PROPERTY(QString description MEMBER description CONSTANT)
	Q_PROPERTY(int episodeCount MEMBER episodes CONSTANT)
	Q_PROPERTY(int startDay MEMBER startDay CONSTANT)
	Q_PROPERTY(int startMonth MEMBER startMonth CONSTANT)
	Q_PROPERTY(int startYear MEMBER startYear CONSTANT)
	Q_PROPERTY(int endDay MEMBER endDay CONSTANT)
	Q_PROPERTY(int endMonth MEMBER endMonth CONSTANT)
	Q_PROPERTY(int endYear MEMBER endYear CONSTANT)
	Q_PROPERTY(QString imageUrl READ getCoverImageUrl CONSTANT)
	Q_PROPERTY(QString cachedImage READ getCachedImagepath CONSTANT)
public:
	Anime();
	
	const QString& getTitle() const;
	const QString& GetDescription() const;
	// Alias for GetDescription()
	const QString& GetSynopsis() const;
	const QString& getCoverImageUrl() const;
	const QString getCachedImagepath() {
		static QString path = QDir::homePath() + "/.cache/lali/";
		return "file:" + path + FormatName(title);
	}
	QString FormatName(QString name) {
		for (auto& character : name) {
			if (!character.isDigit() && !character.isLetter() && !character.isSpace())
				character = '_';
		}
		return name;
	}
	const QVector<QString>& GetGenres() const;
	const QString& GetStatus() const;
	int GetEpisodes() const;
	int GetStartYear() const;
	int GetStartMonth() const;
	int GetStartDay() const;
	int GetEndYear() const;
	int GetEndMonth() const;
	int GetEndDay() const;
	
	void SetTitle(const QString& title);
	void SetDescription(const QString& description);
	void SetCoverImageByUrl(const QString& coverImageUrl);
	void SetGenres(const QVector<QString>& genres);
	void AddGenre(const QString& genreName);
	void SetStatus(const QString& status);
	void SetEpisodes(int episodes);
	void SetStartYear(int year);
	void SetStartMonth(int month);
	void SetStartDay(int day);
	void SetEndYear(int year);
	void SetEndMonth(int month);
	void SetEndDay(int day);
	
	
	
	// private:
	
	QString title;
	QString description;
	QString coverImageUrl;
	QVector<QString> genres;
	QString status;
	int episodes;
	
	int startYear, startMonth, startDay;
	int endYear, endMonth, endDay;
};

#endif // ANIME_H
