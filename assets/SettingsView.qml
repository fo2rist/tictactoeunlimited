import bb.cascades 1.0

Page {
    Container {
        Label {
            text: "Settings"
        }
        Container {
	        Label {
	            text: "User's win"
	        }
	        TextField {
	            id: c_usersWin
	            inputMode: TextFieldInputMode.NumbersAndPunctuation
	            text: "4"
	        }
        }
        Container {
	        Label {
	            text: "AI's win"
	        }
	        TextField {
	            id: c_aisWin
	            inputMode: TextFieldInputMode.NumbersAndPunctuation
	            text: "3"
	        }
        }
        Container {
	        Label {
	            text: "Cells to win left"
	        }
	        TextField {
	            id: c_cellsLeft
	            inputMode: TextFieldInputMode.NumbersAndPunctuation
	            text: "1000"
	        }
        }
        Container {
	        Label {
	            text: "Free lines around"
	        }
	        TextField {
	            id: c_freeLines
	            inputMode: TextFieldInputMode.NumbersAndPunctuation
	            text: "10"
	        }
        }
        Button {
            text: "Save"
            horizontalAlignment: HorizontalAlignment.Center
            onClicked: { game.setParameters(c_usersWin.text, c_aisWin.text, c_cellsLeft.text, c_freeLines.text) }
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
