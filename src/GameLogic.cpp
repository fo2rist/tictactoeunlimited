/*
 * GameLogic.cpp
 *
 *  Created on: 27.01.2013
 *      Author: Dmitry
 */

#include "GameLogic.hpp"

#include <bb/cascades/Container>
#include <bb/cascades/Button>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/ImageToggleButton>
#include <QtDeclarative/qdeclarativecomponent.h>
#include <QPoint>

using namespace bb::cascades;

static const char *POSITION_PROPERTY = "position_property";

//Default game filed size for 1280x768 screen
static const int GAME_WIDTH = 6;
static const int GAME_HEIGHT = 10;

GameLogic::GameLogic(QObject *parent)
: QObject(parent) {
	//Init game field
	gameArea_ = new unsigned char*[GAME_WIDTH];
	for (int x = 0; x < GAME_WIDTH; ++x) {
		gameArea_[x] = new unsigned char[GAME_HEIGHT];
		for (int y = 0; y < GAME_HEIGHT; ++y) {
			gameArea_[x][y] = FiledStateEmpty;
		}
	}
}

GameLogic::~GameLogic() {
	for (int x = 0; x < GAME_WIDTH; ++x) {
		delete[] gameArea_[x];
	}
	delete[] gameArea_;
}

void GameLogic::initializeGame(Container *gameFieldContainer) {
	currentGameField_ = gameFieldContainer;

	for (int y=0; y<GAME_HEIGHT; ++y) {
		Container *row = Container::create()
				.parent(gameFieldContainer)
				.horizontal(HorizontalAlignment::Center)
				.layout(StackLayout::create()
							.parent(gameFieldContainer)
							.orientation(LayoutOrientation::LeftToRight));

		for (int x=0; x<GAME_WIDTH; ++x) {
			ImageToggleButton* imageButton = ImageToggleButton::create()
					.parent(row)
					.imageDefault(QUrl("asset:///images/cell_empty.png"))
					.imagePressedUnchecked(QUrl("asset:///images/cell_empty.png"))
					.imageChecked(QUrl("asset:///images/cell_x.png"))
					.imageDisabledChecked(QUrl("asset:///images/cell_x.png"))
					.imagePressedChecked(QUrl("asset:///images/cell_x.png"))
					.imageDisabledUnchecked(QUrl("asset:///images/cell_o.png"))
					.preferredSize(130, 130)
					.margins(0, 0, 0, 0)
					.connect(SIGNAL(checkedChanged(bool)),
							this, SLOT(onButtonClicked(bool)));
			imageButton->setProperty(POSITION_PROPERTY, QPoint(x, y)); //Store button position in button itself
			row->add(imageButton);
		}
		gameFieldContainer->add(row);
	}
}

void GameLogic::onButtonClicked(bool checked) {
	ImageToggleButton* clickedButton = qobject_cast<ImageToggleButton*>(QObject::sender());
	clickedButton->setEnabled(false); //Disable next turn
}

QPoint GameLogic::bestTurnFor(TurnType turnType) {
	return QPoint();
}
