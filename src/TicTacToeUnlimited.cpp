#include "TicTacToeUnlimited.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include "GameLogic.hpp"
#include "bluetooth/BTController.hpp"
#include "bluetooth/ChatManager.hpp"
#include "bluetooth/DeviceListing.hpp"
#include "bluetooth/LocalDeviceInfo.hpp"
#include "bluetooth/RemoteDeviceInfo.hpp"

using namespace bb::cascades;

TicTacToeUnlimited::TicTacToeUnlimited(bb::cascades::Application *app)
: QObject(app)
{
	qmlRegisterType<ChatManager>();
	qmlRegisterType<DeviceListing>();
	qmlRegisterType<LocalDeviceInfo>();
	qmlRegisterType<RemoteDeviceInfo>();

    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    //Create and setup game logic object
    qml->setContextProperty("game", new GameLogic(this));
    //and BT
    qml->setContextProperty("_btController", new BTController(this));

    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app->setScene(root);
    //Disable menu
    app->setMenuEnabled(false);
}
