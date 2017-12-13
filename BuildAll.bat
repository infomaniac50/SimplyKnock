@echo off
for /r %%i in (Scripts\Source\*) do BuildSingle "%%i"
