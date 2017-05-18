unix:!android {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
            target.path = /opt/$${TARGET}/bin
        }
        export(target.path)
    }
    INSTALLS += target
}

export(INSTALLS)

mac {
    # Quick and dirty way to create
    APP=$${OUT_PWD}/$${TARGET}.app
    DMG_FOLDER=$${OUT_PWD}/dmg

    dmg.target = dmg
    dmg.commands = macdeployqt $${APP}; mkdir -p $${DMG_FOLDER}; cp -a $${APP} $${DMG_FOLDER}; cd $${OUT_PWD}; hdiutil create -srcfolder dmg -volname uforobot -fs HFS+ -fsargs "-c c=64,a=16,e=16" -format UDZO -imagekey zlib-level=9 $${TARGET}.dmg
    dmg.depends = $${APP}

    QMAKE_EXTRA_TARGETS += dmg
}


