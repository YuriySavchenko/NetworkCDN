QT += widgets printsupport

HEADERS += \
        headers/Graph/edge.h \
        headers/Graph/node.h \
        headers/Graph/graphwidget.h \
        headers/Parse/jsonwriter.h \
        headers/Parse/jsonreader.h \
        headers/CDN/cdn.h \
        headers/CDN/matrix.h \
        headers/Info/instructions.h \
        headers/Info/histogramconstructor.h \
        headers/QCustomPlot/qcustomplot.h

SOURCES += \
        sources/Graph/edge.cpp \
        main.cpp \
        sources/Graph/node.cpp \
        sources/Graph/graphwidget.cpp \
        sources/Parse/jsonwriter.cpp \
        sources/Parse/jsonreader.cpp \
        sources/CDN/cdn.cpp \
        sources/CDN/matrix.cpp \
        sources/Info/instructions.cpp \
        sources/Info/histogramconstructor.cpp \
        sources/QCustomPlot/qcustomplot.cpp
