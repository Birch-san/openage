#include "mycocoaeventfilter.h"

#include <QString>
#include <QDebug>
#include <QByteArray>
// #import <AppKit/AppKit.h>

bool CocoaNativeEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *)
{
	qInfo() << "NATIVE EVENT";
    if (eventType == "mac_generic_NSEvent") {
        // NSEvent *event = static_cast<NSEvent *>(message);
        // if ([event type] == NSKeyDown) {
        //     // Handle key event
        //     qDebug() << QString::fromNSString([event characters]);
        // }
        return true;
    }
    return false;
}