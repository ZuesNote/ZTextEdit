#include "ztextdocument.h"
#include "zimagetextobject.h"

ZTextDocument::ZTextDocument(QObject* parent) : QTextDocument(parent)
{
	init();
}

ZTextDocument::ZTextDocument(const QString& text, QObject* parent) : QTextDocument(parent)
{
	init();
}

ZTextDocument::~ZTextDocument()
{

}

void ZTextDocument::init()
{
	//注册下图片的图元类型
	QObject* imageInterface = new ZImageTextObject;
	imageInterface->setParent(this);
	this->documentLayout()->registerHandler(ImageTextFormat, imageInterface);
}
