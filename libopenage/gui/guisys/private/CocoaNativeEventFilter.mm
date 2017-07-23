#include "mycocoaeventfilter.h"

#include <QString>
#include <QDebug>
#include <QByteArray>
#include <AppKit/AppKit.h>

bool CocoaNativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
	//  << "; " << message
    if (eventType == "mac_generic_NSEvent") {
        NSEvent *event = static_cast<NSEvent *>(message);
        qInfo() << "NATIVE EVENT: " << eventType << "; " << [event type];
        // if ([event type] == NSKeyDown) {
        //     // Handle key event
        //     qDebug() << QString::fromNSString([event characters]);
        // }
        // return true;
    } else {
		qInfo() << "!NATIVE EVENT: " << eventType;
    }
    return false;
}