#include "zuesedit.h"

#include <QTextCursor>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextLayout>
#include <QAbstractTextDocumentLayout>

#include "zuesrange.h"
#if _DEBUG
#include <QDebug>
#endif


ZuesEdit::ZuesEdit(QWidget *parent)
	: QTextEdit(parent)
{
	m_doc = this->document();

	connect(this, &QTextEdit::textChanged, this, &ZuesEdit::onDealInput);
	connect(m_doc, &QTextDocument::blockCountChanged, this, &ZuesEdit::onBlockChange);

	_init();
	setFocus();
	setFocusPolicy(Qt::StrongFocus);
//	insertPlainText("123");
}

void ZuesEdit::_init()
{
// 	QTextCursor textCursor = this->textCursor();
// 	QTextCharFormat charFormat = _getNormalFormat();
// 	textCursor.select(QTextCursor::BlockUnderCursor);
// 	textCursor.setBlockCharFormat(charFormat);
// 	textCursor.setPosition(0);

	QFont font;
	font.setBold(false);
	font.setPixelSize(22);

	m_doc->setDefaultFont(font);
}

ZuesEdit::~ZuesEdit()
{
}

void ZuesEdit::inputMethodEvent(QInputMethodEvent*e)
{
	QString str = e->commitString();
	QString str1 = e->preeditString();
	qDebug() << str << str1;
	return QTextEdit::inputMethodEvent(e);
}

void ZuesEdit::onInputEnter()
{

}



void ZuesEdit::onBlockChange(int newIndex)
{
	QTextBlock curBlock = m_doc->findBlockByNumber(newIndex);
	QTextBlockFormat blockFormat = curBlock.blockFormat();
	int index = blockFormat.headingLevel();

	QTextCursor textCursor = this->textCursor();

	QTextCharFormat charFormat;

	QFont font;
	font.setBold(false);
	font.setPixelSize(22);
	charFormat.setFont(font);

	textCursor.select(QTextCursor::BlockUnderCursor);
	textCursor.setBlockCharFormat(charFormat);
	qDebug() << index;
}

//输入处理的总入口
void ZuesEdit::onDealInput()
{
	QTextCursor textCursor = this->textCursor();
	QTextBlock curTextBlock = textCursor.block();

	ZuesRange range(&textCursor, &curTextBlock);
	range.InitRange();
}

void ZuesEdit::testOutAllBlock() 
{
	QTextFrame* frame = m_doc->rootFrame();
	auto f = frame->begin();
	for (auto iter = f; f != frame->end(); f++)
	{
		QTextBlock textBlock = f.currentBlock();
		qDebug() << textBlock.text();
	}
}
