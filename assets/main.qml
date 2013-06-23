import bb.cascades 1.0

NavigationPane {
    id: navigationPane

    onPopTransitionEnded: {
        page.destroy();
    }

    attachedObjects: [
        ComponentDefinition {
            id: gamePageDefinition
            source: "GameView.qml"
        },
        ComponentDefinition {
            id: aboutPageDefinition
            source: "AboutView.qml"
        },
        ComponentDefinition {
            id: btSetupPageDefinition
            source: "BtSetupView.qml"
        },
        ComponentDefinition {
            id: settingsPageDefinition
            source: "SettingsView.qml"
        }
    ]

    peekEnabled: false

    Page {
        Container {
            layout: DockLayout {
            }

            // Background ImageView
            ImageView {
                imageSource: "asset:///images/bg.png"
            }

            Container {
                id: menuContainer
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill

                ImageView {
                    imageSource: "asset:///images/tictactoe.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    opacity: 0.4
                    scalingMethod: ScalingMethod.AspectFit
                }
                
                ImageButton {
                    id: playButton_6_6
                    defaultImageSource: "asset:///images/6x6.png"
                    pressedImageSource: "asset:///images/6x6_pressed.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    onClicked: {
                        var page = gamePageDefinition.createObject();
                        page.gameWidth = 6;
                        page.gameHeight = 6;
                        page.initializeGame(hotSeatEnabledToggle.checked);
                        navigationPane.push(page);
                    }
                }
                ImageButton {
                    id: playButton_6_10
                    defaultImageSource: "asset:///images/6x10.png"
                    pressedImageSource: "asset:///images/6x10_pressed.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    onClicked: {
                        var page = gamePageDefinition.createObject();
                        page.gameWidth = 6;
                        page.gameHeight = 10;
                        page.initializeGame(hotSeatEnabledToggle.checked);
                        navigationPane.push(page);
                    }
                }
                ImageButton {
                    id: playButton_8_14
                    defaultImageSource: "asset:///images/8x14.png"
                    pressedImageSource: "asset:///images/8x14_pressed.png"
                    horizontalAlignment: HorizontalAlignment.Center
                    onClicked: {
                        var page = gamePageDefinition.createObject();
                        page.gameWidth = 8;
                        page.gameHeight = 14;
                        page.initializeGame(hotSeatEnabledToggle.checked);
                        navigationPane.push(page);
                    }
                }
//                ImageButton {
//                    id: playViaBtButton
//                    defaultImageSource: "asset:///images/m_vs_m.png"
//                    pressedImageSource: "asset:///images/m_vs_m.png"
//                    horizontalAlignment: HorizontalAlignment.Center
//                    topMargin: 120
//                    onClicked: {
//                        var page = btSetupPageDefinition.createObject();
//                        navigationPane.push(page);
//                    }
//                }
                //Separator
                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1
                    }
                }

                //                Button {
                //                          id: settingsButton
                //                      text: "Settings"
                //                      onClicked: {
                //                          var page = settingsPageDefinition.createObject();
                //                          navigationPane.push(page);
                //                      }
                //                }
            }

            Container {
                layout: DockLayout {}

                verticalAlignment: VerticalAlignment.Bottom
                horizontalAlignment: HorizontalAlignment.Fill
                rightPadding: 30
                bottomPadding: 10

                ImageView {
                    imageSource: "asset:///images/unlimited.png"
                    opacity: 0.2
                    maxHeight: 60
                    scalingMethod: ScalingMethod.AspectFit
                    horizontalAlignment: HorizontalAlignment.Center
                }

                Container {
                    layout: DockLayout {}
                    horizontalAlignment: HorizontalAlignment.Left

                    ImageView {
                        id: hotSeatImage
                        imageSource: "asset:///images/man_vs_ai.png"
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                    //Ivisible real button that changes image
                    ToggleButton {
                        id: hotSeatEnabledToggle
                        opacity: 0.0
                        checked: false
                        horizontalAlignment: HorizontalAlignment.Center
                        onCheckedChanged: {
                            if (checked)
                            	hotSeatImage.setImageSource("asset:///images/man_vs_man.png");
                            else
                            	hotSeatImage.setImageSource("asset:///images/man_vs_ai.png");
                        }
                    }
                }

                ImageButton {
                    defaultImageSource: "asset:///images/info.png"
                    verticalAlignment: VerticalAlignment.Bottom
                    horizontalAlignment: HorizontalAlignment.Right
                    preferredHeight: 70
                    preferredWidth: 70
                    onClicked: {
                        var page = aboutPageDefinition.createObject();
                        navigationPane.push(page);
                    }
                }
            }
        }
    }
}
