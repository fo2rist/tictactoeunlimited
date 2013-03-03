import bb.cascades 1.0
import bb.system 1.0

Page {
    id: btSetupPage
    
	actions: [
        ActionItem {
            title: qsTr("Refresh List")
            imageSource: "asset:///images/ic_refresh.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                _btController.deviceListing.discover();
            }
        },
        ActionItem {
            title: qsTr("Start Server")
            imageSource: "asset:///images/ic_server.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                gameSizeDialog.show()    
            }
        }
	]

    attachedObjects: [
        ComponentDefinition {
            id: gamePageDefinition
            source: "GameView.qml"
        },
        SystemListDialog {
	        id: gameSizeDialog
	        title: "Game size"
	        	        
	        onFinished: {
		        if (gameSizeDialog.result == SystemUiResult.ConfirmButtonSelection) {
                    _btController.chatManager.startSPPServer()
                    
                    var page = gamePageDefinition.createObject();
                    switch (gameSizeDialog.selectedIndices[0]) {
                        case 0:
                        	page.gameWidth = 6;
                        	page.gameHeight = 6;
                            break;
                        case 1:
                        	page.gameWidth = 8;
                        	page.gameHeight = 8;
                            break;
                        case 2:
                        	page.gameWidth = 9;
                        	page.gameHeight = 9;
                            break;
                        case 3:
                        	page.gameWidth = 6;
                        	page.gameHeight = 10;
                            break;
                        case 4:
                        	page.gameWidth = 8;
                        	page.gameHeight = 14;
                            break;
						default:
                            page.gameWidth = 6;
                            page.gameHeight = 6;
                    }
                    page.initializeGame();
                    navigationPane.push(page);
                    navigationPane.remove(btSetupPage);
                    btSetupPage.deleteLater()
                }
            }
	    }
	]
    
    onCreationCompleted: {
        gameSizeDialog.appendItem("6 x 6");
        gameSizeDialog.appendItem("8 x 8", true, true);//Default item
        gameSizeDialog.appendItem("9 x 9");
        gameSizeDialog.appendItem("6 x 10");
        gameSizeDialog.appendItem("8 x 14");
    }

    Container {
        Label {
            id: title
            text: _btController.localDeviceInfo.name
        }

        ListView {
            dataModel: _btController.deviceListing.model

            listItemComponents: [
                ListItemComponent {
                    type: "listItem"
                    StandardListItem {
                        title: ListItemData.deviceName
                        //description:  ListItemData.deviceAddress
                        status: "0x"+ListItemData.deviceClass
                    }
                }
            ]

            onTriggered: {
                var selectedItem = dataModel.data(indexPath);
                _btController.setRemoteDevice(selectedItem.deviceAddress);
                _btController.chatManager.connectToSPPService();
            }

            function itemType(data, indexPath) {
                if (indexPath.length == 1) {
                    // If the index path contains a single integer, the item
                    // is a "header" type item
                    return "header";
                } else {
                    // If the index path contains more than one integer, the
                    // item is a "listItem" type item
                    return "listItem";
                }
            }
        }
    }
}
