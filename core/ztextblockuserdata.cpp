#include "ztextblockuserdata.h"

ZTextBlockUserData::ZTextBlockUserData(TextBlockType type) : m_textBlockType(type)
{

}

ZTextBlockUserData::~ZTextBlockUserData()
{
	
}

ZTextBlockUserData::TextBlockType ZTextBlockUserData::Type()
{
	return m_textBlockType;
}
