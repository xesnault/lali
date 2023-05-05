#ifndef LISTQML_H
#define LISTQML_H

#include <QObject>
#include "List.h"
#include "AnimeQML.h"

class ListQML : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged);
	Q_PROPERTY(QList<AnimeQML*> animes READ getAnimes CONSTANT);
public:
	explicit ListQML(List list, QObject *parent = nullptr);
	
	const QString getName() { return list.getName(); }
    void setName(QString name) {
        this->list.setName(name);
        emit nameChanged();
    }
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
    void nameChanged();
	
};

Q_DECLARE_METATYPE(ListQML)

#endif // LISTQML_H
