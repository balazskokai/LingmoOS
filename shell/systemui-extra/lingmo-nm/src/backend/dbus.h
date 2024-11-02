/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp com.lingmo.weather.xml -a dbusadaptor -c DbusAdaptor -l MainWindow
 *
 * qdbusxml2cpp is Copyright (C) 2015 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef DBUSADAPTOR_H
#define DBUSADAPTOR_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMetaType>
#include "dbus_adaptor.h"
#include "dbus_interface.h"

#include "tabpage.h"
#include "../dbus-interface/lingmonetworkdeviceresource.h"
QT_BEGIN_NAMESPACE
class QByteArray;
//template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
template<class T> class QVector;
QT_END_NAMESPACE

/*
 * Adaptor class for interface com.lingmo.weather
 */

#include "mainwindow.h"

class DbusAdaptor: public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.lingmo.network")
public:
    explicit DbusAdaptor(QString display, MainWindow *m, QObject *parent = nullptr);

public: // PROPERTIES
public Q_SLOTS: // METHODS
    //无线列表
    QVariantList getWirelessList(QString devName);
    //有线列表
    QVariantList getWiredList(QString devName);
    //有线总开关
    Q_NOREPLY void setWiredSwitchEnable(bool enable);
    //无线总开关
    Q_NOREPLY void setWirelessSwitchEnable(bool enable);
    //有线网卡开关
    Q_NOREPLY void setDeviceEnable(QString devName, bool enable);
    //设置默认网卡
//    Q_NOREPLY void setDefaultWiredDevice(QString deviceName);
//    QString getDefaultWiredDevice();
//    Q_NOREPLY void setDefaultWirelessDevice(QString deviceName);
//    QString  getDefaultWirelessDevice();
    //刪除 根据网络名称 参数1 0:lan 1:wlan 参数2 为ssid/uuid
    void deleteConnect(int type, QString ssid);
    //连接 根据网卡类型 参数1 0:lan 1:wlan 参数3 为ssid/uuid
    Q_NOREPLY void activateConnect(int type, QString devName, QString ssid);
    //断开连接 根据网卡类型 参数1 0:lan 1:wlan 参数3 为ssid/uuid
    Q_NOREPLY void deActivateConnect(int type, QString devName, QString ssid);
    //获取设备列表和启用/禁用状态
    QVariantMap getDeviceListAndEnabled(int devType);
    //获取无线设备能力
    QVariantMap getWirelessDeviceCap();
    //唤起属性页 根据网卡类型 参数2 为ssid/uuid
    Q_NOREPLY void showPropertyWidget(QString devName, QString ssid);
    //唤起新建有线连接界面
    Q_NOREPLY void showCreateWiredConnectWidget(QString devName);
    //唤起加入其他无线网络界面
    Q_NOREPLY void showAddOtherWlanWidget(QString devName);
    //开启热点
    void activeWirelessAp(const QString apName, const QString apPassword, const QString band, const QString apDevice);
    //断开热点
    void deactiveWirelessAp(const QString apName, const QString uuid);
    //获取热点
    QStringList getStoredApInfo();
    QStringList getApInfoBySsid(QString devName, QString ssid);
    QString getApConnectionPath(QString uuid);
    QString getActiveConnectionPath(QString uuid);
    //wifi扫描
    void reScan();
    //keyring
    void keyRingInit();
    void keyRingClear();
    //just show
    void showLingmoNM(int type);

    bool getWirelessSwitchBtnState();

Q_SIGNALS: // SIGNALS
//    void wirelessActivating(QString devName, QString ssid);
//    void wiredActivating(QString devName, QString ssid);
    void lanAdd(QString devName, QStringList info);
    void lanRemove(QString dbusPath);
    void lanUpdate(QString devName, QStringList info);
    void wlanAdd(QString devName, QStringList info);
    void wlanRemove(QString devName,QString ssid);
    void wlanactiveConnectionStateChanged(QString devName, QString ssid, QString uuid, int status);
    void lanActiveConnectionStateChanged(QString devName, QString uuid, int status);
    //仅失败，若成功直接发listUpdate
    void activateFailed(QString errorMessage);
    void deactivateFailed(QString errorMessage);
    //设备插拔
    void deviceStatusChanged();
    void wirelessDeviceStatusChanged();
    void deviceNameChanged(QString oldName, QString newName, int type);
    void wirelessSwitchBtnChanged(bool state);
    //热点断开
    void hotspotDeactivated(QString devName, QString ssid);
    //热点连接
    void hotspotActivated(QString devName, QString ssid, QString uuid, QString activePath, QString settingPath);
    //信号强度变化
    void signalStrengthChange(QString devName, QString ssid, int strength);
    //安全性变化
    void secuTypeChange(QString devName, QString ssid, QString secuType);
    //列表排序
    void timeToUpdate();



    void showLingmoNMSignal(QString display, int type);

    //唤起属性页 根据网卡类型 参数2 为ssid/uuid
    void showPropertyWidgetSignal(QString display, QString devName, QString ssid);
    //唤起新建有线连接界面
    void showCreateWiredConnectWidgetSignal(QString display, QString devName);
    //唤起加入其他无线网络界面
    void showAddOtherWlanWidgetSignal(QString display, QString devName);

private:
    MainWindow *m_mainWindow;
    QString m_display;
    QDBusServiceWatcher *m_watcher = nullptr;

    QString checkDisplay();
    QString displayFromPid(uint pid);
    void connectToMainwindow();
    bool registerService();
private Q_SLOT:
    void onServiceOwnerChanged(const QString &service, const QString &oldOwner, const QString &newOwner);
};

#endif