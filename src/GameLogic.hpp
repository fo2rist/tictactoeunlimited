/*
 * GameLogic.h
 *
 *  Created on: 27.01.2013
 *      Author: Dmitry
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include <qobject.h>

namespace bb {
	namespace cascades {
		class Container;
	}
}
class QPoint;

class GameLogic: public QObject {
	Q_OBJECT

public:
	GameLogic(QObject* parent = 0);
	virtual ~GameLogic();

	Q_INVOKABLE void initializeField(bb::cascades::Container *gameFieldContainer);

private:
	QPoint bestTurnFor();

private:
	/// Game area with turns info.
	/// Index like a[x][y]
	unsigned char **gameArea_;
};

#endif /* GAMELOGIC_H_ */
