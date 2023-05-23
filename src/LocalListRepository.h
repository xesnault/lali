#ifndef LOCALLISTREPOSITORY_H
#define LOCALLISTREPOSITORY_H

#include <QObject>
#include <QList>
#include "AnimeList.h"

class LocalListRepository : public QObject
{
	Q_OBJECT
public:
	explicit LocalListRepository(const QString& dataPath, QObject *parent = nullptr) : QObject{parent}, dataPath(dataPath) {};
	
	QList<AnimeList> getAll();
	void save(QList<AnimeList> lists); // Save everything for the moment
	
private:
	
	QString dataPath;
	QList<AnimeList> loadLists();
	QList<AnimeList> cachedLists;
	
};

#endif // LOCALLISTREPOSITORY_H
