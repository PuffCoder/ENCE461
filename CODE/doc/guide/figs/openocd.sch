S7 box; right=6, l=, aspect=2.5
S8 box; right=2, l=, fill=blue!50
S1 circle; l=Binary file
S2 box; l=Debugger
S3 box; l=OpenOCD
S4 box; l=USB driver
S5 box; l=ST-link, fill=purple
S6 box; l=SAM4S, fill=green!50
W S1.e S2.w; right=0.5
W S2.e S3.w; right=0.5
W S3.e S4.w; right=0.5
W S4.e S5.w; right
W S5.e S6.w; right
O S7.mid S3.mid; right=0.5
O S8.mid S6.mid; right=0.01
A S7.tl; l=PC, anchor=nw
A S8.tl; l=Wacky board, anchor=nw
;scale=0.75
