Rem Current(Working) Directory: D:\...\slnPipeLineV05\DoPipeLine\
Rem Change Directory: D:\...\slnPipeLineV05\Square\
cd ..
cd Square

Rem Variant 1 for debugging DoPipeLine.exe

Rem Command: ..\Debug\DoPipeLine.exe
Rem Command Arguments:"Square<Floats5 2>Errors2|Sum>Results1"
Rem Now Current(Working) Directory: slnPipeLine\Square\
Rem There are all files in this directory


..\Debug\DoPipeLine.exe "Square<Floats5 2>Errors2|Sum>Results1"
type Floats5.txt
type Errors2.txt
type Results1.txt
pause

Rem Variant 2

..\Debug\DoPipeLine.exe "Square<Floats 2>Errors2|Square>Results2"
type Floats.txt
type Errors2.txt
type Results2.txt
pause

Rem Variant 3

..\Debug\DoPipeLine.exe "Sum<Floats 2>Errors2|SqureRoot>Results2"
type Floats.txt
type Errors2.txt
type Results2.txt
pause

Rem End of Job
exit