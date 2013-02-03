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

using namespace bb::cascades;

static const int GAME_WIDTH = 6;
static const int GAME_HEIGHT = 10;

GameLogic::GameLogic(QObject *parent)
: QObject(parent){

	for (int i = 0; i < GAME_WIDTH; ++i) {

	}
}

GameLogic::~GameLogic() {
}

void GameLogic::initializeField(Container *container) {
	for (int i=0; i<GAME_HEIGHT; i++) {
		Container *row = Container::create()
				.parent(container)
				.horizontal(HorizontalAlignment::Center)
				.layout(StackLayout::create().orientation(LayoutOrientation::LeftToRight));

		for (int j=0; j<GAME_WIDTH; j++) {
			ImageToggleButton* imageButton = ImageToggleButton::create()
					.parent(row)
					.imageDefault(QUrl("asset:///images/cell_empty.png"))
					.imageChecked(QUrl("asset:///images/cell_x.png"))
					.imageDisabledUnchecked(QUrl("asset:///images/cell_o.png"))
					.preferredSize(130, 130)
					.margins(0, 0, 0, 0);
			row->add(imageButton);
		}

		container->add(row);
	}
}
