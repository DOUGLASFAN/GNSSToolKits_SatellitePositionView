#include "satellitepositionview.h"
#include "ui_satellitepositionview.h"
#include <QMouseEvent>
#include <QMessageBox>  // 用于显示详情对话框
satellitepositionview::satellitepositionview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::satellitepositionview)
{
    ui->setupUi(this);


    // 启用鼠标追踪，用于悬停效果
    setMouseTracking(true);

    //模拟数据
    QVector<Satellite> testData;
    testData.append(Satellite(1, 45, 30, 40, true, "BDS"));
    testData.append(Satellite(2, 66, 120, 35, true, "GLONASS"));
    testData.append(Satellite(3, 30, 210, 25, false, "GPS"));
    testData.append(Satellite(4, 75, 300, 45, true, "GLONASS"));
    testData.append(Satellite(5, 45, 45, 20, true, "BDS"));
    testData.append(Satellite(6, 52, 150, 30, false, "GPS"));
    testData.append(Satellite(7, 80, 240, 50, true, "Galileo"));
    testData.append(Satellite(8, 25, 330, 15, true, "Galileo"));

    m_satellites = testData;
}

//绘制事件总函数
void satellitepositionview::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //绘制网格线
    drawSkyGrid(painter);

    //绘制卫星
    drawSatellites(painter);

    //绘制图例
    drawLegend(painter);

    // 绘制指北针
    drawCompass(painter);
}

// 绘制网格
void satellitepositionview::drawSkyGrid(QPainter &painter)
{
    QPointF center (width() / 2.0,height() / 2.0);
    double radius = qMin(width(),height()) / 2.0 - 50;


    QPen pen(Qt::darkBlue,1);
    painter.setPen(pen);
    painter.drawPoint(center);


    for(int el = 90;el >= 0;el -= 30){
        double r = (90 - el) / 90.0 * radius;
        painter.drawEllipse(center,r,r);
        if(el == 0){
            continue;
        }
        painter.drawText(center.x(),center.y() - r-5,QString("%1 °").arg(el));

    }

    for(int az = 0;az < 360;az += 30){
        double azRad = az * M_PI / 180;

        QPointF end(center.x()+radius * sin(azRad),
                    center.y() - radius * cos(azRad));
        painter.drawLine(center,end);
        QString label;
        switch(az){
        case 0: label = "N" ; break;
        case 90: label = "E"; break;
        case 180: label = "S"; break;
        case 270: label = "W"; break;
        default : label = QString("%1 °").arg(az);
        }

        QPointF labelPos;
        if(az > 180){
            labelPos = QPointF(center.x()+(radius+35) * sin(azRad),
                             center.y() -(radius+35) * cos(azRad));
        }else{
            labelPos = QPointF(center.x()+(radius+5) * sin(azRad),
                             center.y() -(radius+15) * cos(azRad));
        }

        painter.drawText(labelPos.x()+2,labelPos.y(),label);
    }


}


// 获取极坐标下的卫星 x轴和y轴
QPointF satellitepositionview::polarToCartesian(int ele,int az)
{
    //仰角确定半径
    //方位角确定位置
    double r = 1.0 - (ele / 90.0);
    double azRad = az *M_PI /180.0;

    double x = r * sin(azRad);
    double y = - r * cos(azRad);

    return QPointF(x,y);
}


// 鼠标点击事件处理
void satellitepositionview::mousePressEvent(QMouseEvent *event)
{
    // 只处理左键点击
    if (event->button() == Qt::LeftButton) {
        //
        int index = findSatelliteAtPosition(event->pos());
        if (index != -1) {
            m_selectedSatelliteIndex = index;
            showSatelliteDetails(index);
            // 重绘以突出显示选中的卫星
            update();
        }
    }
    QWidget::mousePressEvent(event);
}

// 鼠标移动事件（可选，用于悬停提示）
void satellitepositionview::mouseMoveEvent(QMouseEvent *event)
{
    int index = findSatelliteAtPosition(event->pos());
    if (index != -1) {
        const Satellite &sat = m_satellites[index];
        // 显示简单的悬停提示
        QToolTip::showText(event->globalPos(),
                           QString("卫星 %1\n%2").arg(sat.id).arg(sat.type));
    } else {
        QToolTip::hideText();
    }
    QWidget::mouseMoveEvent(event);
}

// 根据点击位置查找卫星
int satellitepositionview::findSatelliteAtPosition(const QPoint &pos)
{
    QPointF center(width() / 2.0, height() / 2.0);
    double radius = qMin(width(), height()) / 2.0 - 50;

    // 遍历所有卫星，检查点击位置是否在卫星图标范围内
    for (int i = 0; i < m_satellites.size(); ++i) {
        const Satellite &sat = m_satellites[i];
        QPointF satPos = polarToCartesian(sat.elevation, sat.azimuth);
        QPointF pixelPos(center.x() + satPos.x() * radius,
                         center.y() + satPos.y() * radius);

        // 计算点击位置与卫星图标的距离
        double distance = QLineF(pos, pixelPos).length();

        // 如果距离小于卫星图标的半径（10像素），则认为点击了该卫星
        if (distance <= 10) {
            return i;
        }
    }
    return -1;  // 未找到卫星
}

// 显示卫星详细信息
void satellitepositionview::showSatelliteDetails(int index)
{
    if (index < 0 || index >= m_satellites.size())
        return;

    const Satellite &sat = m_satellites[index];

    // 使用QMessageBox显示详情
    QString details = QString("卫星详情:\n")
                      + QString("编号: %1\n").arg(sat.id)
                      + QString("星座: %1\n").arg(sat.type)
                      + QString("仰角: %1°\n").arg(sat.elevation)
                      + QString("方位角: %1°\n").arg(sat.azimuth)
                      + QString("载噪比: %1\n").arg(sat.snr)
                      + QString("是否参与解算: %1").arg(sat.isuse ? "是" : "否");

    QMessageBox::information(this, "卫星信息", details);
}

// drawSatellites方法，绘制卫星，并突出显示选中的卫星
void satellitepositionview::drawSatellites(QPainter &painter)
{
    //中心点位置
    QPointF center(width() / 2.0, height() / 2.0);
    //确定半径
    double radius = qMin(width(), height()) / 2.0 - 50;


    //确定不同卫星的颜色
    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QBrush grayBrush(Qt::gray);
    QBrush yellowBrush(Qt::yellow);

    // 新增：选中卫星的边框画笔
    QPen selectedPen(Qt::white, 2);

    //遍历整个卫星集合，绘制
    for(int i = 0; i < m_satellites.size(); ++i) {
        const Satellite &sat = m_satellites[i];
        //转换成极坐标
        QPointF satPos = polarToCartesian(sat.elevation, sat.azimuth);
        //极坐标转换为二维坐标
        QPointF pixelPos (center.x() + satPos.x() * radius,
                         center.y() + satPos.y() * radius);

        // 设置卫星颜色
        if(sat.isuse){
            if(sat.type == "BDS") painter.setBrush(redBrush);
            if(sat.type == "GPS") painter.setBrush(yellowBrush);
            if(sat.type == "Galileo") painter.setBrush(greenBrush);
            if(sat.type == "GLONASS") painter.setBrush(blueBrush);
        }else{
            painter.setBrush(grayBrush);
        }

        // 如果是选中的卫星，绘制白色边框
        if (i == m_selectedSatelliteIndex) {
            painter.setPen(selectedPen);
        } else {
            // 普通卫星使用默认边框
            painter.setPen(QPen(Qt::black, 1));
        }

        // 绘制卫星为 10，10的圆
        painter.drawEllipse(pixelPos, 10, 10);
        //绘制卫星的文本描述
        painter.drawText(pixelPos + QPointF(-4, 4), QString::number(sat.id));
    }
}

// 展示图注
void satellitepositionview::drawLegend(QPainter &painter){
    painter.save();

    // 图例位置和大小设置
    int legendWidth = 180;
    int legendHeight = 200;
    int x = width() - legendWidth - 10;  // 右侧留出10px边距
    int y = 10;                          // 顶部留出10px边距

    // 绘制图例背景
    painter.setBrush(QBrush(QColor(255, 255, 255, 230)));  // 半透明白色
    painter.setPen(QPen(Qt::gray, 1));
    painter.drawRect(x, y, legendWidth, legendHeight);

    // 绘制图例标题
    painter.setPen(QPen(Qt::black));
    painter.setFont(QFont("SimHei", 10, QFont::Bold));
    painter.drawText(x + 10, y + 20, "卫星图例");

    // 图例项位置偏移量
    int itemOffset = 30;
    int textOffsetX = 30;
    int textOffsetY = 5;

    // 定义图例项：颜色和对应的文本
    QVector<QPair<QColor, QString>> legendItems = {
        {Qt::red, "北斗 (BDS)"},
        {Qt::yellow, "GPS"},
        {Qt::green, "伽利略 (Galileo)"},
        {Qt::blue, "格洛纳斯 (GLONASS)"},
        {Qt::gray, "未参与解算卫星"},
        {Qt::white, "选中的卫星 (白色边框)"}
    };

    // 绘制每个图例项
    painter.setFont(QFont("SimHei", 9));
    for (int i = 0; i < legendItems.size(); ++i) {
        int itemY = y + 40 + i * itemOffset;

        // 绘制颜色标识
        painter.setBrush(QBrush(legendItems[i].first));
        if (i == 5) {  // 特殊处理"选中的卫星"项
            painter.setPen(QPen(Qt::white, 2));
            painter.drawRect(x + 10, itemY - 8, 16, 16);
        } else {
            painter.setPen(QPen(Qt::black, 1));
            painter.drawEllipse(x + 10, itemY - 8, 16, 16);
        }

        // 绘制文本说明
        painter.setPen(QPen(Qt::black));
        painter.drawText(x + textOffsetX, itemY + textOffsetY, legendItems[i].second);
    }

    // 恢复画笔状态
    painter.restore();
}


// 新增：绘制指北针函数
void satellitepositionview::drawCompass(QPainter &painter)
{
    // 保存当前画笔状态
    painter.save();

    // 指北针位置和大小（左下角）
    int compassSize = 60;
    int margin = 10;
    int x = margin;
    int y = height() - compassSize - margin;

    // 绘制指南针背景
    painter.setBrush(QBrush(QColor(255, 255, 255, 220))); // 半透明白色
    painter.setPen(QPen(Qt::lightGray, 1));
    painter.drawEllipse(x, y, compassSize, compassSize);

    // 指南针中心点
    QPointF center(x + compassSize/2, y + compassSize/2);
    int radius = compassSize / 2 - 5;

    // 绘制方向线（北、东、南、西）
    painter.setPen(QPen(Qt::black, 2));

    // 北线（最长线）
    painter.drawLine(center.x(), center.y() - radius,
                     center.x(), center.y() - radius/2);

    // 东线
    painter.drawLine(center.x() + radius/2, center.y(),
                     center.x() + radius, center.y());

    // 南线
    painter.drawLine(center.x(), center.y() + radius/2,
                     center.x(), center.y() + radius);

    // 西线
    painter.drawLine(center.x() - radius, center.y(),
                     center.x() - radius/2, center.y());

    // 绘制方向标签
    painter.setFont(QFont("SimHei", 8, QFont::Bold));
    painter.drawText(center.x() - 5, center.y() - radius + 12, "N"); // 北
    painter.drawText(center.x() + radius - 8, center.y() + 5, "E");  // 东
    painter.drawText(center.x() - 5, center.y() + radius + 10, "S"); // 南
    painter.drawText(center.x() - radius + 2, center.y() + 5, "W");  // 西

    // 绘制北方箭头
    painter.setBrush(QBrush(Qt::red));
    painter.setPen(QPen(Qt::darkRed, 1));

    QPolygonF arrow;
    arrow << center + QPointF(0, -radius*0.7)
          << center + QPointF(-radius*0.2, -radius*0.3)
          << center + QPointF(radius*0.2, -radius*0.3);
    painter.drawPolygon(arrow);

    // 恢复画笔状态
    painter.restore();
}


satellitepositionview::~satellitepositionview()
{
    delete ui;
}
