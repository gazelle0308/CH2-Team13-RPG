@echo off

for /R "%~dp0..\include" %%f in (*.h) do py "%~dp0..\tools\cpplint.py" "%%f"

for /R "%~dp0..\src" %%f in (*.cpp) do py "%~dp0..\tools\cpplint.py" "%%f"

exit /b 0