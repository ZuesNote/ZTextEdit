#include "zimagetextobject.h"

#include <QtWidgets>
#include <QtSvg>

QSizeF ZImageTextObject::intrinsicSize(QTextDocument* doc, int posInDocument, const QTextFormat& format)
{
	QImage bufferedImage = qvariant_cast<QImage>(format.property(5));
	QSize size = bufferedImage.size();

	//todo 这里应该是用配置项里的东西
	return QSizeF(size);
}

void ZImageTextObject::drawObject(QPainter* painter, const QRectF& rect, QTextDocument* doc, int posInDocument, const QTextFormat& format)
{
	QImage bufferedImage = qvariant_cast<QImage>(format.property(5));

	painter->drawImage(rect, bufferedImage);
}
