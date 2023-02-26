#ifndef ZTEXTEDIT_H
#define ZTEXTEDIT_H

#include <QTextEdit>
#include <QPoint>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class ZTextDocument;

class ZTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	ZTextEdit(QWidget *parent = nullptr);
	~ZTextEdit();

	enum class BlockType
	{
		Normal = 0,
		Heading1 = 1
	};

public:
	void setDefaultHeading1Format();

private:
	//这个状态用于预处理的一些状态枚举。
	//为了更好地判断当前用户的行为，提前做出判断一些行为
	enum class InputState 
	{
		Normal,
		PreNumerSign,
		PreExclam, 
		AdjustToContents
	};
public:
	virtual void keyPressEvent(QKeyEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* e) override;

private:
	void initFormat();

	bool handledNumerSign(QKeyEvent* event);
	bool handledSpace(QKeyEvent* event);
	bool handledEnter(QKeyEvent* event);
	bool handledExclam(QKeyEvent* event);
	bool handledBracketLeft(QKeyEvent* event);
	bool handledBackspace(QKeyEvent* event);
	bool handledDelete(QKeyEvent* event);

private slots:
	void onPressEvent(const QPoint& pos);
	void onContentsChange(int from, int charsRemoved, int charsAdded);

signals:
	void sigPressEvent(const QPoint& pos);

private:
	InputState m_inputState = InputState::Normal;

	QTextCharFormat m_normalCharFormat;
	QTextCharFormat m_heading1CharFormat;
	QTextCharFormat m_heading2CharFormat;
	QTextCharFormat m_heading3CharFormat;
	QTextCharFormat m_heading4CharFormat;
	QTextCharFormat m_heading5CharFormat;
	QTextCharFormat m_heading6CharFormat;

	ZTextDocument* m_doc = nullptr;
};
#endif // ZTEXTEDIT_H
