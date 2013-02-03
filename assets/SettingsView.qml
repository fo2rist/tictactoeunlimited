import bb.cascades 1.0

Page {
    Container {
        Label {
            text: "Settings"
        }
    }
    
    paneProperties: NavigationPaneProperties {
        backButton: ActionItem {
            title: "Previous page"
            imageSource: "asset:///back.png"
            onTriggered: { navigationPane.pop(); }
        }
    }
}
