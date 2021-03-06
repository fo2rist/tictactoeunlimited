/*
 * GameLogic.cpp
 *
 *  Created on: 27.01.2013
 *      Author: Dmitry
 */

#include "GameLogic.hpp"

#include <bb/cascades/ActivityIndicator>
#include <bb/cascades/Button>
#include <bb/cascades/Container>
#include <bb/cascades/ImagePaint>
#include <bb/cascades/ImageButton>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Label>
#include <bb/cascades/Dialog>
#include <bb/cascades/ImageToggleButton>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>

//#include <QtDeclarative/qdeclarativecomponent.h>
#include <QPoint>

using namespace bb::cascades;

//Length of the line to win
static const int WIN_LINE_LENGTH = 4;

//Directions to walk through cells
static const QPoint directionN = QPoint(0, -1);
static const QPoint directionS = QPoint(0, 1);
static const QPoint directionW = QPoint(-1, 0);
static const QPoint directionE = QPoint(1, 0);
static const QPoint directionNW = QPoint(-1, -1);
static const QPoint directionNE = QPoint(1, -1);
static const QPoint directionSW = QPoint(-1, 1);
static const QPoint directionSE = QPoint(1, 1);

GameLogic::GameLogic(QObject *parent)
: QObject(parent) {
	gameField_ = 0;

	gameMode_ = GameModeSinglePlayer;
	currentTurn_ = TurnX;
	gameNumber_ = 0;
	numberOfWins_ = 0;
	numberOfDefeats_ = 0;

	C_userWin_ = 10;
	C_enemyWin_ = 9;
	C_turnsLeftToWin_ = 100;
	C_freeLinesAroundCell_ = 1;
}

GameLogic::~GameLogic() {
	cleanGameField();
}

void GameLogic::initializeGame(int width, int height, GameMode mode) {
	//Clean old game
	cleanGameField();

	//Clear game state
	currentTurn_ = TurnX; //First player starts by default
	gameNumber_ = 0;
	numberOfWins_ = 0;
	numberOfDefeats_ = 0;

	//Set new game parameters
	gameMode_ = mode;
	gameWidth_ = width;
	gameHeight_ = height;


	//Init game field
	initGameField();

	//Notify UI to redraw everything
	emit currentPlayerChanged(currentPlayer());
	emit numberOfWinsChanged(numberOfWins_);
	emit numberOfDefeatsChanged(numberOfDefeats_);
}

void GameLogic::setParameters(QString c_usersWin, QString c_aisWin, QString c_cellsLeft, QString c_freeLines) {
	bool result;
	C_userWin_ = c_usersWin.toInt(&result, 10);
	C_enemyWin_ = c_aisWin.toInt(&result, 10);
	C_turnsLeftToWin_ = c_cellsLeft.toInt(&result, 10);
	C_freeLinesAroundCell_ = c_freeLines.toInt(&result, 10);
}

int GameLogic::numberOfWins() const {
	return numberOfWins_;
}

int GameLogic::numberOfDefeats() const {
	return numberOfDefeats_;
}

int GameLogic::currentPlayer() const {
	return currentTurn_;
}

void GameLogic::onButtonClicked(QPoint position) {
	makeTurn(position);

	//Check for palyer's win
	if (checkForWin(position)) {
		return;
	}

	//Calculate computer's turn
	QPoint computersTurnPosition = bestTurnFor(currentTurn_);

	if (computersTurnPosition == QPoint(-1, -1)) {
		emit showDialog("asset:///images/dialog_no_turns.png");
		return;
	}

	//If we play vs CPU make this turn
	if (gameMode_ == GameModeSinglePlayer) {
		makeTurn(computersTurnPosition);

		//Check for computer's win
		if(checkForWin(computersTurnPosition)) {
			return;
		}
	} else {
		//Wait for next player turn
		emit currentPlayerChanged(currentPlayer());
	}
}

void GameLogic::resetGame() {
	cleanGameField();
	initGameField();

	emit fieldErased();

	//increase game number to switch first player
	gameNumber_++;
	//Switch first player every second time
	switch (gameNumber_ % 2) {
	case 0:
		currentTurn_ = TurnX;
		break;
	case 1:
		currentTurn_ = TurnO;
		//Make AI's turn automatically
		if (gameMode_ == GameModeSinglePlayer) {
			QPoint computersTurnPosition = bestTurnFor(currentTurn_);
			makeTurn(computersTurnPosition);
		}
		break;
	}
	emit currentPlayerChanged(currentPlayer());
}

void GameLogic::makeTurn(QPoint position) {
	switch (currentTurn_) {
		case TurnX:
			gameField_[position.x()][position.y()] = CellStateX;
			emit cellFilled(position.x(), position.y(), CellStateX);
			break;
		case TurnO:
			gameField_[position.x()][position.y()] = CellStateO;
			emit cellFilled(position.x(), position.y(), CellStateO);
			break;
		case TurnV:
			gameField_[position.x()][position.y()] = CellStateV;
			emit cellFilled(position.x(), position.y(), CellStateV);
			break;
	}

	//Figure out who is the next
	switch (gameMode_) {
		case GameModeSinglePlayer:
		case GameModeTwoPlayers:
			if (currentTurn_ == TurnX) {
				currentTurn_ = TurnO;
			} else {
				currentTurn_ = TurnX;
			}
			break;
		case GameModeThreePlayers:
			if (currentTurn_ == TurnX) {
				currentTurn_ = TurnO;
			} else if (currentTurn_ == TurnO) {
				currentTurn_ = TurnV;
			} else {
				currentTurn_ = TurnX;
			}
			break;
	}
}

bool GameLogic::checkForWin(QPoint position) {
	if (getLineLength(position, directionE) + getLineLength(position, directionW) > WIN_LINE_LENGTH
			|| getLineLength(position, directionN) + getLineLength(position, directionS) > WIN_LINE_LENGTH
			|| getLineLength(position, directionNE) + getLineLength(position, directionSW) > WIN_LINE_LENGTH
			|| getLineLength(position, directionNW) + getLineLength(position, directionSE) > WIN_LINE_LENGTH) {

		CellState cellState = gameField_[position.x()][position.y()];
		QString background;
		if (cellState == CellStateX) {
			background= "asset:///images/dialog_winner_x.png";
			numberOfWins_++;
			emit numberOfWinsChanged(numberOfWins_);
		} else {
			background = "asset:///images/dialog_winner_o.png";
			numberOfDefeats_++;
			emit numberOfDefeatsChanged(numberOfDefeats_);
		}

		emit showDialog(background);
		return true;
	}
	return false;
}

QPoint GameLogic::bestTurnFor(TurnType turnType) const {
	CellState desiredState;
	CellState enemysState;
	switch (turnType) {
		case TurnX:
			desiredState = CellStateX;
			enemysState = CellStateO;
			break;
		case TurnO:
			desiredState = CellStateO;
			enemysState = CellStateX;
			break;
		case TurnV:
			//not implemented
			desiredState = CellStateV;
			return QPoint(-1, -1); //impossible point
	}

	//Go through matrix an look for best point
	int bestWeight = 0;
	QPoint bestPoint = QPoint(-1, -1); //impossible point
	for (int x = 0; x < gameWidth_; ++x) {
		for (int y = 0; y < gameHeight_; ++y) {
			QPoint position = QPoint(x, y);
			int playersWeight = calculateWeightFor(position, desiredState);
			int enemysWeight = calculateWeightFor(position, enemysState);

			int total = playersWeight*C_userWin_ + enemysWeight*C_enemyWin_;
			if (total > bestWeight) {
				bestWeight = total;
				bestPoint = position;
			}
		}
	}

	return bestPoint;
}

int GameLogic::getLineLength(QPoint initialPoint, QPoint direction) const {
	int x = initialPoint.x();
	int y = initialPoint.y();

	int result = 0;
	CellState desiredCellState = gameField_[x][y]; //Will calculate cell of same type as the initial
	do {
		result++; //Take into account current cell and move forward in given direction.
		x += direction.x();
		y += direction.y();
	} while(x < gameWidth_
			&& x >= 0
			&& y < gameHeight_
			&& y >= 0
			&& gameField_[x][y] == desiredCellState);

	return result;
}

int GameLogic::calculateWeightFor(QPoint position, CellState desiredState) const {
	//Impossible point
	if (gameField_[position.x()][position.y()] != CellStateEmpty) {
		return -1;
	}

	//1 Maximal possible line * lines count (low priority factor)
	int cumulativeLinesLength = 0;
	//2 Turns left to win if win possible (high priority)
	int turnsLeftToWin = WIN_LINE_LENGTH;

	int lineN_S = calculateMaxLineLength(position, directionN, desiredState)
			+ calculateMaxLineLength(position, directionS, desiredState);
	if (lineN_S > WIN_LINE_LENGTH) { //Take into account only directions that may win
		cumulativeLinesLength += lineN_S;

		int cellsFilled = calculateFilledCells(position, directionN, desiredState)
					+ calculateFilledCells(position, directionS, desiredState);
		turnsLeftToWin = qMin(turnsLeftToWin, WIN_LINE_LENGTH - cellsFilled);
	}

	int lineE_W = calculateMaxLineLength(position, directionE, desiredState)
			+ calculateMaxLineLength(position, directionW, desiredState);
	if (lineE_W > WIN_LINE_LENGTH) { //Take into account only directions that may win
		cumulativeLinesLength += lineE_W;

		int cellsFilled = calculateFilledCells(position, directionE, desiredState)
					+ calculateFilledCells(position, directionW, desiredState);
		turnsLeftToWin = qMin(turnsLeftToWin, WIN_LINE_LENGTH - cellsFilled);
	}

	int lineNE_SW = calculateMaxLineLength(position, directionNE, desiredState)
			+ calculateMaxLineLength(position, directionSW, desiredState);
	if (lineNE_SW > WIN_LINE_LENGTH) { //Take into account only directions that may win
		cumulativeLinesLength += lineNE_SW;

		int cellsFilled = calculateFilledCells(position, directionNE, desiredState)
					+ calculateFilledCells(position, directionSW, desiredState);
		turnsLeftToWin = qMin(turnsLeftToWin, WIN_LINE_LENGTH - cellsFilled);
	}

	int lineNW_SE = calculateMaxLineLength(position, directionNW, desiredState)
			+ calculateMaxLineLength(position, directionSE, desiredState);
	if (lineNW_SE > WIN_LINE_LENGTH) { //Take into account only directions that may win
		cumulativeLinesLength += lineNW_SE;

		int cellsFilled = calculateFilledCells(position, directionNW, desiredState)
					+ calculateFilledCells(position, directionSE, desiredState);
		turnsLeftToWin = qMin(turnsLeftToWin, WIN_LINE_LENGTH - cellsFilled);
	}

	//If win impossible
	if (cumulativeLinesLength == 0) {
		return 0;
	}

	//If win possible
	return C_turnsLeftToWin_ * qPow((WIN_LINE_LENGTH - turnsLeftToWin), 2)
			+ C_freeLinesAroundCell_ * cumulativeLinesLength;
}

int GameLogic::calculateMaxLineLength(QPoint initialPoint, QPoint direction, CellState desiredState) const {
	int x = initialPoint.x();
	int y = initialPoint.y();

	int result = 0;
	//Calculate our own and empty cells
	while (x < gameWidth_
			&& x >= 0
			&& y < gameHeight_
			&& y >= 0
			&& (gameField_[x][y] == desiredState || gameField_[x][y] == CellStateEmpty)) {
		result++; //Take into account current cell and move forward in given direction.
		x += direction.x();
		y += direction.y();
	}

	return result;
}

int GameLogic::calculateFilledCells(QPoint initialPoint, QPoint direction, CellState desiredState) const {
	//Start from "next" cell
	int x = initialPoint.x() + direction.x();
	int y = initialPoint.y() + direction.y();

	int result = 0;
	//Go through own cells
	while (x < gameWidth_
			&& x >= 0
			&& y < gameHeight_
			&& y >= 0
			&& (gameField_[x][y] == desiredState)) {
		result++;
		x += direction.x();
		y += direction.y();
	}

	return result;
}

void GameLogic::initGameField() {
	gameField_ = new CellState*[gameWidth_];
	for (int x = 0; x < gameWidth_; ++x) {
		gameField_[x] = new CellState[gameHeight_];
		for (int y = 0; y < gameHeight_; ++y) {
			gameField_[x][y] = CellStateEmpty;
		}
	}
}

void GameLogic::cleanGameField() {
	if (gameField_ != 0) {
		for (int x = 0; x < gameWidth_; ++x) {
			delete[] gameField_[x];
		}
		delete[] gameField_;
		gameField_ = 0;
	}
}
