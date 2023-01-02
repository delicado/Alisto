#ifndef XYAXISVIEW_H
#define XYAXISVIEW_H

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QList>

static constexpr double cfg_axis_size_x = 235.0;
static constexpr double cfg_axis_size_y = 235.0;
static constexpr double cfg_axis_size_z = 250.0;
static constexpr int cfg_layer_axis_density = 8;
static constexpr double cfg_layer_pixels_x = cfg_axis_size_x * double(cfg_layer_axis_density);
static constexpr double cfg_layer_pixels_y = cfg_axis_size_y * double(cfg_layer_axis_density);
static constexpr double cfg_layers_z = cfg_axis_size_z * double(cfg_layer_axis_density);

class XYLayer {
    QImage _data;
public:
    XYLayer() = default;
    XYLayer(int x, int y);
    void Init(int x, int y);

    const QImage& GetData() const;
    QImage& GetData();
};

class XYAxisView : public QWidget
{
    Q_OBJECT

    struct _Head {
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
    };

    QVector<XYLayer> _layers;
    QVector<_Head> _head;

    int _active_layer = 0;
protected:
    void paintEvent(QPaintEvent* event) override;
    void InitLayer(int layer);
public:
    explicit XYAxisView(QWidget *parent = nullptr);

    void InitHeadCount(int heads);
    void DisplayLayer(double layer);

    void Put(int head_id, double x, double y, double z, double radius);

signals:

};

#endif // XYAXISVIEW_H
