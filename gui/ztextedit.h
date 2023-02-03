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
};
#endif // Z_TEXT_EDIT
