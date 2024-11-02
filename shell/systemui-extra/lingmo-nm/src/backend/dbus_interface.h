/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp dbus.xml -p dbus_interface
 *
 * qdbusxml2cpp is Copyright (C) 2020 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef DBUS_INTERFACE_H
#define DBUS_INTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.lingmo.network
 */
class ComLingmoNetworkInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.lingmo.network"; }

public:
    ComLingmoNetworkInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~ComLingmoNetworkInterface();

public Q_SLOTS: // METHODS
    inline Q_NOREPLY void deleteConnect(int type, const QString ssid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(type) << QVariant::fromValue(ssid);
        callWithArgumentList(QDBus::NoBlock, QStringLiteral("deleteConnect"), argumentList);
    }
    inline Q_NOREPLY void activateConnect(int type, const QString &devName, const QString &ssid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(type) << QVariant::fromValue(devName) << QVariant::fromValue(ssid);
        callWithArgumentList(QDBus::NoBlock, QStringLiteral("activateConnect"), argumentList);
    }

    inline QDBusPendingReply<> activeWirelessAp(const QString &apName, const QString &apPassword, const QString &band, const QString &apDevice)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(apName) << QVariant::fromValue(apPassword) << QVariant::fromValue(band) << QVariant::fromValue(apDevice);
        return asyncCallWithArgumentList(QStringLiteral("activeWirelessAp"), argumentList);
    }

    inline Q_NOREPLY void deActivateConnect(int type, const QString &devName, const QString &ssid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(type) << QVariant::fromValue(devName) << QVariant::fromValue(ssid);
        callWithArgumentList(QDBus::NoBlock, QStringLiteral("deActivateConnect"), argumentList);
    }

    inline QDBusPendingReply<> deactiveWirelessAp(const QString &apName, const QString &uuid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(apName) << QVariant::fromValue(uuid);
        return asyncCallWithArgumentList(QStringLiteral("deactiveWirelessAp"), argumentList);
    }

    inline QDBusPendingReply<QString> getActiveConnectionPath(const QString &uuid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(uuid);
        return asyncCallWithArgumentList(QStringLiteral("getActiveConnectionPath"), argumentList);
    }

    inline QDBusPendingReply<QString> getApConnectionPath(const QString &uuid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(uuid);
        return asyncCallWithArgumentList(QStringLiteral("getApConnectionPath"), argumentList);
    }

    inline QDBusPendingReply<QStringList> getApInfoBySsid(const QString &devName, const QString &ssid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(devName) << QVariant::fromValue(ssid);
        return asyncCallWithArgumentList(QStringLiteral("getApInfoBySsid"), argumentList);
    }

    inline QDBusPendingReply<QVariantMap> getDeviceListAndEnabled(int devType)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(devType);
        return asyncCallWithArgumentList(QStringLiteral("getDeviceListAndEnabled"), argumentList);
    }

    inline QDBusPendingReply<QStringList> getStoredApInfo()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("getStoredApInfo"), argumentList);
    }

    inline QDBusPendingReply<QVariantList> getWiredList(const QString &devName)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(devName);
        return asyncCallWithArgumentList(QStringLiteral("getWiredList"), argumentList);
    }

    inline QDBusPendingReply<QVariantMap> getWirelessDeviceCap()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("getWirelessDeviceCap"), argumentList);
    }

    inline QDBusPendingReply<QVariantList> getWirelessList(const QString &devName)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(devName);
        return asyncCallWithArgumentList(QStringLiteral("getWirelessList"), argumentList);
    }

    inline QDBusPendingReply<bool> getWirelessSwitchBtnState()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("getWirelessSwitchBtnState"), argumentList);
    }

    inline QDBusPendingReply<> keyRingClear()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("keyRingClear"), argumentList);
    }

    inline QDBusPendingReply<> keyRingInit()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("keyRingInit"), argumentList);
    }

    inline QDBusPendingReply<> reScan()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("reScan"), argumentList);
    }

    inline Q_NOREPLY void setDeviceEnable(const QString &devName, bool enable)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(devName) << QVariant::fromValue(enable);
        callWithArgumentList(QDBus::NoBlock, QStringLiteral("setDeviceEnable"), argumentList);
    }

    inline Q_NOREPLY void setWiredSwitchEnable(bool enable)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(enable);
        callWithArgumentList(QDBus::NoBlock, QStringLiteral("setWiredSwitchEnable"), argumentList);
    }

    inline Q_NOREPLY void setWirelessSwitchEnable(bool enable)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(enable);
        callWithArgumentList(QDBus::NoBlock, QStringLiteral("setWirelessSwitchEnable"), argumentList);
    }

    inline Q_NOREPLY void showAddOtherWlanWidget(const QString &devName)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(devName);
        callWithArgumentList(QDBus::NoBlock, QStringLiteral("showAddOtherWlanWidget"), argumentList);
    }

    inline Q_NOREPLY void showCreateWiredConnectWidget(const QString &devName)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(devName);
        callWithArgumentList(QDBus::NoBlock, QStringLiteral("showCreateWiredConnectWidget"), argumentList);
    }

    inline QDBusPendingReply<> showLingmoNM(int type)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(type);
        return asyncCallWithArgumentList(QStringLiteral("showLingmoNM"), argumentList);
    }

    inline Q_NOREPLY void showPropertyWidget(const QString &devName, const QString &ssid)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(devName) << QVariant::fromValue(ssid);
        callWithArgumentList(QDBus::NoBlock, QStringLiteral("showPropertyWidget"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void activateFailed(const QString &errorMessage);
    void deactivateFailed(const QString &errorMessage);
    void deviceNameChanged(const QString &oldName, const QString &newName, int type);
    void deviceStatusChanged();
    void hotspotActivated(const QString &devName, const QString &ssid, const QString &uuid, const QString &activePath, const QString &settingPath);
    void hotspotDeactivated(const QString &devName, const QString &ssid);
    void lanActiveConnectionStateChanged(const QString &devName, const QString &uuid, int status);
    void lanAdd(const QString &devName, const QStringList &info);
    void lanRemove(const QString &dbusPath);
    void lanUpdate(const QString &devName, const QStringList &info);
    void secuTypeChange(const QString &devName, const QString &ssid, const QString &secuType);
    void showAddOtherWlanWidgetSignal(const QString &display, const QString &devName);
    void showCreateWiredConnectWidgetSignal(const QString &display, const QString &devName);
    void showLingmoNMSignal(const QString &display, int type);
    void showPropertyWidgetSignal(const QString &display, const QString &devName, const QString &ssid);
    void signalStrengthChange(const QString &devName, const QString &ssid, int strength);
    void timeToUpdate();
    void wirelessDeviceStatusChanged();
    void wirelessSwitchBtnChanged(bool state);
    void wlanAdd(const QString &devName, const QStringList &info);
    void wlanRemove(const QString &devName, const QString &ssid);
    void wlanactiveConnectionStateChanged(const QString &devName, const QString &ssid, const QString &uuid, int status);
};

namespace com {
  namespace lingmo {
    typedef ::ComLingmoNetworkInterface network;
  }
}
#endif