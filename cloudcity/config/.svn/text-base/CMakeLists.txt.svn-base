# the exec config tool

# ADD_DEPENDENCIES(bespin bespin_config)
# ADD_DEPENDENCIES(kstyle_bespin_config bespin_config)

# project (bespin-config)
# add_definitions ( -DB_EXPORT=Q_DECL_EXPORT )

set (bespin_config_SOURCES bconfig.cpp config.cpp kdeini.cpp)

qt4_add_resources (bespin_config_SOURCES)
qt4_wrap_ui (bespin_config_FRM_HDRS config.ui)

set (bespin_config_MOC_HDRS bconfig.h config.h dialog.h)
qt4_wrap_cpp(bespin_config_MOC_SRCS ${bespin_config_MOC_HDRS})

# add_library(bespin_config STATIC ${bespin_config_SOURCES} ${bespin_config_MOC_SRCS}  ${bespin_config_FRM_HDRS})

#--------------------------------------------------------

project (bespin)
# add_definitions ( -DB_EXPORT=Q_DECL_IMPORT )
qt4_wrap_ui (bespin_demo_FRM_HDRS uiDemo.ui)
add_executable (bespin main.cpp ${bespin_config_SOURCES} ${bespin_config_MOC_SRCS}  ${bespin_config_FRM_HDRS} ${bespin_demo_FRM_HDRS})
target_link_libraries (bespin ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install (TARGETS bespin DESTINATION bin)

#--------------------------------------------------------

# the kcmstyle plugin, in case
if (KDE4_FOUND)

project (kstyle-bespin-config)
# add_definitions ( -DB_EXPORT=Q_DECL_IMPORT )
kde4_add_plugin (kstyle_bespin_config ${bespin_config_SOURCES} ${bespin_config_FRM_HDRS} )
target_link_libraries (kstyle_bespin_config ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install (TARGETS kstyle_bespin_config DESTINATION ${PLUGIN_INSTALL_DIR})
   
endif (KDE4_FOUND)
