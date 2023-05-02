#ifndef ANIMEQML_H
#define ANIMEQML_H

#include <QObject>
#include "Anime.h"

class AnimeQML : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString title READ getTitle CONSTANT)
	Q_PROPERTY(QString description READ getDescription CONSTANT)
	Q_PROPERTY(int episodeCount READ getEpisodeCount CONSTANT)
	Q_PROPERTY(int startDay READ getStartDay CONSTANT)
	Q_PROPERTY(int startMonth READ getStartMonth CONSTANT)
	Q_PROPERTY(int startYear READ getStartYear CONSTANT)
	Q_PROPERTY(int endDay READ getEndDay CONSTANT)
	Q_PROPERTY(int endMonth READ getEndMonth CONSTANT)
	Q_PROPERTY(int endYear READ getEndYear CONSTANT)
	Q_PROPERTY(QString imageUrl READ getImageUrl CONSTANT)
	Q_PROPERTY(QString cachedImage READ getCachedImage CONSTANT)
public:
	explicit AnimeQML(const Anime& anime, QObject *parent = nullptr);
	
	QString getTitle() { return anime.getTitle(); }
	QString getDescription() { return anime.GetDescription(); }
	
	QString getStatus() { return anime.GetStatus(); }
	int getEpisodeCount() { return anime.GetEpisodes(); }
	int getStartDay() { return anime.GetStartDay(); }
	int getStartMonth() { return anime.GetStartMonth(); }
	int getStartYear() { return anime.GetStartYear(); }
	int getEndDay() { return anime.GetEndDay(); }
	int getEndMonth() { return anime.GetEndMonth(); }
	int getEndYear() { return anime.GetEndYear(); }
	
	QString getImageUrl() { return anime.getCoverImageUrl(); }
	QString getCachedImage() { return anime.getCachedImagepath(); }
	const Anime& getAnime() const { return anime; }
	
private:
	Anime anime;
	
signals:
	
};

Q_DECLARE_METATYPE(AnimeQML)

#endif // ANIMEQML_H
