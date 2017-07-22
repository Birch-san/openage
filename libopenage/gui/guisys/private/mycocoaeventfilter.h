#include <QAbstractNativeEventFilter>
#include <QByteArray>

class CocoaNativeEventFilter : public QAbstractNativeEventFilter
{
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *) override;
};