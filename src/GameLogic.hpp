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

///Possible states for game cells.
enum CellState {
	CellStateEmpty = 0,
	CellStateX = 1,
	CellStateO = 2
};

///Current turn.
enum TurnType {
	TurnX = CellStateX, //just make turn and state binary compatible
	TurnO = CellStateO
};

/**
 * Game itself.
 * Contains all game logic and can initialize game field in UI.
 */
class GameLogic: public QObject {
	Q_OBJECT

public:
	GameLogic(QObject* parent = 0);
	virtual ~GameLogic();

	///Init game with width/height number of cells.
	///Will place buttons in container and start game.
	Q_INVOKABLE void initializeGame(bb::cascades::Container *gameFieldContainer, int width, int height);
	///Debug opiton to tune AI's parameters.
	Q_INVOKABLE void setParameters(QString c_usersWin, QString c_aisWin, QString c_cellsLeft, QString c_freeLines);

public slots:
	void onButtonClicked(bool checked);
	void resetGame();

private:
	///Set check-mark in given position.
	///Setup UI cell if necessary.
	void makeTurn(QPoint position, TurnType turn);
	///Check whether current step is the last.
	///@return true if it's a last step.
	bool checkForWin(QPoint position);
	///Calculate best turn position for given gamer(X/O).
	//Will return point (-1,-1) if there are no possible turns.
	QPoint bestTurnFor(TurnType turnType);

	///Get length of the line started by this point in given direction.
	int getLineLength(QPoint initialPoint, QPoint direction);
	///Calculate weight for this point for given cell state.
	///@return 0 - useless point, -1 - impossible point, >0 - good point.
	int calculateWeightFor(QPoint position, CellState desiredState);
	///Calculate number of cells, non blocked by enemy or border in given direction.
	int calculateMaxLineLength(QPoint initialPoint, QPoint direction, CellState desiredState);
	///Calculate number of cells, with desired stated in given direction (before first border).
	///Except initial point itself.
	int calculateFilledCells(QPoint initialPoint, QPoint direction, CellState desiredState);

	void initGameField();
	void cleanGameField();

	void showGameOverDialog(const QString& background);

private:
	///Initialized by @link initializeGame()
	bb::cascades::Container* currentGameFieldContainer_;
	int gameWidth_;
	int gameHeight_;

	/// Game field with turns info.
	/// Index like a[x][y]
	CellState **gameField_;

	int gameNumber_;
	int numberOfWins_;
	int numberOfDefeats_;

	//Game logic coefficients
	int C_userWin_;
	int C_enemyWin_;
	int C_turnsLeftToWin_;
	int C_freeLinesAroundCell_;
};

#endif /* GAMELOGIC_H_ */
