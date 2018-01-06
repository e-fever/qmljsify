var pkg = require('%{PACKAGE}');

if (typeof pkg === "function") {
    module.exports = {
        %{FUNCTION} : pkg
    };
} else {
    module.exports = pkg;
}

