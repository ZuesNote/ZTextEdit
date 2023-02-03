#ifndef ZRANGE
#define ZRANGE

#include <QObject>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextBlock>

class ZRange : public QObject
{
	Q_OBJECT
public:
	ZRange(QObject *parent = nullptr);
	~ZRange();
};
#endif // ZRANGE
