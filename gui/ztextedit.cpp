﻿#include "ztextedit.h"
#include "../core/ztextblockuserdata.h"
#include "../core/ztextdocument.h"

#include <QTextCursor>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextLayout>
#include <QAbstractTextDocumentLayout>
#include <QKeyEvent>

#include <QDebug>


ZTextEdit::ZTextEdit(QWidget *parent)
	: QTextEdit(parent)
{
	initFormat();
	m_doc = new ZTextDocument(this);
	setDocument(m_doc);

	connect(this, &ZTextEdit::sigPressEvent, this, &ZTextEdit::onPressEvent);

	connect(m_doc, &QTextDocument::contentsChange, this, &ZTextEdit::onContentsChange);
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
		font.setPixelSize(18);
		font.setFamily(QString::fromUtf8("等线"));
		m_normalCharFormat.setFont(font);
		this->document()->setDefaultFont(font);
	}
	{
		QFont font;
		font.setBold(true);
		font.setPixelSize(28);
		m_heading1CharFormat.setFont(font);
		m_heading1CharFormat.setBackground(Qt::red);
		m_heading1CharFormat.setProperty(QTextFormat::AnchorHref, "svgBufferImage");
	}
	{
		QFont font;
		font.setBold(true);
		font.setPixelSize(27);
		m_heading2CharFormat.setFont(font);
		m_heading2CharFormat.setBackground(Qt::green);
	}
	{
		QFont font;
		font.setBold(true);
		font.setPixelSize(26);
		m_heading3CharFormat.setFont(font);
		m_heading3CharFormat.setBackground(Qt::blue);
	}

	{
		QFont font;
		font.setBold(true);
		font.setPixelSize(25);
		m_heading4CharFormat.setFont(font);
	}

	{
		QFont font;
		font.setBold(true);
		font.setPixelSize(24);
		m_heading5CharFormat.setFont(font);
	}

	{
		QFont font;
		font.setBold(true);
		font.setPixelSize(23);
		m_heading6CharFormat.setFont(font);
	}
}

void ZTextEdit::onPressEvent(const QPoint& pos)
{
	QTextFormat textFormat = m_doc->documentLayout()->formatAt(pos);
	if (textFormat.isImageFormat())
	{
//		qDebug() << textFormat;
		QTextImageFormat imgFormat = textFormat.toImageFormat();
		qDebug() << imgFormat.name();
	}
}

//这个用于处理关联关系的block
void ZTextEdit::onContentsChange(int from, int charsRemoved, int charsAdded)
{
	//from代表的是QTextCursor绝对位置。可以通过这个东西来查找Block.
	//charsRemoved代表的是删除的个数。
	//charsAdded代表的是增加的个数。
	qDebug() << from << " " << charsRemoved << " " << charsAdded;
	QTextBlock block = m_doc->findBlock(from);
	qDebug() << block.text() << endl;
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
		//if (zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading1 
		//	|| zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading2
		//	|| zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading3
		//	)
		//	return false;
	}

	int nPositionInBlock = textCursor.positionInBlock();
	int nBlockPosition = textBlock.position();
	QString strBlockText = textBlock.text();

	Qt::KeyboardModifiers modifiers = event->modifiers();
	if (modifiers == Qt::NoModifier)
	{
		if (m_inputState == InputState::PreNumerSign && nPositionInBlock == 1 && strBlockText.startsWith("#"))
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
		if (m_inputState == InputState::PreNumerSign && nPositionInBlock == 2 && strBlockText.startsWith("##"))
		{
			m_inputState = InputState::Normal;

			textCursor.beginEditBlock();

			textCursor.setPosition(nBlockPosition);
			textCursor.setPosition(nBlockPosition + 2, QTextCursor::KeepAnchor);
			textCursor.removeSelectedText();

			//setBlockFormat必须得清空以后才能设置成功
			textCursor.setBlockCharFormat(m_heading2CharFormat);

			textCursor.endEditBlock();

			ZTextBlockUserData* userData = new ZTextBlockUserData(ZTextBlockUserData::TextBlockType::Heading2);
			textBlock.setUserData(userData);

			return true;
		}
		if (m_inputState == InputState::PreNumerSign && nPositionInBlock == 3 && strBlockText.startsWith("###"))
		{
			m_inputState = InputState::Normal;

			textCursor.beginEditBlock();

			textCursor.setPosition(nBlockPosition);
			textCursor.setPosition(nBlockPosition + 3, QTextCursor::KeepAnchor);
			textCursor.removeSelectedText();

			//setBlockFormat必须得清空以后才能设置成功
			textCursor.setBlockCharFormat(m_heading3CharFormat);

			textCursor.endEditBlock();

			ZTextBlockUserData* userData = new ZTextBlockUserData(ZTextBlockUserData::TextBlockType::Heading3);
			textBlock.setUserData(userData);

			return true;
		}
		if (m_inputState == InputState::PreNumerSign && nPositionInBlock == 4 && strBlockText.startsWith("####"))
		{
			m_inputState = InputState::Normal;

			textCursor.beginEditBlock();

			textCursor.setPosition(nBlockPosition);
			textCursor.setPosition(nBlockPosition + 4, QTextCursor::KeepAnchor);
			textCursor.removeSelectedText();

			//setBlockFormat必须得清空以后才能设置成功
			textCursor.setBlockCharFormat(m_heading4CharFormat);

			textCursor.endEditBlock();

			ZTextBlockUserData* userData = new ZTextBlockUserData(ZTextBlockUserData::TextBlockType::Heading4);
			textBlock.setUserData(userData);

			return true;
		}
		if (m_inputState == InputState::PreNumerSign && nPositionInBlock == 5 && strBlockText.startsWith("#####"))
		{
			m_inputState = InputState::Normal;

			textCursor.beginEditBlock();

			textCursor.setPosition(nBlockPosition);
			textCursor.setPosition(nBlockPosition + 5, QTextCursor::KeepAnchor);
			textCursor.removeSelectedText();

			//setBlockFormat必须得清空以后才能设置成功
			textCursor.setBlockCharFormat(m_heading5CharFormat);

			textCursor.endEditBlock();

			ZTextBlockUserData* userData = new ZTextBlockUserData(ZTextBlockUserData::TextBlockType::Heading5);
			textBlock.setUserData(userData);

			return true;
		}
		if (m_inputState == InputState::PreNumerSign && nPositionInBlock == 6 && strBlockText.startsWith("######"))
		{
			m_inputState = InputState::Normal;

			textCursor.beginEditBlock();

			textCursor.setPosition(nBlockPosition);
			textCursor.setPosition(nBlockPosition + 6, QTextCursor::KeepAnchor);
			textCursor.removeSelectedText();

			//setBlockFormat必须得清空以后才能设置成功
			textCursor.setBlockCharFormat(m_heading6CharFormat);

			textCursor.endEditBlock();

			ZTextBlockUserData* userData = new ZTextBlockUserData(ZTextBlockUserData::TextBlockType::Heading6);
			textBlock.setUserData(userData);

			return true;
		}

	}
	return false;
}

bool ZTextEdit::handledEnter(QKeyEvent* event)
{
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
		if (zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading1
			|| zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading2
			|| zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading3
			|| zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading4
			|| zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading5
			|| zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading6
			)
		{
			textCursor.insertBlock(QTextBlockFormat(), m_normalCharFormat);
			return true;
		}
	}

	return false;
}

bool ZTextEdit::handledExclam(QKeyEvent *event)
{
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

	}

	int nPositionInBlock = textCursor.positionInBlock();
	int nBlockPosition = textBlock.position();
	QString strBlockText = textBlock.text();

	if (nPositionInBlock == 0)
	{
		textCursor.insertText("!");
		m_inputState = InputState::PreExclam;
		return true;		
	}

	return false;
}

bool ZTextEdit::handledBracketLeft(QKeyEvent *event)
{
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
		//if (zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading1
		//	|| zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading2
		//	|| zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Heading3
		//	)
		//	return false;
	}

	int nPositionInBlock = textCursor.positionInBlock();
	int nBlockPosition = textBlock.position();
	QString strBlockText = textBlock.text();

	Qt::KeyboardModifiers modifiers = event->modifiers();
	if (modifiers == Qt::NoModifier)
	{
		if (m_inputState == InputState::PreExclam && nPositionInBlock == 1 && strBlockText.startsWith("!"))
		{
			textCursor.insertText("[name](./image.png)");
			ZTextBlockUserData* imageTextData = new ZTextBlockUserData(ZTextBlockUserData::TextBlockType::ImageText);
			textBlock.setUserData(imageTextData);

			textCursor.insertBlock(QTextBlockFormat(), m_normalCharFormat);

//			QTextCharFormat imageCharFormat;
			QTextImageFormat imageCharFormat;
			imageCharFormat.setName("D:\\1.png");
			imageCharFormat.setWidth(this->width());
			textCursor.insertImage(imageCharFormat);

			QTextBlock imgBlock = textCursor.block();

//			ZTextBlockUserData* imageData = new ZTextBlockUserData(ZTextBlockUserData::TextBlockType::Image);
//			imgBlock.setUserData(imageData);
			return true;
		}
		else
		{
			//插入图片
			QTextCharFormat imageCharFormat;
			imageCharFormat.setAnchorHref("https://www.wps.cn");
			textCursor.insertText("[name](https://www.wps.cn)", imageCharFormat);
			return true;
		}
	}
	return false;
}

bool ZTextEdit::handledBackspace(QKeyEvent* event)
{
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
		if (zBlockUserData->Type() == ZTextBlockUserData::TextBlockType::Image)
			return true;
	}

	return false;
}

bool ZTextEdit::handledDelete(QKeyEvent* event)
{


	return false;
}



void ZTextEdit::keyPressEvent(QKeyEvent* event)
{
	bool bHandled = false;

	const int key = event->key();
	Qt::Key keyType = static_cast<Qt::Key>(key);
	QString keyName = event->text();
	qDebug()<<"keyPress-----:"<<keyName;

	switch (key) 
	{
	case Qt::Key_NumberSign: //#
		bHandled = handledNumerSign(event);
		break;
	case Qt::Key_Space:
		bHandled = handledSpace(event);
		break;
	case Qt::Key_Exclam: // ! 图片
		bHandled = handledExclam(event);
		break;
	case Qt::Key_BracketLeft: // [
		bHandled = handledBracketLeft(event);
		break;
	case Qt::Key_Backspace:
		bHandled = handledBackspace(event);
		break;
	case Qt::Key_QuoteLeft: //公式的"`",但是发现一个奇怪的`·`这个符号的案件并没有监测到
		break;
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

void ZTextEdit::mouseReleaseEvent(QMouseEvent* e)
{
	auto block = this->document()->documentLayout()->anchorAt(e->pos());
//	auto block1 = this->document()->documentLayout()->anchorAt(e->globalPos());
//	auto block2 = this->document()->documentLayout()->anchorAt(e->localPos());
//	qDebug() << block;
//	qDebug() << block1;
//	qDebug() << block2;
//	QTextFormat formatAt(const QPointF & pos) const;
//	QTextBlock blockWithMarkerAt(const QPointF & pos) const;
	emit sigPressEvent(e->pos());
	QTextEdit::mousePressEvent(e);
}

void ZTextEdit::mouseMoveEvent(QMouseEvent* e)
{
	QTextFormat textFormat = m_doc->documentLayout()->formatAt(e->pos());
	if (textFormat.hasProperty(QTextFormat::AnchorHref))
	{
		QVariant var = textFormat.property(QTextFormat::AnchorHref);
		qDebug() << var.toString();
//		QCursor cur(Qt::ArrowCursor);//这个不管用
//		setCursor(cur);
//		return;
	}
	QTextEdit::mouseMoveEvent(e);
}

