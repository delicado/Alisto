#include "xy_axis_view.h"
#include <QPainter>
#include <QPointF>

XYAxisView::XYAxisView(QWidget *parent)
    : QWidget{parent}
{
    _layers.resize(int(cfg_layers_z));
    //test
    this->InitLayer(0);
}

void XYAxisView::InitHeadCount(int heads)
{
    _head.resize(heads);
}


void XYAxisView::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(this->rect(), _layers.at(_active_layer).GetData());
    painter.end();
}

void XYAxisView::InitLayer(int layer)
{
    int index = cfg_layer_axis_density * layer;
    for(int i = 0; i < int(cfg_layer_axis_density); ++i)
        _layers[index + i].Init(int(cfg_layer_pixels_x), int(cfg_layer_pixels_y));
}


void XYAxisView::DisplayLayer(double layer)
{
    _active_layer = layer;
}

void XYAxisView::Put(int head_id, double x, double y, double z, double radius)
{
    double t = cfg_layer_axis_density / 2.0;
    double xt = (cfg_layer_axis_density * x) + t;
    double yt = (cfg_layer_axis_density * y) + t;
    double zt = (cfg_layer_axis_density * z) + t;

    auto& i = _layers[0].GetData();
    QPainter p;
    p.begin(&i);
    p.drawRect(xt - (radius / 2), yt - (radius / 2), radius, radius);
}

XYLayer::XYLayer(int x, int y)
{
    this->Init(x, y);
}

void XYLayer::Init(int x, int y)
{
    _data = QImage(x, y, QImage::Format_Grayscale8);
    _data.fill(0);
}

const QImage &XYLayer::GetData() const
{
    return _data;
}

QImage &XYLayer::GetData()
{
    return _data;
}


