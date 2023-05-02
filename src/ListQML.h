#ifndef LISTQML_H
#define LISTQML_H

#include <QObject>
#include "List.h"
#include "AnimeQML.h"

class ListQML : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName CONSTANT);
	Q_PROPERTY(QList<AnimeQML*> animes READ getAnimes CONSTANT);
public:
	explicit ListQML(List list, QObject *parent = nullptr);
	
	QString getName() { return list.getName(); }
	QList<AnimeQML*> getAnimes() {
		QList<AnimeQML*> animesQML;
		for (const auto& anime : list.getAnimes()) {
			animesQML.push_back(new AnimeQML(anime));
		}
		return animesQML;
	}
	
private:
	List list;
	
signals:
	
};

Q_DECLARE_METATYPE(ListQML)

#endif // LISTQML_H
