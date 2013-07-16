// Drilldown navigation project template
#include "TicTacToeUnlimited.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include "GameLogic.hpp"
#include "GameViewController.hpp"

using namespace bb::cascades;

TicTacToeUnlimited::TicTacToeUnlimited(bb::cascades::Application *app)
: QObject(app)
{
    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    GameLogic *game = new GameLogic(this);
    qml->setContextProperty("game", game);
    qml->setContextProperty("gameController", new GameViewController(game, this));

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
    //Disable menu
    app->setMenuEnabled(false);
}
