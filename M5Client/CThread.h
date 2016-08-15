#ifndef CTHREAD_H
#define CTHREAD_H

#include <QThread>



class CThread : public QThread
{
    Q_OBJECT
public:
    explicit CThread(QThread *parent = 0);

signals:

public slots:
};

#endif // CTHREAD_H
