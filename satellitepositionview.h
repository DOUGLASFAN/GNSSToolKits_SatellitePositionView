#ifndef SATELLITEPOSITIONVIEW_H
#define SATELLITEPOSITIONVIEW_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPointF>
#include <QVector>
#include <QToolTip>  // 新增：用于显示提示框

QT_BEGIN_NAMESPACE
namespace Ui {
class satellitepositionview;
}
QT_END_NAMESPACE

struct Satellite{
    int id;             // 卫星编号
    int elevation;      // 仰角
    int azimuth;        // 方位角
    int snr;            // 载噪比
    bool isuse;         // 卫星是否参与未知结算
    QString type;       // 卫星星座类型（GPS,BDS,Galileo,GLONASS）

    Satellite() {}
    Satellite(int id, int ele, int az, int snr, bool use, QString t)
        : id(id), elevation(ele), azimuth(az), snr(snr), isuse(use), type(t) {}
};

class satellitepositionview : public QWidget
{
    Q_OBJECT

public:
    satellitepositionview(QWidget *parent = nullptr);
    ~satellitepositionview();

protected:
    void paintEvent(QPaintEvent *event) override;
    // 新增：重写鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override;
    // 新增：重写鼠标悬停事件（可选）
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::satellitepositionview *ui;
    QVector<Satellite> m_satellites;

    // 新增：当前选中的卫星索引
    int m_selectedSatelliteIndex;

    void drawSkyGrid(QPainter &painter);
    void drawSatellites(QPainter &painter);
    QPointF polarToCartesian(int ele,int az);

    // 新增：根据坐标查找卫星
    int findSatelliteAtPosition(const QPoint &pos);
    // 新增：显示卫星详情
    void showSatelliteDetails(int index);
    // 绘制图例
    void drawLegend(QPainter &painter);
    // 绘制指北针
    void drawCompass(QPainter &painter);

};
#endif // SATELLITEPOSITIONVIEW_H
