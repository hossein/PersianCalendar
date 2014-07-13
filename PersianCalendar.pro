HEADERS += \
    CalendarDialog.h \
    CtDate.h \
    CalendarWidget.h \
    CtCommon.h

SOURCES += \
    jalali.c \
    CalendarDialog.cpp \
    CtDate.cpp \
    CalendarWidget.cpp \
    main.cpp

FORMS += \
    CalendarDialog.ui

RESOURCES += \
    PersianCalendarResources.qrc

win32 {
    RC_FILE = res/PersianCalendarInfo.rc
}

OTHER_FILES += \
    res/PersianCalendarInfo.rc
