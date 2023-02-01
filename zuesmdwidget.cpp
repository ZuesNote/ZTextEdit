#include "zuesmdwidget.h"
#include "zuesedit.h"
#include <QVBoxLayout>


ZuesMDWidget::ZuesMDWidget(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout* vBox = new QVBoxLayout(this);
	ZuesEdit* mdEdit = new ZuesEdit(this);

	vBox->addWidget(mdEdit);

	this->setLayout(vBox);
}

ZuesMDWidget::~ZuesMDWidget()
{
}

