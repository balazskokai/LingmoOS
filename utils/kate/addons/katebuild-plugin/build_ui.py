# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/home/lingmo/project/nx_pkg/LingmoOS/utils/kate/addons/katebuild-plugin/build.ui'
#
# Created by: PyQt5 UI code generator 5.15.11
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_build(object):
    def setupUi(self, build):
        build.setObjectName("build")
        build.resize(407, 308)
        self.verticalLayout = QtWidgets.QVBoxLayout(build)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.u_tabWidget = QtWidgets.QTabWidget(build)
        self.u_tabWidget.setObjectName("u_tabWidget")
        self.errs = QtWidgets.QWidget()
        self.errs.setObjectName("errs")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.errs)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.u_outpTopLayout = QtWidgets.QHBoxLayout()
        self.u_outpTopLayout.setObjectName("u_outpTopLayout")
        self.buildAgainButton = QtWidgets.QPushButton(self.errs)
        self.buildAgainButton.setObjectName("buildAgainButton")
        self.u_outpTopLayout.addWidget(self.buildAgainButton)
        self.cancelBuildButton = QtWidgets.QPushButton(self.errs)
        self.cancelBuildButton.setObjectName("cancelBuildButton")
        self.u_outpTopLayout.addWidget(self.cancelBuildButton)
        self.buildStatusLabel = QtWidgets.QLabel(self.errs)
        self.buildStatusLabel.setText("")
        self.buildStatusLabel.setObjectName("buildStatusLabel")
        self.u_outpTopLayout.addWidget(self.buildStatusLabel)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.u_outpTopLayout.addItem(spacerItem)
        self.verticalLayout_2.addLayout(self.u_outpTopLayout)
        self.textBrowser = QtWidgets.QTextBrowser(self.errs)
        self.textBrowser.setReadOnly(True)
        self.textBrowser.setObjectName("textBrowser")
        self.verticalLayout_2.addWidget(self.textBrowser)
        self.u_tabWidget.addTab(self.errs, "")
        self.verticalLayout.addWidget(self.u_tabWidget)

        self.retranslateUi(build)
        self.u_tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(build)

    def retranslateUi(self, build):
        _translate = QtCore.QCoreApplication.translate
        self.buildAgainButton.setText(_translate("build", "Build again"))
        self.cancelBuildButton.setText(_translate("build", "Cancel"))
        self.u_tabWidget.setTabText(self.u_tabWidget.indexOf(self.errs), _translate("build", "Output"))
