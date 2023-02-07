#ifndef Z_TEXT_EDIT
#define Z_TEXT_EDIT

#include <QTextEdit>

class QTextDocument;

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
private:
	enum class InputState 
	{
		Normal,
		PreNumerSign,
		AdjustToContents
	};
public:
	virtual void keyPressEvent(QKeyEvent* event) override;

private:
	bool handledNumerSign(QKeyEvent* event);
	bool handledSpace(QKeyEvent* event);


private:
	InputState m_inputState = InputState::Normal;
};
#endif // Z_TEXT_EDIT
