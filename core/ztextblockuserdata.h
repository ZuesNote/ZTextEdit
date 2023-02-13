#ifndef ZTEXTBLOCKUSERDATA_H
#define ZTEXTBLOCKUSERDATA_H

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
		Heading5 = 5,
		Heading6 = 6,
		Code = 7,
		ImageText = 8,
		Image = 9,
	};
	explicit ZTextBlockUserData(TextBlockType type);
	virtual ~ZTextBlockUserData();

	ZTextBlockUserData::TextBlockType Type();
private:
	TextBlockType m_textBlockType = TextBlockType::Normal;
};
#endif // Z_TEXTBLOCKDATA
