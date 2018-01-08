.pragma library

var thiz = this;

this.setTimeout = function(){
}

function validate(source) {
    var status = Qt.include(source);

    if (status.status !== 0) {
        console.warn("Failed to load: " + source);
        if (status.hasOwnProperty("exception")) {
            console.warn(status.exception.lineNumber + ":" + status.exception);
        }
        return false;
    }

    return true;
}

function create(source, fileName) {
    var status = Qt.include(source);

    if (status.status !== 0) {
        console.warn("Failed to load: " + source);
        if (status.hasOwnProperty("exception")) {
            console.warn(status.exception.lineNumber + ":" + status.exception);
        }

        return;
    }

    var res = ".pragma library\n";
    res += "Qt.include(\"" + fileName + "\")\n";
    for (var i in thiz) {
        for (var j in thiz[i]) {
            res += "var " + j + " = " + i +"." + j + ";\n";
        }
    }

    return res;
}
