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
    Anime();

    const QString& getTitle() const;
    const QString& GetDescription() const;
    const QString& GetSynopsis() const; // Alias for GetDescription()
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
	
	

private:

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
