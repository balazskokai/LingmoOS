function(find_lingmosdk_package prj_name lingmosdk_package_name)
    pkg_check_modules(${lingmosdk_package_name}_PKG ${lingmosdk_package_name})
    target_include_directories(${prj_name} PRIVATE ${${lingmosdk_package_name}_PKG_INCLUDE_DIRS})
    target_link_directories(${prj_name} PRIVATE ${${lingmosdk_package_name}_PKG_LIBRARY_DIRS})
    target_link_libraries(${prj_name} ${${lingmosdk_package_name}_PKG_LIBRARIES})
endfunction()


function(target_link_lingmosdk_libraries prj_name)
    find_package(PkgConfig REQUIRED)

    find_lingmosdk_package(${prj_name} lingmosdk-qtwidgets)
    find_lingmosdk_package(${prj_name} lingmosdk-diagnostics)
    find_lingmosdk_package(${prj_name} lingmosdk-log)
    find_lingmosdk_package(${prj_name} lingmosdk-utils)
    find_lingmosdk_package(${prj_name} lingmosdk-config)
    find_lingmosdk_package(${prj_name} lingmosdk-waylandhelper)
    find_lingmosdk_package(${prj_name} lingmosdk-alm)
    find_lingmosdk_package(${prj_name} lingmosdk-sysinfo)
    find_lingmosdk_package(${prj_name} lingmosdk-datacollect)
    find_lingmosdk_package(${prj_name} lingmosdk-systime)
endfunction()

function(target_link_glib_libraries prj_name)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLIB REQUIRED glib-2.0)
    include_directories(${GLIB_INCLUDE_DIRS})
    target_link_libraries(${prj_name} "-lglib-2.0")
endfunction()

function(target_link_qgsettings_libraries prj_name)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(QGSETTINGS REQUIRED IMPORTED_TARGET gsettings-qt)
    target_link_libraries(${prj_name} PkgConfig::QGSETTINGS)
endfunction()

function(target_link_X11_libraries prj_name)
    target_link_libraries(${prj_name} -lX11)
endfunction()

function(target_link_KWindowSystem_libraries prj_name)
    find_package(KF5WindowSystem REQUIRED)
    target_link_libraries(${prj_name} KF5::WindowSystem)
endfunction()
