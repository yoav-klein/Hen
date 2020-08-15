
Rem LINK32_FLAGS="kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib
Rem advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
Rem odbccp32.lib /nologo /subsystem:windows /DLL /incremental:no\
Rem /def:".\Exports.def"\'
  
cl /W4 /c Library.cpp Registry.cpp

link.exe /def:".\Library.def" kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib odbccp32.lib /nologo /subsystem:windows advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib /dll %LINK32_FLAGS% Library.obj Registry.obj