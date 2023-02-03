#include "zrange.h"

#include <QDebug>

// namespace
// {
// 	constexpr int NormalFontSize = 22;
// 	constexpr int Heading1FontSize = 48;
// 	constexpr int Heading2FontSize = 32;
// 	constexpr int Heading3FontSize = 28;
// 	constexpr int Heading4FontSize = 22;
// 	constexpr int CodeFontSize = 10;
// }

// class KTextBlockData : public QTextBlockUserData
// {
// public:
// 	enum class MDBlockType
// 	{
// 		NormalText = 0,
// 		Heading1 = 1,
// 		Heading2 = 2,
// 		Heading3 = 3,
// 		Heading4 = 4,
// 		Code = 5,
// 		Image = 6,
// 	};
// 	KTextBlockData(int type)
// 	{
// 		m_type = type;
// 	}
// 	virtual ~KTextBlockData()
// 	{

// 	}

// 	int m_type = 1;
// };


ZRange::ZRange(QObject *parent)
	: QObject(parent)
{

}

ZRange::~ZRange()
{
}
