format PE64 GUI 5.0
entry start

include 'win64ax.inc'

section '.text' code readable executable
start:
  ; Register the window class
  invoke GetModuleHandle, NULL
  mov    [wc.hInstance], rax
  xor    rax, rax
  mov    [wc.style], rax
  mov    [wc.lpfnWndProc], WindowProc
  mov    [wc.cbClsExtra], rax
  mov    [wc.cbWndExtra], rax
  push   rax
  call   GetModuleHandle
  mov    [wc.hIcon], rax
  mov    [wc.hCursor], rax
  mov    [wc.hbrBackground], COLOR_BTNFACE + 1
  mov    [wc.lpszMenuName], rax
  mov    [wc.lpszClassName], classname
  invoke RegisterClassEx, wc

  ; Show the MsgBox
  invoke MessageBox, 0, msgBoxText, caption, MB_OKCANCEL or MB_ICONINFORMATION or MB_APPLMODAL
  cmp    eax, IDOK
  jne    exit_program

  ; Create the main window
  invoke CreateWindowEx, 0, classname, caption, WS_VISIBLE + WS_POPUP, 100, 100, 300, 300, NULL, NULL, [wc.hInstance], NULL
  mov    [hwnd], rax

  ; Enter the message loop
  message_loop:
    invoke GetMessage, msg, NULL, 0, 0
    or     eax, eax
    jz     exit_loop
    invoke TranslateMessage, msg
    invoke DispatchMessage, msg
    jmp    message_loop

  ; Exit the program
  exit_loop:
    invoke ExitProcess, [msg.wParam]

exit_program:
  invoke ExitProcess, 0

; Window procedure
WindowProc:
  cmp    [uMsg], WM_DESTROY
  je     .wmdestroy
  cmp    [uMsg], WM_PAINT
  je     .wmpaint
  invoke DefWindowProc, [hwnd], [uMsg], [wParam], [lParam]
  jmp    .finish

.wmdestroy:
  invoke PostQuitMessage, 0
  xor    rax, rax
  jmp    .finish

.wmpaint:
  push   rax
  push   COLOR_BTNFACE + 1
  call   GetSysColor
  invoke SetBkColor, [wParam], eax
  invoke DefWindowProc, [hwnd], [uMsg], [wParam], [lParam]
  pop    rax
  jmp    .finish

.finish:
  ret

section '.idata' import data readable
  library kernel32, 'kernel32.dll', \
          user32, 'user32.dll'

  import kernel32, \
          ExitProcess, 'ExitProcess', \
          GetModuleHandle, 'GetModuleHandleA'

  import user32, \
          RegisterClassEx, 'RegisterClassExA', \
          CreateWindowEx, 'CreateWindowExA', \
          DefWindowProc, 'DefWindowProcA', \
          GetMessage, 'GetMessageA', \
          TranslateMessage, 'TranslateMessage', \
          DispatchMessage, 'DispatchMessageA', \
          PostQuitMessage, 'PostQuitMessageA', \
          MessageBox, 'MessageBoxA', \
          SetBkColor, 'SetBkColor', \
          GetSysColor, 'GetSysColor'

section '.data
