Steps to compile with make:

1) In files config.make you should change this strings to your path:

 PROJECT_CFLAGS  += -I/home/drakkonne/cef_minimal
 PROJECT_LDFLAGS += -L/home/drakkonne/cef_minimal/Release
 PROJECT_LDFLAGS += -L/home/drakkonne/cef_minimal/libcef_dll_wrapper
 PROJECT_LDFLAGS += -lcef -lcef_dll_wrapper -lX11 -lXcomposite -lXrandr -lXi -lGL -lpthread -ldl -lrt

 to your Chromium Embedded Framework like:
home/YOU_USER/cef_binary_137.0.17+gf354b0e+chromium-137.0.7151.104_linux64
home/YOU_USER/cef_binary_137.0.17+gf354b0e+chromium-137.0.7151.104_linux64/Release
home/YOU_USER/cef_binary_137.0.17+gf354b0e+chromium-137.0.7151.104_linux64/libcef_dll_wrapper

2) You should create symlink home/YOU_USER/cef_binary_137.0.17+gf354b0e+chromium-137.0.7151.104_linux64/Release/libcef.so into my repository: OpenFWithCef/bin/libcef.so
   for example: sudo ln  home/YOU_USER/cef_binary_137.0.17+gf354b0e+chromium-137.0.7151.104_linux64/Release/libcef.so ~/OpenFWithCef/bin/libcef.so

3) In Makefile you should change root path (OF_ROOT) to your OpenFramework compile sources

Thats all.
