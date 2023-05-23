#ifndef STATUS_H
#define STATUS_H

#include "QObject"

class StatusClass 
{
	Q_GADGET
	
public:
	enum States {
		None, InProgress, Error, Completed
	};
	Q_ENUM(States)
};

using Status = StatusClass::States;

Q_DECLARE_METATYPE(StatusClass);

#endif // STATUS_H
