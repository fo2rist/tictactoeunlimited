// Drilldown navigation project template
import bb.cascades 1.0

NavigationPane {
    id: navigationPane
    
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
    
    onCreationCompleted: {
        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
        //DEBUG
        playButton.clicked()
    }
    
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
	            
		        Button {
		            id: settingsButton
	                text: "Settings"
	                onClicked: {
	                    var page = settingsPageDefinition.createObject();
	                    navigationPane.push(page);
	                } 
	            }
		    }
		}
	}
	
	onPopTransitionEnded: { page.destroy(); }
}
