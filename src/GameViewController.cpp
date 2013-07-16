/*
 * GameViewController.cpp
 *
 *  Created on: 16.07.2013
 *      Author: Dmitry
 */

#include "GameViewController.hpp"

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

#include <QPoint>

#include "GameLogic.hpp"

using namespace bb::cascades;

static const int DEFAULT_SCREEN_WIDTH = 660;
static const char *POSITION_PROPERTY = "position_property";
static const char *BUTTONS_NAME = "cell_button";

GameViewController::GameViewController(GameLogic* game, QObject* parent)
: QObject(parent) {
	this->game_ = game;
	connect(game, SIGNAL(cellFilled(int, int, int)),
			this, SLOT(onCellFilled(int, int, int)));
	connect(game, SIGNAL(fieldErased()),
			this, SLOT(onFieldErased()));
	connect(game, SIGNAL(showDialog(QString)),
			this, SLOT(onShowDialog(QString)));

}

GameViewController::~GameViewController() {
}

void GameViewController::initializeGame(Container *gameFieldContainer, int width, int height, int mode) {
	game_->initializeGame(width, height, (GameMode)mode);

	currentGameFieldContainer_ = gameFieldContainer;
	//Init UI
	int cellSize = DEFAULT_SCREEN_WIDTH / width;
	for (int y=0; y<height; ++y) {
		Container *row = Container::create()
				.parent(gameFieldContainer)
				.horizontal(HorizontalAlignment::Center)
				.layout(StackLayout::create()
							.parent(gameFieldContainer)
							.orientation(LayoutOrientation::LeftToRight));

		for (int x=0; x<width; ++x) {
			ImageToggleButton* imageButton = ImageToggleButton::create()
					.parent(row)
					.objectName(BUTTONS_NAME)
					.imageDefault(QUrl("asset:///images/cell_empty.png"))          // \.
					.imagePressedUnchecked(QUrl("asset:///images/cell_empty.png")) //  \_ Default state
					.imagePressedChecked(QUrl("asset:///images/cell_empty.png"))   //  /
					.imageChecked(QUrl("asset:///images/cell_empty.png"))          // /
					.imageDisabledChecked(QUrl("asset:///images/cell_x.png"))      // - Checked by First Player
					.imageDisabledUnchecked(QUrl("asset:///images/cell_o.png"))    //  -Checked by Second Player
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

void GameViewController::onButtonClicked(bool checked) {
	if (checked == false) { //Ignore game reset
		return;
	}

	ImageToggleButton* clickedButton = qobject_cast<ImageToggleButton*>(QObject::sender());
	QPoint position = clickedButton->property(POSITION_PROPERTY).toPoint();

	game_->onButtonClicked(position);
}

void GameViewController::onCellFilled(int x, int y, int cellState) {
	QPoint position = QPoint(x, y);

	//Find button by position
	ImageToggleButton* buttonAtPosition;
	QList<ImageToggleButton*> buttons = currentGameFieldContainer_->findChildren<ImageToggleButton*>(BUTTONS_NAME);
	foreach(ImageToggleButton *button, buttons) {
		if (button->property(POSITION_PROPERTY).toPoint() == position) {
			buttonAtPosition = button;
			break;
		}
	}

	switch (cellState) {
		case CellStateX:
			buttonAtPosition->setEnabled(false);//Disable next turn in same place
			break;
		case CellStateO:
			buttonAtPosition->setChecked(false);
			buttonAtPosition->setEnabled(false);//Disable next turn in same place
			break;
		case CellStateV:
			//not implemented yet
			onShowDialog("no background");
			break;
	}
}

void GameViewController::onFieldErased() {
	QList<ImageToggleButton*> buttons =
			currentGameFieldContainer_->findChildren<ImageToggleButton*>(BUTTONS_NAME);
	foreach(ImageToggleButton *button, buttons){
		button->setEnabled(true);
		button->setChecked(false);
	}
}

void GameViewController::onShowDialog(QString background) {
	ImageButton *okButton = ImageButton::create()
								.horizontal(HorizontalAlignment::Center)
								.vertical(VerticalAlignment::Bottom)
								.defaultImage(QUrl("asset:///images/ok.png"))
								.pressedImage(QUrl("asset:///images/ok.png"));

		Dialog* winDialog = Dialog::create()
				.content(Container::create()
						.preferredSize(540, 360)
						.background(ImagePaint(QUrl(background), RepeatPattern::Fill))
						.horizontal(HorizontalAlignment::Center)
						.vertical(VerticalAlignment::Center)
						.add(Container::create()
								.preferredSize(500, 320)
								.layout(DockLayout::create())
							.vertical(VerticalAlignment::Center)
							.horizontal(HorizontalAlignment::Center)
							.add(okButton))
				);
		QObject::connect(okButton, SIGNAL(clicked()),
						winDialog, SLOT(close()));
		QObject::connect(okButton, SIGNAL(clicked()),
						game_, SLOT(resetGame()));
		winDialog->open();
}
