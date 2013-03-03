import bb.cascades 1.0

Page {
	actions: [
        ActionItem {
            title: qsTr("Search Devices")
            imageSource: "asset:///images/device_discovery.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                _btController.deviceListing.discover();
            }
        },
        ActionItem {
            title: qsTr("SPP Server")
            imageSource: "asset:///images/send.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                _btController.chatManager.startSPPServer()
                navigationPane.push(chatPage.createObject())
            }
        }
	]
    Container {
        ListView {
            dataModel: _btController.deviceListing.model

            listItemComponents: [
                ListItemComponent {
                    type: "listItem"
                    StandardListItem {
                        title: ListItemData.deviceName
                        description: ListItemData.deviceAddress
                        status: ListItemData.deviceClass
                    }
                }
            ]

            onTriggered: {
                var selectedItem = dataModel.data(indexPath);
                _btController.setRemoteDevice(selectedItem.deviceAddress);

                navigationPane.push(remoteDevicePage.createObject())
            }
        }
    }
}
