#ifndef ZIMAGETEXTOBJECT_H
#define ZIMAGETEXTOBJECT_H

/*
此类本来想平替成QTextImageFormat，但是发现常规的Image不支持一些东西
本来想继承QTextImage，发现他只能设置名字，不支持设置内存数据，网络下载下来的图片得支持内存级别的设置QImageData类型的接口
这里统一用QImage来搞定

- 网络图片
- SVG支持
- todo

*/

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