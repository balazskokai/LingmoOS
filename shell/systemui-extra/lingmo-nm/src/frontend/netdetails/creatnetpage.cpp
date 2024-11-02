/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2022 Tianjin LINGMO Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */
#include "creatnetpage.h"
#include "math.h"

#define MAX_NAME_LENGTH 32
#define  HINT_TEXT_MARGINS 8, 1, 0, 3
#define  LABEL_HEIGHT 24
#define FRAME_SPEED 150
#define ICON_SIZE 16,16

CreatNetPage::CreatNetPage(QWidget *parent):QFrame(parent)
{
    initUI();
    initComponent();
}

void CreatNetPage::initUI()
{
    connNameEdit = new LineEdit(this);
    ipv4ConfigCombox = new QComboBox(this);
    ipv4addressEdit = new LineEdit(this);
    netMaskEdit = new LineEdit(this);
    gateWayEdit = new LineEdit(this);

    m_connNameLabel = new QLabel(this);
    m_configLabel = new QLabel(this);
    m_addressLabel = new QLabel(this);
    m_maskLabel = new QLabel(this);
    m_gateWayLabel = new QLabel(this);

    // IP的正则格式限制
    QRegExp rx("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");
    m_dnsWidget = new MultipleDnsWidget(rx, false, this);

    QLabel *nameEmptyLabel = new QLabel(this);
    QLabel *configEmptyLabel = new QLabel(this);
    QLabel *gateWayEmptyLabel = new QLabel(this);

    QLabel *firstDnsEmptyLabel = new QLabel(this);
    nameEmptyLabel->setFixedHeight(LABEL_HEIGHT);
    configEmptyLabel->setFixedHeight(LABEL_HEIGHT);
    gateWayEmptyLabel->setFixedHeight(LABEL_HEIGHT);
    firstDnsEmptyLabel->setFixedHeight(LABEL_HEIGHT);

    m_addressHintLabel = new QLabel(this);
    m_maskHintLabel = new QLabel(this);
    m_addressHintLabel->setFixedHeight(LABEL_HEIGHT);
    m_maskHintLabel->setFixedHeight(LABEL_HEIGHT);
    m_addressHintLabel->setContentsMargins(HINT_TEXT_MARGINS);
    m_maskHintLabel->setContentsMargins(HINT_TEXT_MARGINS);

    m_statusLabel = new QLabel(this);
    m_statusLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QHBoxLayout *pPwdLayout = new QHBoxLayout(ipv4addressEdit);
    pPwdLayout->addStretch();
    pPwdLayout->addWidget(m_statusLabel);

    QPalette hintTextColor;
    hintTextColor.setColor(QPalette::WindowText, Qt::red);
    m_addressHintLabel->setPalette(hintTextColor);
    m_maskHintLabel->setPalette(hintTextColor);

    QWidget *addressWidget = new QWidget(this);
    QVBoxLayout *addressLayout = new QVBoxLayout(addressWidget);
    addressLayout->setContentsMargins(0, 0, 0, 0);
    addressLayout->setSpacing(0);
    addressLayout->addWidget(ipv4addressEdit);
    addressLayout->addWidget(m_addressHintLabel);

    initConflictHintLable();

    QWidget *maskWidget = new QWidget(this);
    QVBoxLayout *maskLayout = new QVBoxLayout(maskWidget);
    maskLayout->setContentsMargins(0, 0, 0, 0);
    maskLayout->setSpacing(0);
    maskLayout->addWidget(netMaskEdit);
    maskLayout->addWidget(m_maskHintLabel);

    m_connNameLabel->setText(tr("Connection Name"));
    m_configLabel->setText(tr("IPv4Config"));
    m_addressLabel->setText(tr("Address"));
    m_maskLabel->setText(tr("Netmask"));
    m_gateWayLabel->setText(tr("Default Gateway"));

    m_detailLayout = new QFormLayout(this);
    m_detailLayout->setVerticalSpacing(0);
    m_detailLayout->setContentsMargins(0, 0, 0, 0);
    m_detailLayout->addRow(m_connNameLabel,connNameEdit);
    m_detailLayout->addRow(nameEmptyLabel);
    m_detailLayout->addRow(m_configLabel,ipv4ConfigCombox);
    m_detailLayout->addRow(configEmptyLabel);
    m_detailLayout->addRow(m_addressLabel, addressWidget);
    m_detailLayout->addRow(m_maskLabel, maskWidget);
    m_detailLayout->addRow(m_gateWayLabel,gateWayEdit);
    m_detailLayout->addRow(gateWayEmptyLabel);

    m_addressLabel->setContentsMargins(0, 0, 0, LABEL_HEIGHT);  //解决布局错位问题
    m_maskLabel->setContentsMargins(0, 0, 0, LABEL_HEIGHT);

    m_detailLayout->addRow(m_dnsWidget);

    ipv4ConfigCombox->addItem(tr("Auto(DHCP)"), AUTO_CONFIG); //"自动(DHCP)"
    ipv4ConfigCombox->addItem(tr("Manual"), MANUAL_CONFIG); //"手动"

    QRegExp nameRx("^.{0,32}$");
    QValidator *validator = new QRegExpValidator(nameRx, this);

    connNameEdit->setValidator(validator);
    ipv4addressEdit->setValidator(new QRegExpValidator(rx, this));
    gateWayEdit->setValidator(new QRegExpValidator(rx, this));
    netMaskEdit->setValidator(new QRegExpValidator(rx, this));

    initLoadingIcon();
}

void CreatNetPage::initComponent() {
    if (ipv4ConfigCombox->currentIndex() == AUTO_CONFIG) {
        setLineEnabled(false);
    } else if (ipv4ConfigCombox->currentIndex() == MANUAL_CONFIG) {
        setLineEnabled(true);
    }
    connect(ipv4ConfigCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(configChanged(int)));

    connect(connNameEdit, SIGNAL(textChanged(QString)), this, SLOT(setEnableOfSaveBtn()));
    connect(ipv4ConfigCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(setEnableOfSaveBtn()));
    connect(netMaskEdit, SIGNAL(textChanged(QString)), this, SLOT(setEnableOfSaveBtn()));
    connect(gateWayEdit, SIGNAL(textChanged(QString)), this, SLOT(setEnableOfSaveBtn()));
    connect(ipv4addressEdit, SIGNAL(textChanged(QString)), this, SLOT(onAddressTextChanged()));
    connect(ipv4addressEdit, SIGNAL(editingFinished()), this, SLOT(onAddressEditFinished()));
    connect(netMaskEdit, SIGNAL(textChanged(QString)), this, SLOT(onNetMaskTextChanged()));
}

bool CreatNetPage::checkConnectBtnIsEnabled()
{
    if (connNameEdit->text().isEmpty()) {
        qDebug() << "create connName empty or invalid";
        return false;
    }
    qDebug() << "checkConnectBtnIsEnabled currentIndex" << ipv4ConfigCombox->currentIndex();
    if (ipv4ConfigCombox->currentIndex() == AUTO_CONFIG) {
        return true;
    } else {
        if (ipv4addressEdit->text().isEmpty() || !getTextEditState(ipv4addressEdit->text())) {
            qDebug() << "create ipv4address empty or invalid";
            return false;
        }

        if (netMaskEdit->text().isEmpty() || !netMaskIsValide(netMaskEdit->text())) {
            qDebug() << "create ipv4 netMask empty or invalid";
            return false;
        }
    }
    return true;
}

void CreatNetPage::configChanged(int index) {
    if (index == AUTO_CONFIG) {
        setLineEnabled(false);
    }
    if (index == MANUAL_CONFIG) {
        setLineEnabled(true);
    }
}

void CreatNetPage::onAddressTextChanged()
{
    m_iconLabel->hide();
    m_textLabel->hide();

    if (!getTextEditState(ipv4addressEdit->text())) {
        m_addressHintLabel->setText(tr("Invalid address"));
    } else {
        m_addressHintLabel->clear();
    }
}

void CreatNetPage::onAddressEditFinished()
{
    if (ipv4addressEdit->isModified()) {
        if (!ipv4addressEdit->text().isEmpty() && getTextEditState(ipv4addressEdit->text())) {
            Q_EMIT ipv4EditFinished(ipv4addressEdit->text());
        }
    }
}

void CreatNetPage::onNetMaskTextChanged()
{
    if (!netMaskIsValide(netMaskEdit->text())) {
        m_maskHintLabel->setText(tr("Invalid subnet mask"));
    } else {
        m_maskHintLabel->clear();
    }
}

void CreatNetPage::setLineEnabled(bool check) {

    ipv4addressEdit->setEnabled(check);
    netMaskEdit->setEnabled(check);
    gateWayEdit->setEnabled(check);

    if (!check) {
        ipv4addressEdit->clear();
        netMaskEdit->clear();
        gateWayEdit->clear();

        ipv4addressEdit->setPlaceholderText(" ");
        netMaskEdit->setPlaceholderText(" ");
    } else {
        ipv4addressEdit->setPlaceholderText(tr("Required")); //必填
        netMaskEdit->setPlaceholderText(tr("Required")); //必填
    }
}

void CreatNetPage::setEnableOfSaveBtn() {
    Q_EMIT setCreatePageState(checkConnectBtnIsEnabled());
}

bool CreatNetPage::getTextEditState(QString text)
{
    if (text.isEmpty()) {
        return true;
    }
    QRegExp rx("\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b");

    bool match = false;
    match = rx.exactMatch(text);

    return match;
}

void CreatNetPage::constructIpv4Info(KyConnectSetting &setting)
{
    setting.m_connectName = connNameEdit->text();
    QString ipv4address =ipv4addressEdit->text();
    QString netMask = getNetMaskText(netMaskEdit->text());
    QString gateWay = gateWayEdit->text();
    qDebug() << "constructIpv4Info: " << "ipv4address " << ipv4address
             << " netMask " << netMask
             << " gateWay " << gateWay;

    QStringList dnsList;
    dnsList.clear();
#if 0
    if (!firstDnsEdit->text().isEmpty()) {
        dnsList << firstDnsEdit->text();
        if (!secondDnsEdit->text().isEmpty()) {
            dnsList << secondDnsEdit->text();
        }
    }
#endif

    QList<QHostAddress> ipv4dnsList;
    ipv4dnsList.clear();
    ipv4dnsList = m_dnsWidget->getDns();

    if (ipv4ConfigCombox->currentData() == AUTO_CONFIG) {
        setting.setIpConfigType(IPADDRESS_V4, CONFIG_IP_DHCP);
    } else {
        setting.setIpConfigType(IPADDRESS_V4, CONFIG_IP_MANUAL);
        setting.ipv4AddressConstruct(ipv4address, netMask, gateWay);
    }

    setting.ipv4DnsConstruct(ipv4dnsList);
}

bool CreatNetPage::netMaskIsValide(QString text)
{
    if (getTextEditState(text)) {
        return true;
    } else {
        if (text.length() > 0 && text.length() < 3) {
            int num = text.toInt();
            if (num > 0 && num < 33) {
                return true;
            }
        }
    }
    return false;
}

QString CreatNetPage::getNetMaskText(QString text)
{
    if (text.length() > 2) {
        return text;
    }

    int num = text.toInt();
    QStringList list;
    list << "0" << "0" << "0" << "0";
    int count = 0;
    while (num - 8 >= 0) {
        list[count] = "255";
        num = num - 8;
        count ++;
    }
    if (num > 0) {
        int size = pow(2, 8) - pow(2,(8-num));
        list[count] = QString::number(size);
    }
    return QString("%1.%2.%3.%4").arg(list[0],list[1],list[2],list[3]);
}

void CreatNetPage::initConflictHintLable()
{
    QIcon icon = QIcon::fromTheme("dialog-warning");
    m_iconLabel = new QLabel(m_addressHintLabel);
    m_iconLabel->setPixmap(icon.pixmap(ICON_SIZE));
    m_textLabel = new QLabel(m_addressHintLabel);
    m_textLabel->setText(tr("Address conflict"));
    QHBoxLayout *conflictHintLayout = new QHBoxLayout(m_addressHintLabel);
    conflictHintLayout->setContentsMargins(0, 0, 0, 0);
    conflictHintLayout->addWidget(m_iconLabel);
    conflictHintLayout->addWidget(m_textLabel);
    conflictHintLayout->addStretch();
    m_addressHintLabel->setLayout(conflictHintLayout);
    m_iconLabel->hide();
    m_textLabel->hide();
}

void CreatNetPage::initLoadingIcon()
{
    m_loadIcons.append(QIcon::fromTheme("lingmo-loading-1-symbolic"));
    m_loadIcons.append(QIcon::fromTheme("lingmo-loading-2-symbolic"));
    m_loadIcons.append(QIcon::fromTheme("lingmo-loading-3-symbolic"));
    m_loadIcons.append(QIcon::fromTheme("lingmo-loading-4-symbolic"));
    m_loadIcons.append(QIcon::fromTheme("lingmo-loading-5-symbolic"));
    m_loadIcons.append(QIcon::fromTheme("lingmo-loading-6-symbolic"));
    m_loadIcons.append(QIcon::fromTheme("lingmo-loading-7-symbolic"));
    m_iconTimer = new QTimer(this);
    connect(m_iconTimer, &QTimer::timeout, this, &CreatNetPage::updateIcon);
}

void CreatNetPage::updateIcon()
{
    if (m_currentIconIndex > 6) {
        m_currentIconIndex = 0;
    }
    m_statusLabel->setPixmap(m_loadIcons.at(m_currentIconIndex).pixmap(ICON_SIZE));
    m_currentIconIndex ++;
}

void CreatNetPage::startLoading()
{
    m_iconTimer->start(FRAME_SPEED);
}

void CreatNetPage::stopLoading()
{
    m_iconTimer->stop();
    m_statusLabel->clear();
}

void CreatNetPage::showIpv4AddressConflict(bool isConflict)
{
    if (isConflict) {
        m_iconLabel->show();
        m_textLabel->show();
    } else {
        m_iconLabel->hide();
        m_textLabel->hide();
    }
}