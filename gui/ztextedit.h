#ifndef Z_TEXT_EDIT
#define Z_TEXT_EDIT

#include <QTextEdit>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

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
	enum class InputState 
	{
		Normal,
		PreNumerSign,
		PreExclam, 
		AdjustToContents
	};
public:
	virtual void keyPressEvent(QKeyEvent* event) override;

private:
	void initFormat();

	bool handledNumerSign(QKeyEvent* event);
	bool handledSpace(QKeyEvent* event);
	bool handledEnter(QKeyEvent* event);
	bool handledExclam(QKeyEvent* event);
	bool handledBracketLeft(QKeyEvent* event);

private:
	InputState m_inputState = InputState::Normal;

	QTextCharFormat m_normalCharFormat;
	QTextCharFormat m_heading1CharFormat;
	QTextCharFormat m_heading2CharFormat;
	QTextCharFormat m_heading3CharFormat;
	QTextCharFormat m_heading4CharFormat;
	QTextCharFormat m_heading5CharFormat;
	QTextCharFormat m_heading6CharFormat;
};
#endif // Z_TEXT_EDIT
