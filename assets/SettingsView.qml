import bb.cascades 1.0

Page {
    //BG by http://dioma.deviantart.com/
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
	            text: "10"
	        }
        }
        Container {
	        Label {
	            text: "AI's win"
	        }
	        TextField {
	            id: c_aisWin
	            inputMode: TextFieldInputMode.NumbersAndPunctuation
	            text: "9"
	        }
        }
        Container {
	        Label {
	            text: "Cells to win left"
	        }
	        TextField {
	            id: c_cellsLeft
	            inputMode: TextFieldInputMode.NumbersAndPunctuation
	            text: "100"
	        }
        }
        Container {
	        Label {
	            text: "Free lines around"
	        }
	        TextField {
	            id: c_freeLines
	            inputMode: TextFieldInputMode.NumbersAndPunctuation
	            text: "1"
	        }
        }
        Button {
            text: "Save"
            horizontalAlignment: HorizontalAlignment.Center
            onClicked: { game.setParameters(c_usersWin.text, c_aisWin.text, c_cellsLeft.text, c_freeLines.text) }
        }
    }
}
