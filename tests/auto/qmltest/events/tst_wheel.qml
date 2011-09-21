import QtQuick 2.0
import QtTest 1.0

Rectangle {
    id:top
    width: 400
    height: 400
    color: "gray"

    Flickable {
        id: flick
        objectName: "flick"
        anchors.fill: parent
        contentWidth: 800
        contentHeight: 800

        Rectangle {
            width: flick.contentWidth
            height: flick.contentHeight
            color: "red"
            Rectangle {
                width: 50; height: 50; color: "blue"
                anchors.centerIn: parent
            }
        }
    }
    TestCase {
        name: "WheelEvents"
        when: windowShown       // Must have this line for events to work.

        function test_wheel() {
            //mouseWheel(item, x, y, delta, buttons = Qt.NoButton, modifiers = Qt.NoModifier, delay = -1, orientation = Qt.Vertical)
            mouseWheel(flick, 200, 200, -120, Qt.NoButton, Qt.NoModifier, -1, Qt.Vertical);
            wait(1000);
            verify(flick.contentY > 0);
            verify(flick.contentX == 0);
            flick.contentY = 0;
            verify(flick.contentY == 0);
            mouseWheel(flick, 200, 200, -120, Qt.NoButton, Qt.NoModifier, -1, Qt.Horizontal);
            wait(1000);
            verify(flick.contentX > 0);
            verify(flick.contentY == 0);
        }

    }

}