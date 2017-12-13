set rootSkyrimDir="G:\Skyrim\Game"

"%rootSkyrimDir%\Papyrus Compiler\PapyrusCompiler.exe" %1 -f="TESV_Papyrus_Flags.flg" -i=".\Scripts\Source;..\PapyrusCommon\Scripts\Source;%rootSkyrimDir%\Data\Scripts\Source;%rootSkyrimDir%\Data\Source\Scripts;..\SkyUI\Scripts\Source" -o=".\Scripts"
