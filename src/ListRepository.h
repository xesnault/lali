#ifndef LIST_REPOSITORY_H
#define LIST_REPOSITORY_H
#include <QList>
#include "List.h"

class ListRepository
{
	
public:
	ListRepository(const QString& dataPath): dataPath(dataPath) {};

	QList<List> getAll();
	void save(QList<List> lists); // Save everything for the moment
	
private:
	
	QString dataPath;
	QList<List> loadLists();
	QList<List> cachedLists;
};

#endif // LIST_REPOSITORY_H
