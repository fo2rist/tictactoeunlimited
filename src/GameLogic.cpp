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

///Possible states for game fields.
enum FieldState {
	FiledStateEmpty = 0,
	FiledStateX = 1,
	FiledStateO = 2
};

///Current turn.
enum CurrentTurn {
	CurrentTurnX = FiledStateX,
	CurrentTurnO = FiledStateO
};

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

void GameLogic::initializeField(Container *gameFieldContainer) {
	for (int i=0; i<GAME_HEIGHT; i++) {
		Container *row = Container::create()
				.parent(gameFieldContainer)
				.horizontal(HorizontalAlignment::Center)
				.layout(StackLayout::create()
							.parent(gameFieldContainer)
							.orientation(LayoutOrientation::LeftToRight));

		for (int j=0; j<GAME_WIDTH; j++) {
			ImageToggleButton* imageButton = ImageToggleButton::create()
					.parent(row)
					.imageDefault(QUrl("asset:///images/cell_empty.png"))
					.imagePressedUnchecked(QUrl("asset:///images/cell_empty.png"))
					.imageChecked(QUrl("asset:///images/cell_x.png"))
					.imageDisabledChecked(QUrl("asset:///images/cell_x.png"))
					.imagePressedChecked(QUrl("asset:///images/cell_x.png"))
					.imageDisabledUnchecked(QUrl("asset:///images/cell_o.png"))
					.preferredSize(130, 130)
					.margins(0, 0, 0, 0);
			row->add(imageButton);
		}

		gameFieldContainer->add(row);
	}
}
