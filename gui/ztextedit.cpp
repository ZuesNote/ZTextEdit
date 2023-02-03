#include "ztextedit.h"

#include <QTextCursor>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextLayout>
#include <QAbstractTextDocumentLayout>

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

