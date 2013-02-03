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

///Possible states for game fields.
enum FieldState {
	FiledStateEmpty = 0,
	FiledStateX = 1,
	FiledStateO = 2
};

///Current turn.
enum TurnType {
	CurrentTurnX = FiledStateX,
	CurrentTurnO = FiledStateO
};

class GameLogic: public QObject {
	Q_OBJECT

public:
	GameLogic(QObject* parent = 0);
	virtual ~GameLogic();

	Q_INVOKABLE void initializeGame(bb::cascades::Container *gameFieldContainer);

public slots:
	void onButtonClicked(bool checked);

private:
	QPoint bestTurnFor(TurnType turnType);

private:
	///Initialized by @link initializeGame()
	bb::cascades::Container* currentGameField_;

	/// Game area with turns info.
	/// Index like a[x][y]
	unsigned char **gameArea_;
};

#endif /* GAMELOGIC_H_ */
