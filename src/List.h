#ifndef LIST_H
#define LIST_H
#include <QList>
#include "Anime.h"

class List
{
	
public:
	List() {};
	List(QString name): name(name) {};
	List(QString name, QList<Anime> animes): name(name), animes(animes) {};
	
	void add(const Anime& anime) { animes.push_back(anime); };
	void removeByName(const QString& name) {
		animes.removeIf([=](Anime anime) { return anime.getTitle() == name; });
	}
	
	const QString getName() const { return name; }
	const QList<Anime>& getAnimes() const { return animes; }

private:
	
	QString name;
	QList<Anime> animes;
};

#endif // LIST_H
