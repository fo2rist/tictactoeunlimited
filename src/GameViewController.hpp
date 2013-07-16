/*
 * GameViewController.hpp
 *
 *  Created on: 16.07.2013
 *      Author: Dmitry
 */

#ifndef GAMEVIEWCONTROLLER_HPP_
#define GAMEVIEWCONTROLLER_HPP_

#include <qobject.h>

namespace bb {
	namespace cascades {
		class Container;
	}
}
class GameLogic;

class GameViewController: public QObject {
	Q_OBJECT
public:
	///Create controller and automatically connect to game's signals.
	GameViewController(GameLogic* game, QObject* parent = 0);
	virtual ~GameViewController();

	///Init game with width/height number of cells.
	///Will place buttons in container and start game.
	Q_INVOKABLE void initializeGame(bb::cascades::Container *gameFieldContainer,
			int width,
			int height,
			int mode);
public slots:
	void onButtonClicked(bool checked);

	void onCellFilled(int x, int y, int cellState);
	void onFieldErased();
	void onShowDialog(QString background);

private:
	GameLogic* game_;
	///Initialized by @link initializeGame()
	bb::cascades::Container* currentGameFieldContainer_;
};

#endif /* GAMEVIEWCONTROLLER_HPP_ */
