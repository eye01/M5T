#ifndef ITEMBUTTON_H
#define ITEMBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
class ItemButton : public QWidget
{
    Q_OBJECT
public:
    explicit ItemButton(QWidget *parent = 0);

    ~ItemButton();

    void mousePressEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

    void setStyleSheet(const QString &styleSheet);

    void setMaskStyleSheet(const QString &styleSheet);

    void setText(QString sText);

    QString text();

    void setImage(QString sUrl);

protected:

    QLabel *m_lb;

    QLabel *m_mask;

private:

    void showEvent(QShowEvent *);

signals:

    void clicked();

public slots:
};

#endif // ITEMBUTTON_H
