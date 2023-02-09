#include "ztextedit.h"
#include "../core/ztextblockuserdata.h"

#include <QTextCursor>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextLayout>
#include <QAbstractTextDocumentLayout>
#include <QKeyEvent>

#if _DEBUG
#include <QDebug>
#endif


ZTextEdit::ZTextEdit(QWidget *parent)
	: QTextEdit(parent)
{
	initFormat();
}

ZTextEdit::~ZTextEdit()
{
}

void ZTextEdit::setDefaultHeading1Format()
{
}

void ZTextEdit::initFormat()
{
	{
		QFont font;
		font.setPixelSize(11);
		m_normalCharFormat.setFont(font);
	}
	{
		QFont font;
		font.setBold(true);
		font.setPixelSize(28);
		m_heading1CharFormat.setFont(font);
	}

}

bool ZTextEdit::handledNumerSign(QKeyEvent* event)
{
	//todo 获取block的状态
	QTextCursor textCursor = this->textCursor();
	QTextBlock textBlock = textCursor.block();

	int nPositionInBlock = textCursor.positionInBlock();
	QString strBlockText = textBlock.text();

	if (nPositionInBlock == 0)
	{
		textCursor.insertText("#");
		m_inputState = InputState::PreNumerSign;
		return true;
	}
	return false;
}

bool ZTextEdit::handledSpace(QKeyEvent* event)
{
	//todo 获取block的状态



	QTextCursor textCursor = this->textCursor();
	if (textCursor.isNull())
		return false;

	QTextBlock textBlock = textCursor.block();
	if (!textBlock.isValid())
		return false;

	QTextBlockUserData* blockUserData = textBlock.userData();
	ZTextBlockUserData* zBlockUserData = static_cast<ZTextBlockUserData*>(blockUserData);
	if (zBlockUserData != nullptr)
	{
		if (zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading1)
			return false;
	}

	int nPositionInBlock = textCursor.positionInBlock();
	int nBlockPosition = textBlock.position();
	QString strBlockText = textBlock.text();

	Qt::KeyboardModifiers modifiers = event->modifiers();
	if (modifiers == Qt::NoModifier)
	{
		if (m_inputState == InputState::PreNumerSign && strBlockText.startsWith("#"))
		{
			m_inputState = InputState::Normal;

			textCursor.beginEditBlock();

			textCursor.setPosition(nBlockPosition);
			textCursor.setPosition(nBlockPosition + 1, QTextCursor::KeepAnchor);
			textCursor.removeSelectedText();

			//setBlockFormat必须得清空以后才能设置成功
			textCursor.setBlockCharFormat(m_heading1CharFormat);

			textCursor.endEditBlock();

			ZTextBlockUserData* userData = new ZTextBlockUserData(ZTextBlockUserData::TextBlockType::Heading1);
			textBlock.setUserData(userData);
			return true;
		}
	}
	return false;
}

bool ZTextEdit::handledEnter(QKeyEvent* event)
{
	return false;
}



void ZTextEdit::keyPressEvent(QKeyEvent* event)
{
	bool bHandled = false;

	const int key = event->key();
	switch (key) 
	{
	case Qt::Key_NumberSign: //#
		bHandled = handledNumerSign(event);
		break;
	case Qt::Key_Space:
		bHandled = handledSpace(event);
	case Qt::Key_Tab:
		break;
	case Qt::Key_Backtab:
		break;
	case Qt::Key_Return:
		Q_FALLTHROUGH();
	case Qt::Key_Enter:
		bHandled = handledEnter(event);
		break;
	default:
		break;
	}

	if (!bHandled)
		return QTextEdit::keyPressEvent(event);
}

