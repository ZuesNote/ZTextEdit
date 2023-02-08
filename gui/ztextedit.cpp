#include "ztextedit.h"

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

}

ZTextEdit::~ZTextEdit()
{
}

bool ZTextEdit::handledNumerSign(QKeyEvent* event)
{
	//todo 获取block的状态
	QTextCursor textCursor = this->textCursor();
	QTextBlock textBlock = textCursor.block();

	int nPositionInBlock = textCursor.positionInBlock();
	QString strBlockText = textBlock.text();

	if (strBlockText.isEmpty())
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
	QTextBlock textBlock = textCursor.block();

	int nPositionInBlock = textCursor.positionInBlock();
	int nBlockPosition = textBlock.position();
	QString strBlockText = textBlock.text();

	Qt::KeyboardModifiers modifiers = event->modifiers();
	if (modifiers == Qt::NoModifier)
	{
		if (m_inputState == InputState::PreNumerSign && strBlockText.size() == 1 && strBlockText == "#")
		{
			m_inputState = InputState::Normal;

			textCursor.beginEditBlock();
			textCursor.insertText(" ");

			textCursor.setPosition(nBlockPosition);
			textCursor.setPosition(nBlockPosition + 2, QTextCursor::KeepAnchor);


			//setBlockFormat必须得清空以后才能设置成功

			QTextCharFormat charFormat = textCursor.charFormat();
			charFormat.setFontPointSize(48);
			charFormat.setFontStretch(60);
			textCursor.setCharFormat(charFormat);

			textCursor.endEditBlock();

			return true;
			//this->setTextCursor(textCursor);
			//todo 处理标题1的format
		}
	}
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
		break;
	default:
		break;
	}

	if (!bHandled)
		return QTextEdit::keyPressEvent(event);
}

