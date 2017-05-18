import QtQuick 2.0
import "./wrappercreator.js" as Script

QtObject {
    objectName: "Main"

    function create(source, fileName) {
        return Script.create(source, fileName);
    }
}
