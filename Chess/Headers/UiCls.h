#ifndef UICLS_H
#define UICLS_H

#include <QObject>

class UiCls : public QObject
{
	Q_OBJECT
public:
	explicit UiCls(QObject* parent = nullptr);
};

#endif