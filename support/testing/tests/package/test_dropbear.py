import os

import infra.basetest


class TestDropbear(infra.basetest.BRTest):
    passwd = "testpwd"
    config = infra.basetest.BASIC_TOOLCHAIN_CONFIG + \
        """
        LINGMO_TARGET_GENERIC_ROOT_PASSWD="{}"
        LINGMO_SYSTEM_DHCP="eth0"
        LINGMO_PACKAGE_DROPBEAR=y
        LINGMO_PACKAGE_SSHPASS=y
        LINGMO_TARGET_ROOTFS_CPIO=y
        # LINGMO_TARGET_ROOTFS_TAR is not set
        """.format(passwd)

    def test_run(self):
        img = os.path.join(self.builddir, "images", "rootfs.cpio")
        self.emulator.boot(arch="armv5",
                           kernel="builtin",
                           options=["-initrd", img,
                                    "-net", "nic",
                                    "-net", "user"])
        self.emulator.login(self.passwd)
        cmd = "netstat -ltn 2>/dev/null | grep 0.0.0.0:22"
        self.assertRunOk(cmd)

        cmd = "sshpass -p {} ssh -y localhost /bin/true".format(self.passwd)
        self.assertRunOk(cmd)
