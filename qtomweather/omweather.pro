VERSION = 1.0
TEMPLATE = subdirs
CONFIG += ordered

#SUBDIRS += core qt-qml meego-mpl
SUBDIRS += core qt-qml qtsetting

system(pkg-config --exists meego-panel) {
 SUBDIRS += meego-mpl
} 
