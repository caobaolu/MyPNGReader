set(classes
  LXPNGReader)

vtk_module_add_module(LXPNG
  CLASSES ${classes})

paraview_add_server_manager_xmls(
  XMLS  readers.xml)
