#ifndef Z_TEXTBLOCKUSERDATA
#define Z_TEXTBLOCKUSERDATA

#include <QTextBlockUserData>

class ZTextBlockUserData : public QTextBlockUserData
{
public:
	enum class TextBlockType
	{
		Normal = 0,
		Heading1 = 1,
		Heading2 = 2,
		Heading3 = 3,
		Heading4 = 4,
		Code = 5,
		Image = 6,
	};
	explicit ZTextBlockUserData(TextBlockType type);
	virtual ~ZTextBlockUserData();

	ZTextBlockUserData::TextBlockType Type();
private:
	TextBlockType m_textBlockType = TextBlockType::Normal;
};
#endif // Z_TEXTBLOCKDATA
