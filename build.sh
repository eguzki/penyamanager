
#!/bin/bash
#
# Simple build script for Unix
# This will invoke qmake and make at the same time ...
#

help()
{
    echo "usage: build.sh ARGS"
    echo "where ARGS can be:"
    cat << EOF
    clean           clean all generated files
    --release       do a Release build (not yet implemented)
EOF
}

checkBinary()
{
    set +e
    FIND=$(which $1)
    if [ ${#FIND} -eq 0 ]
    then
     echo "$1 is not installed ?"
     exit 1
    fi
    set -e
}

set -e # Returns error if any command returns error

# configuration options
# ... you can store you local modifications on a 'build.local' file

checkBinary "which"
#checkBinary "qmake"
checkBinary "make"
#QMAKE=$(which qmake)
QMAKE="/opt/Qt5.5.1/5.5/gcc_64/bin/qmake"
MAKE=$(which make)
#LRELEASE=$(which lrelease)
LRELEASE="/opt/Qt5.5.1/5.5/gcc_64/bin/lrelease"

PROJECT_NAME="penyamanager"
CURRENT_PATH="$( cd "$( dirname "$0" )" && pwd )"
TARGETPATH=$CURRENT_PATH/dist
PROJECT_PATH=$CURRENT_PATH/$PROJECT_NAME
CONF_APP=$PROJECT_PATH/penyamanagerconf.pro
USER_APP=$PROJECT_PATH/penyamanager.pro
ADMIN_APP=$PROJECT_PATH/penyamanageradmin.pro
QMAKE_FLAGS="-Wall"
DEBUG=yes
CLEAN=no

while [ "$1" ]
do
    case $1 in
    clean)
        CLEAN=yes
        ;;
    --release)
        DEBUG=no
        ;;
    --help)
        help
        exit 0
        ;;
    *)
        TARGET="$1";;
    esac
    shift
done


if [ "$CLEAN" = "yes" ] ; then
    echo "cleaning dist, buid-*"
    rm -rf dist
    rm -rf build-*
else
    [ -d $TARGETPATH ] || mkdir -p $TARGETPATH

    echo "** BUILD:: running \"$QMAKE\" and \"$MAKE $TARGET\" in $TARGETPATH [DEBUG build]"
    cd $TARGETPATH
    echo "** BUILD:: building \"$USER_APP\""
    $QMAKE $QMAKE_FLAGS $USER_APP
    echo "** BUILD:: making with: $MAKE**"
    $MAKE
    echo "** TRANSLATION:: making with: $LRELEASE**"
    $LRELEASE $USER_APP
    echo "** DEPLOY:: qm files**"
    mv $PROJECT_PATH/translations/*.qm $TARGETPATH
    echo "** BUILD:: building \"$ADMIN_APP\""
    $QMAKE $QMAKE_FLAGS $ADMIN_APP
    echo "** BUILD:: making with: $MAKE**"
    $MAKE
    echo "** TRANSLATION:: making with: $LRELEASE**"
    $LRELEASE $ADMIN_APP
    echo "** DEPLOY:: qm files**"
    mv $PROJECT_PATH/translations/*.qm $TARGETPATH
    echo "** BUILD:: building \"$CONF_APP\""
    $QMAKE $QMAKE_FLAGS $CONF_APP
    echo "** BUILD:: making with: $MAKE**"
    $MAKE
fi

