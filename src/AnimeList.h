#ifndef ANIMELIST_H
#define ANIMELIST_H
#include <QObject>
#include "Anime.h"

class AnimeList
{
	Q_GADGET
	Q_PROPERTY(QString name MEMBER name CONSTANT);
	Q_PROPERTY(QList<Anime> animes MEMBER animes CONSTANT);
public:
	explicit AnimeList();
	AnimeList(QString name): name(name) {};
	AnimeList(QString name, QList<Anime> animes): name(name), animes(animes) {};
	
	void add(const Anime& anime) { animes.push_back(anime); };
	void removeByName(const QString& name) {
		animes.removeIf([=](Anime anime) { return anime.getTitle() == name; });
	}
	Q_INVOKABLE void setName(QString name) {
		this->name = name;
	}
	Q_INVOKABLE const QString getName() const { return name; }
	Q_INVOKABLE const QList<Anime> getAnimes() const { return animes; }
	
	QString name;
	QList<Anime> animes;
};

Q_DECLARE_METATYPE(AnimeList)

#endif // ANIMELIST_H
