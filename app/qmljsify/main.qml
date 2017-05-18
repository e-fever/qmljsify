import QtQuick 2.3
import QtQuick.Window 2.2
import QtMultimedia 5.5
import QtQuick.Controls 1.4
import QuickFlux 1.1
import Qmljsify.constants 1.0
import Qmljsify.actions 1.0
import Qmljsify.stores 1.0
import Qmljsify.middlewares 1.0

Window {
    id: mainWindow
    visible: true
    width: 480
    height: 640

    MiddlewareList {
        id : middleware
        applyTarget: AppActions
        SystemMiddleware {
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            AppActions.quitApp();
        }
    }

    Text {
        text: qsTr(MainStore.text)
        anchors.centerIn: parent
    }

}
