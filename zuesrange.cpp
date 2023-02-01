#include "zuesrange.h"

#include <QDebug>

namespace
{
	constexpr int NormalFontSize = 22;
	constexpr int Heading1FontSize = 48;
	constexpr int Heading2FontSize = 32;
	constexpr int Heading3FontSize = 28;
	constexpr int Heading4FontSize = 22;
	constexpr int CodeFontSize = 10;
}

class KTextBlockData : public QTextBlockUserData
{
public:
	enum class MDBlockType
	{
		NormalText = 0,
		Heading1 = 1,
		Heading2 = 2,
		Heading3 = 3,
		Heading4 = 4,
		Code = 5,
		Image = 6,
	};
	KTextBlockData(int type)
	{
		m_type = type;
	}
	virtual ~KTextBlockData()
	{

	}

	int m_type = 1;
};


ZuesRange::ZuesRange(QObject *parent)
	: QObject(parent)
{

}

ZuesRange::ZuesRange(QTextCursor* textCursor, QTextBlock* textBlock) : m_textCursor(textCursor), m_textBlock(textBlock)
{
}

ZuesRange::~ZuesRange()
{
}

bool ZuesRange::InitRange()
{
	if (m_textBlock == nullptr || m_textCursor == nullptr)
		return false;

	QTextBlockUserData* userData = m_textBlock->userData();
	KTextBlockData* kUserData = static_cast<KTextBlockData*>(userData);
	if (kUserData != nullptr)
	{
		qDebug() << "test---" << kUserData->m_type;
	}
	int nPosition = m_textCursor->position();
	int npositionInBlock = m_textCursor->positionInBlock();

	if (m_textCursor->positionInBlock() == 2 && m_textBlock->text().startsWith("# "))
	{
		KTextBlockData* userData = new KTextBlockData(2);
		m_textBlock->setUserData(userData);

		m_textCursor->beginEditBlock();
		int nBlock = m_textBlock->position();
		int nTextCur = m_textCursor->position();
		m_textCursor->setPosition(m_textBlock->position());
		m_textCursor->setPosition(m_textBlock->position() + 2, QTextCursor::KeepAnchor);
		m_textCursor->removeSelectedText();

		QFont font;
		font.setBold(true);
		font.setPixelSize(Heading1FontSize);

		QTextCharFormat charFormat = m_textCursor->charFormat();
		charFormat.setFont(font);
		
		m_textCursor->setBlockCharFormat(charFormat);
		m_textCursor->endEditBlock();
	}

	if (m_textCursor->positionInBlock() == 3 && m_textBlock->text().startsWith("## "))
	{
		KTextBlockData* userData = new KTextBlockData(2);
		m_textBlock->setUserData(userData);

		m_textCursor->beginEditBlock();
		int nBlock = m_textBlock->position();
		int nTextCur = m_textCursor->position();
		m_textCursor->setPosition(m_textBlock->position());
		m_textCursor->setPosition(m_textBlock->position() + 3, QTextCursor::KeepAnchor);
		m_textCursor->removeSelectedText();

		QFont font;
		font.setBold(true);
		font.setPixelSize(Heading2FontSize);

		QTextCharFormat charFormat = m_textCursor->charFormat();
		charFormat.setFont(font);

		m_textCursor->setBlockCharFormat(charFormat);
		m_textCursor->endEditBlock();
	}

	return false;
}

