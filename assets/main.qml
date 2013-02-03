// Drilldown navigation project template
import bb.cascades 1.0

NavigationPane {
    id: navigationPane
    
    onCreationCompleted: {
        //DEBUG
        playButton.clicked()
    }
        
    attachedObjects: [
        ComponentDefinition {
            id: gamePageDefinition;
            source: "GameView.qml"
        },
        ComponentDefinition {
            id: settingsPageDefinition;
            source: "SettingsView.qml"
        }
    ]
    
    
    Page {
        Container {
	        layout: DockLayout {
            }

            // Background ImageView
            ImageView {
	            imageSource: "asset:///images/bg4.png"
	        }
		    
		    Container {
		        id: menuContainer
	            horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                Button {
	                id: playButton
	                text: "Play"
	                onClicked: {
	                    var page = gamePageDefinition.createObject();
	                    navigationPane.push(page);
	                } 
	            }
	            
//		        Button {
//		            id: settingsButton
//	                text: "Settings"
//	                onClicked: {
//	                    var page = settingsPageDefinition.createObject();
//	                    navigationPane.push(page);
//	                } 
//	            }
		    }
		}
	}
	
	onPopTransitionEnded: { page.destroy(); }
}
