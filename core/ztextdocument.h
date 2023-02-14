#ifndef ZTEXTDOCUMENT_H
#define ZTEXTDOCUMENT_H

#include <QTextDocument>
#include <QTextFormat>

class ZTextDocument : public QTextDocument
{
	Q_OBJECT
public:
	enum 
	{ 
		ImageTextFormat = QTextFormat::UserObject + 1,
	};

	enum
	{
		ImageProperties = QTextFormat::UserProperty + 1,
	};

public:
	explicit ZTextDocument(QObject* parent = nullptr);
	explicit ZTextDocument(const QString& text, QObject* parent = nullptr);
	~ZTextDocument();

private:
	void init();

};
#endif //ZTEXTDOCUMENT_H