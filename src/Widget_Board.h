#ifndef WIDGET_BOARD_H
#define WIDGET_BOARD_H

#include <QtWidgets>
#include <QPushButton>

class Boards_ui;

class Widget_Board : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Board(std::size_t indx, const std::string& lbl, Boards_ui *parent = nullptr);
    static QWidget* create_ADD_widget(Boards_ui* parent = nullptr);
    QWidget* create_buttons();
    virtual ~Widget_Board() override;

signals:
    void signalLabelChanged(std::size_t, const std::string&);
    void signalRemoveBoard(std::size_t);
    void signalPressed(std::size_t indx);

public slots:
    void slotLabelChanged();
    void slotRemoveBoard();

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void mousePressEvent(QMouseEvent* event) override
    {
        emit signalPressed(indx);
    }

private:
     QLabel* create_label();

private:
    QLabel* name;
    QWidget* buttons;
    std::size_t indx;
    std::string label;
};

#endif // WIDGET_BOARD_H
