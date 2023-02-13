#ifndef ZIMAGETEXTOBJECT_H
#define ZIMAGETEXTOBJECT_H

#include <QTextObjectInterface>

QT_BEGIN_NAMESPACE
class QTextDocument;
class QTextFormat;
class QPainter;
class QRectF;
class QSizeF;
QT_END_NAMESPACE

class ZImageTextObject : public QObject, public QTextObjectInterface
{
	Q_OBJECT
	Q_INTERFACES(QTextObjectInterface)
public:
	QSizeF intrinsicSize(QTextDocument* doc, int posInDocument, const QTextFormat& format) override;
	void drawObject(QPainter* painter, const QRectF& rect, QTextDocument* doc, int posInDocument, const QTextFormat& format) override;

};
#endif