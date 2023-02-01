#ifndef Zues_RANGE
#define Zues_RANGE

#include <QObject>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextBlock>

class ZuesRange : public QObject
{
	Q_OBJECT
public:
	ZuesRange(QObject *parent = nullptr);
	ZuesRange(QTextCursor* textCursor = nullptr, QTextBlock* textBlock = nullptr);
	~ZuesRange();

public:
	bool InitRange();
	QTextCursor* test() { return m_textCursor; }

private:
	QTextCursor* m_textCursor = nullptr;
	QTextBlock* m_textBlock = nullptr;
};
#endif // Zues_RANGE
