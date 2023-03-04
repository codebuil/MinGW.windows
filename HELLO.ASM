

include 'win64ax.inc'

.code

  start:

        invoke  MessageBox,HWND_DESKTOP,"Hello world 64",invoke GetCommandLine,MB_OK



        invoke  ExitProcess,0

.end start
