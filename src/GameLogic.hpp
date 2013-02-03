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

class GameLogic: public QObject {
	Q_OBJECT

public:
	GameLogic(QObject* parent = 0);
	virtual ~GameLogic();

	Q_INVOKABLE void initializeField(bb::cascades::Container *container);

private:
	QPoint bestTurnFor();

private:
	/// Game area with turns info.
	/// Index like a[x][y]
	byte[][] gameArea_;
};

#endif /* GAMELOGIC_H_ */
