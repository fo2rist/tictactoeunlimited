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
#include <bb/cascades/DockLayout>
#include <bb/cascades/Label>
#include <bb/cascades/Dialog>
#include <bb/cascades/ImageToggleButton>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>

#include <QtDeclarative/qdeclarativecomponent.h>
#include <QPoint>

using namespace bb::cascades;

static const char *POSITION_PROPERTY = "position_property";
static const char *BUTTONS_NAME = "cell_button";

static const int DEFAULT_SCREEN_WIDTH = 720;

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

void GameLogic::initializeGame(Container *gameFieldContainer, int width, int height) {
	currentGameFieldContainer_ = gameFieldContainer;
	gameWidth_ = width;
	gameHeight_ = height;
	int cellSize = DEFAULT_SCREEN_WIDTH / width;


	//Init game field
	cleanGameField();
	initGameField();

	//Init UI
	for (int y=0; y<gameHeight_; ++y) {
		Container *row = Container::create()
				.parent(gameFieldContainer)
				.horizontal(HorizontalAlignment::Center)
				.layout(StackLayout::create()
							.parent(gameFieldContainer)
							.orientation(LayoutOrientation::LeftToRight));

		for (int x=0; x<gameWidth_; ++x) {
			ImageToggleButton* imageButton = ImageToggleButton::create()
					.parent(row)
					.objectName(BUTTONS_NAME)
					.imageDefault(QUrl("asset:///images/cell_empty.png"))          // \ _Default state
					.imagePressedUnchecked(QUrl("asset:///images/cell_empty.png")) // /
					.imageChecked(QUrl("asset:///images/cell_x.png"))              // \.
					.imageDisabledChecked(QUrl("asset:///images/cell_x.png"))      //  >-Checked by user
					.imagePressedChecked(QUrl("asset:///images/cell_x.png"))       // /
					.imageDisabledUnchecked(QUrl("asset:///images/cell_o.png"))    //   -Checked by AI
					.preferredSize(cellSize, cellSize)
					.margins(0, 0, 0, 0);

					QObject::connect(imageButton, SIGNAL(checkedChanged(bool)),
							this, SLOT(onButtonClicked(bool)));
			imageButton->setProperty(POSITION_PROPERTY, QPoint(x, y)); //Store button position in button itself
			row->add(imageButton);
		}
		gameFieldContainer->add(row);
	}
}

void GameLogic::setParameters(QString c_usersWin, QString c_aisWin, QString c_cellsLeft, QString c_freeLines) {
	bool result;
	C_userWin_ = c_usersWin.toInt(&result, 10);
	C_enemyWin_ = c_aisWin.toInt(&result, 10);
	C_turnsLeftToWin_ = c_cellsLeft.toInt(&result, 10);
	C_freeLinesAroundCell_ = c_freeLines.toInt(&result, 10);
}

void GameLogic::onButtonClicked(bool checked) {
	if (checked == false) { //Ignore game rest
		return;
	}

	ImageToggleButton* clickedButton = qobject_cast<ImageToggleButton*>(QObject::sender());
	QPoint position = clickedButton->property(POSITION_PROPERTY).toPoint();

	makeTurn(position, TurnX);

	//Check for palyer's win
	if (checkForWin(position)) {
		return;
	}

	//Calculate computer's turn
	QPoint computersTurnPosition = bestTurnFor(TurnO);
	//Go ahead
	if (computersTurnPosition == QPoint(-1, -1)) {
		Dialog* waitDialog = Dialog::create()
					.content(Container::create()
					.add(ActivityIndicator::create())
					.add(Label::create("No turns!")));
			waitDialog->open();
		return;
	}
	makeTurn(computersTurnPosition, TurnO);

	//Check for computer's win
	if(checkForWin(computersTurnPosition)) {
		return;
	}
}

void GameLogic::resetGame() {
	cleanGameField();
	initGameField();
	QList<ImageToggleButton*> buttons = currentGameFieldContainer_->findChildren<ImageToggleButton*>(BUTTONS_NAME);
	foreach(ImageToggleButton *button, buttons) {
		button->setEnabled(true);
		button->setChecked(false);
	}

	//increase game number to switch first player
	gameNumber_++;
	//Make AI's turn every second time
	if (gameNumber_ % 2 == 1) {
		QPoint computersTurnPosition = bestTurnFor(TurnO);
		makeTurn(computersTurnPosition, TurnO);
	}
}

bool GameLogic::checkForWin(QPoint position){
	if (getLineLength(position, directionE) + getLineLength(position, directionW) > WIN_LINE_LENGTH
			|| getLineLength(position, directionN) + getLineLength(position, directionS) > WIN_LINE_LENGTH
			|| getLineLength(position, directionNE) + getLineLength(position, directionSW) > WIN_LINE_LENGTH
			|| getLineLength(position, directionNW) + getLineLength(position, directionSE) > WIN_LINE_LENGTH) {

		CellState cellState = gameField_[position.x()][position.y()];
		QString text;
		if (cellState == CellStateX) {
			text= "You win!";
			numberOfWins_++;
		} else {
			text = "Computer win...";
			numberOfDefeats_++;
		}

		Button *okButton = Button::create("Ok");
		Dialog* winDialog = Dialog::create()
				.content(Container::create()
						.background(ImagePaint(QUrl("asset:///images/dialog_bg.png"), RepeatPattern::Fill))
						.layout(DockLayout::create())
						.horizontal(HorizontalAlignment::Center)
						.vertical(VerticalAlignment::Center)
						.add(Container::create()
								.layout(StackLayout::create()
										.orientation(LayoutOrientation::TopToBottom))
								.add(Label::create(text).horizontal(HorizontalAlignment::Center))
								.add(okButton))
				);
		QObject::connect(okButton, SIGNAL(clicked()),
						winDialog, SLOT(close()));
		QObject::connect(okButton, SIGNAL(clicked()),
						this, SLOT(resetGame()));
		winDialog->open();
		return true;
	}
	return false;
}

void GameLogic::makeTurn(QPoint position, TurnType turn) {
	//Find button by position
	ImageToggleButton* buttonAtPosition;
	QList<ImageToggleButton*> buttons = currentGameFieldContainer_->findChildren<ImageToggleButton*>(BUTTONS_NAME);
	foreach(ImageToggleButton *button, buttons) {
		if (button->property(POSITION_PROPERTY).toPoint() == position) {
			buttonAtPosition = button;
			break;
		}
	}

	switch (turn) {
		case TurnX:
			gameField_[position.x()][position.y()] = CellStateX;
			buttonAtPosition->setEnabled(false);//Disable next turn in same place
			break;
		case TurnO:
			gameField_[position.x()][position.y()] = CellStateO;

			buttonAtPosition->setChecked(false);
			buttonAtPosition->setEnabled(false);//Disable next turn in same place
			break;
	}
}

QPoint GameLogic::bestTurnFor(TurnType turnType) {
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

int GameLogic::getLineLength(QPoint initialPoint, QPoint direction) {
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

int GameLogic::calculateWeightFor(QPoint position, CellState desiredState) {
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

int GameLogic::calculateMaxLineLength(QPoint initialPoint, QPoint direction, CellState desiredState) {
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

int GameLogic::calculateFilledCells(QPoint initialPoint, QPoint direction, CellState desiredState) {
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
