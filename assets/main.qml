// Navigation pane project template
import bb.cascades 1.0

NavigationPane {
    id: navigationPane
    /*onPopTransitionEnded: {
        page.destroy();
    }*/
    Page {
        actions: [
            ActionItem {
                title: "Refresh"
                onTriggered: app.initiateRequest()
                ActionBar.placement: ActionBarPlacement.OnBar
            }
        ]
        // page with a picture thumbnail
        content: Container {
            background: Color.Black
            layout: DockLayout {
            }
            ListView {
                objectName: "twunches"
                verticalAlignment: VerticalAlignment.Top
                horizontalAlignment: HorizontalAlignment.Center
                
                layout: FlowListLayout {
                            
                }
                dataModel: XmlDataModel {
                    source: "twunches.xml"
                }
                listItemComponents: [
                    ListItemComponent {
                        type: "twunches"
                        Header {
                            topMargin: 8
                            title: "Twunches"
                            subtitle: (ListItem.initialized ? ListItem.view.dataModel.childCount(ListItem.indexPath) : 0);
                        }
                    },
                    ListItemComponent {
                        type: "twunch"
                        StandardListItem {
                            title: ListItemData.title
                        }
                    }
                ]
            }
            ActivityIndicator {
                objectName: "indicator"
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                preferredWidth: 200
                preferredHeight: 200
            }
            /*Button {
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                text: qsTr("Show detail")
                imageSource: "asset:///images/picture1thumb.png"
                onClicked: {
                    // show detail page when the button is clicked
                    var page = getSecondPage();
                    console.debug("pushing detail " + page)
                    navigationPane.push(page);
                }
                property Page secondPage
                function getSecondPage() {
                    if (! secondPage) {
                        secondPage = secondPageDefinition.createObject();
                    }
                    return secondPage;
                }
                attachedObjects: [
                    ComponentDefinition {
                        id: secondPageDefinition
                        source: "DetailsPage.qml"
                    }
                ]
            }*/
        }
    }
    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        console.log("NavigationPane - onCreationCompleted()");

        // enable layout to adapt to the device rotation
        // don't forget to enable screen rotation in bar-bescriptor.xml (Application->Orientation->Auto-orient)
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
}
